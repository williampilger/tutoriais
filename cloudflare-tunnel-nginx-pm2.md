# Expor apps locais com domínio próprio via Cloudflare Tunnel + Nginx + PM2

Objetivo: acessar aplicações Node rodando localmente (gerenciadas pelo PM2) de fora da rede, usando subdomínios de um domínio próprio, com HTTPS automático e sem abrir portas no roteador.

Arquitetura:

```
navegador → Cloudflare (HTTPS) → cloudflared (tunnel) → nginx :80 → pm2 :300x
```

---

## Pré-requisitos

- Ubuntu com Nginx instalado e configurado por subdomínio na porta 80
- Apps rodando via PM2 em portas internas
- Domínio próprio (ex: `authentydev.com.br`) com DNS gerenciado pelo Cloudflare
  - Se o DNS ainda estiver no registrador (ex: Registro.br), transfira a zona para o Cloudflare primeiro: crie a conta, adicione o domínio, e troque os nameservers no registrador pelos que o Cloudflare indicar

---

## 1. Instalar o cloudflared

```bash
sudo mkdir -p --mode=0755 /usr/share/keyrings
curl -fsSL https://pkg.cloudflare.com/cloudflare-main.gpg | sudo tee /usr/share/keyrings/cloudflare-main.gpg >/dev/null
echo 'deb [signed-by=/usr/share/keyrings/cloudflare-main.gpg] https://pkg.cloudflare.com/cloudflared any main' | sudo tee /etc/apt/sources.list.d/cloudflared.list
sudo apt update && sudo apt install -y cloudflared
```

---

## 2. Autenticar e criar o túnel

```bash
cloudflared tunnel login         # abre o browser — selecione seu domínio
cloudflared tunnel create <nome> # ex: cloudflared tunnel create authentydev
```

O comando `create` gera um arquivo JSON de credenciais em `~/.cloudflared/<UUID>.json`.
Anote o UUID retornado — ele será usado em todos os passos seguintes.

---

## 3. Criar os registros CNAME no Cloudflare

Para cada subdomínio que você quer expor, crie um CNAME apontando para o tunnel.
Pode ser feito via comando ou pelo dashboard.

### Via comando (um por subdomínio)

```bash
cloudflared tunnel route dns <nome> <subdominio>.<dominio>
# ex:
cloudflared tunnel route dns authentydev auth.authentydev.com.br
cloudflared tunnel route dns authentydev precificacao.authentydev.com.br
cloudflared tunnel route dns authentydev authentydev.com.br   # apex, se necessário
```

### Via dashboard (Cloudflare → DNS → Records)

Crie um registro para cada subdomínio:

| Type  | Name          | Target                              | Proxy    |
|-------|---------------|-------------------------------------|----------|
| CNAME | auth          | `<UUID>.cfargotunnel.com`           | ✅ Proxied |
| CNAME | precificacao  | `<UUID>.cfargotunnel.com`           | ✅ Proxied |
| CNAME | @             | `<UUID>.cfargotunnel.com`           | ✅ Proxied |

> O proxy (ícone laranja) precisa estar ativo. É ele que termina o HTTPS e encaminha pelo tunnel. O HTTPS é automático — o Cloudflare provisiona o certificado em minutos.

---

## 4. Configurar o tunnel como serviço

Copie as credenciais para `/etc/cloudflared/`:

```bash
sudo mkdir -p /etc/cloudflared
sudo cp ~/.cloudflared/<UUID>.json /etc/cloudflared/
sudo chown root:root /etc/cloudflared/<UUID>.json
sudo chmod 600 /etc/cloudflared/<UUID>.json
```

Crie o arquivo de configuração `/etc/cloudflared/config.yml`:

```yaml
tunnel: <UUID>
credentials-file: /etc/cloudflared/<UUID>.json

ingress:
  - hostname: "*.seudominio.com.br"
    service: http://localhost:80
  - hostname: seudominio.com.br
    service: http://localhost:80
  - service: http_status:404
```

> Substitua `<UUID>` pelo UUID real (ex: `a3393a75-c33f-4c67-b79f-353758e97429`). Não use os caracteres `<>`.

Instale e inicie o serviço:

```bash
sudo cloudflared service install
sudo systemctl enable --now cloudflared
```

Verifique:

```bash
sudo systemctl status cloudflared
cloudflared tunnel info <UUID>
```

O `tunnel info` deve mostrar um conector ativo com IP de origem e edge nodes.

---

## 5. Ajustar o Nginx

O cloudflared entrega as requisições ao nginx via `127.0.0.1` em HTTP. Por isso dois headers precisam ser corrigidos em todos os `server` blocks expostos via tunnel:

```nginx
# ERRADO — com tunnel, $remote_addr é sempre 127.0.0.1 e $scheme é sempre "http"
proxy_set_header X-Real-IP $remote_addr;
proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
proxy_set_header X-Forwarded-Proto $scheme;

# CORRETO — lê os headers que o Cloudflare injeta
proxy_set_header X-Real-IP $http_cf_connecting_ip;
proxy_set_header X-Forwarded-For $http_cf_connecting_ip;
proxy_set_header X-Forwarded-Proto $http_x_forwarded_proto;
```

Exemplo de bloco completo:

```nginx
server {
  listen 80;
  server_name app.seudominio.com.br app.seudominio-local.com.br;

  location / {
    proxy_pass http://127.0.0.1:3001;
    proxy_http_version 1.1;
    proxy_set_header Upgrade $http_upgrade;
    proxy_set_header Connection "upgrade";
    proxy_set_header Host $host;
    proxy_set_header X-Real-IP $http_cf_connecting_ip;
    proxy_set_header X-Forwarded-For $http_cf_connecting_ip;
    proxy_set_header X-Forwarded-Proto $http_x_forwarded_proto;
    proxy_cache_bypass $http_upgrade;
  }
}
```

> Os headers `Upgrade`, `Connection` e `proxy_http_version 1.1` são necessários apenas para apps com WebSocket. Para APIs REST simples, podem ser omitidos.

> Manter `authentylocal` e `authentydev` no mesmo `server_name` funciona. Quando acessado localmente, `$http_cf_connecting_ip` fica vazio — inofensivo se o app não depender do IP real em dev.

Recarregue o Nginx:

```bash
sudo nginx -t && sudo systemctl reload nginx
```

---

## 6. Testar

### Nginx local (sem passar pelo tunnel)

```bash
curl -I -H "Host: auth.seudominio.com.br" http://127.0.0.1
```

Deve retornar `200` (ou o código que o app retorna). `502` indica que o app PM2 não está respondendo; `404` do nginx indica que o `server_name` não casou.

### DNS propagado

```bash
dig auth.seudominio.com.br CNAME
```

Deve retornar o `<UUID>.cfargotunnel.com` na seção ANSWER. Se retornar `NXDOMAIN`, o CNAME ainda não foi criado ou não propagou.

### Acesso externo

No celular com Wi-Fi desligado (4G):

```
https://auth.seudominio.com.br
```

---

## Diagnóstico rápido

```bash
# Status do serviço
sudo systemctl status cloudflared
journalctl -u cloudflared -n 50 --no-pager

# Conexões ativas do tunnel
cloudflared tunnel info <UUID>

# Validar ingress rules
cloudflared tunnel --config /etc/cloudflared/config.yml ingress validate

# Nginx
sudo nginx -t
sudo systemctl status nginx --no-pager -l
sudo tail -n 50 /var/log/nginx/error.log
```

---

## Observações

- O certificado HTTPS é o Universal SSL do Cloudflare, gratuito e com renovação automática. Cobre `seudominio.com.br` e `*.seudominio.com.br` (um nível de subdomínio). Subdomínios de segundo nível como `api.app.seudominio.com.br` não são cobertos no plano free.
- O cloudflared sobe com a máquina via systemd, igual ao `pm2 startup`.
- Para subdomínios de uso interno ou administrativo, o **Cloudflare Access** (Zero Trust, gratuito até 50 usuários) permite exigir autenticação por e-mail na frente do subdomínio sem mexer no app.
