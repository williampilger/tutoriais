# UFW no Ubuntu: guia rápido (Firewall)

Este guia é um resumo prático para usar o **UFW (Uncomplicated Firewall)** no Ubuntu.

> Dica: no Ubuntu, o UFW normalmente gerencia regras do `iptables`/`nftables` por baixo. Você trabalha só com comandos do UFW.

---

## 1) Instalar e verificar status

```bash
sudo apt update
sudo apt install ufw
sudo ufw status verbose
```

Se estiver desativado, você verá `Status: inactive`.

---

## 2) Política padrão (recomendado)

Para servidores e PCs em geral:

```bash
sudo ufw default deny incoming
sudo ufw default allow outgoing
```

Isso bloqueia conexões **entrando** e permite conexões **saindo**.

---

## 3) Habilitar e desabilitar

### Habilitar

```bash
sudo ufw enable
```

### Desabilitar

```bash
sudo ufw disable
```

> Atenção em servidores remotos: antes de habilitar, libere **SSH** (porta 22) ou você pode se trancar fora.

---

## 4) Liberar portas e serviços (ALLOW)

### Liberar uma porta TCP

```bash
sudo ufw allow 22/tcp
sudo ufw allow 80/tcp
sudo ufw allow 443/tcp
```

### Liberar uma porta UDP

```bash
sudo ufw allow 1194/udp
```

### Liberar uma porta em TCP e UDP

```bash
sudo ufw allow 53
```

### Liberar um intervalo de portas

```bash
sudo ufw allow 60000:61000/udp
```

### Liberar um serviço conhecido (por nome)

```bash
sudo ufw allow ssh
sudo ufw allow http
sudo ufw allow https
```

---

## 5) Bloquear portas e serviços (DENY / REJECT)

### Bloquear (silencioso)

```bash
sudo ufw deny 445/tcp
```

### Rejeitar (responde ao cliente)

```bash
sudo ufw reject 445/tcp
```

Use `deny` quando você quer “sumir”. Use `reject` quando faz sentido responder rapidamente.

---

## 6) Permitir por IP (whitelist)

### Permitir todo tráfego de um IP

```bash
sudo ufw allow from 192.168.0.50
```

### Permitir um IP apenas para uma porta

```bash
sudo ufw allow from 192.168.0.50 to any port 22 proto tcp
```

### Permitir uma rede inteira (CIDR)

```bash
sudo ufw allow from 192.168.0.0/24
```

---

## 7) Regras por interface e direção

### Permitir apenas na interface LAN (exemplo: `enp3s0`)

```bash
sudo ufw allow in on enp3s0 to any port 22 proto tcp
```

### Permitir saída específica (raramente necessário)

```bash
sudo ufw allow out 53/udp
```

---

## 8) Rate limit (proteção básica contra brute force)

Muito útil para SSH:

```bash
sudo ufw limit 22/tcp
```

Isso aplica limites de conexão por origem.

---

## 9) Listar regras, remover regras, e ordem

### Listar regras numeradas

```bash
sudo ufw status numbered
```

### Deletar regra pelo número

```bash
sudo ufw delete 3
```

### Deletar regra repetindo exatamente a regra

```bash
sudo ufw delete allow 80/tcp
```

> Ordem importa: UFW avalia regras em sequência. Normalmente as regras mais específicas devem aparecer antes.

---

## 10) Logs e troubleshooting

### Habilitar logs

```bash
sudo ufw logging on
```

Níveis:

```bash
# Loga bloqueios (com rate limmit)
sudo ufw logging low
# Loga bloqueios (sem rate limmit) + coisas não condizentes com as políticas de permissão (com rate limmit)
sudo ufw logging medium
# Loga bloqueios (sem rate limmit) + coisas não condizentes com as políticas de permissão (sem rate limmit) + Tudo o que passou (com rate limit)
sudo ufw logging high
# simplesmente loga tudo (isso aqui ligado por umas horas pode lotar o disco se for um servidor com muito acesso!!)
sudo ufw logging full
```

### Ver eventos no syslog/journal

```bash
sudo journalctl -e | grep -i ufw
```

ou:

```bash
sudo grep -i ufw /var/log/syslog
```

---

## 11) Perfis de aplicativos (Application Profiles)

Alguns pacotes instalam perfis do UFW.

### Listar perfis

```bash
sudo ufw app list
```

### Ver detalhes do perfil

```bash
sudo ufw app info "OpenSSH"
```

### Liberar por perfil

```bash
sudo ufw allow "OpenSSH"
```

---

## 12) IPv6

Verifique se IPv6 está habilitado no UFW:

```bash
sudo cat /etc/default/ufw | grep -i ipv6
```

O ideal é manter `IPV6=yes` se sua máquina usa IPv6, para não deixar “um buraco” de firewall no IPv6.

Depois de alterar:

```bash
sudo ufw disable
sudo ufw enable
```

---

## 13) “Reset” do UFW

Apaga regras e volta ao padrão:

```bash
sudo ufw reset
```

> Isso remove tudo. Use com cuidado.

---

## 14) Exemplos típicos

### PC pessoal (fechado)

```bash
sudo ufw default deny incoming
sudo ufw default allow outgoing
sudo ufw enable
```

### Servidor web + SSH

```bash
sudo ufw default deny incoming
sudo ufw default allow outgoing
sudo ufw allow 22/tcp
sudo ufw allow 80/tcp
sudo ufw allow 443/tcp
sudo ufw enable
```

### Liberar uma porta para uma máquina específica na LAN

Exemplo: liberar `3000/tcp` apenas para `192.168.0.50`:

```bash
sudo ufw allow from 192.168.0.50 to any port 3000 proto tcp
```

---

## 15) Checagens rápidas

- Status detalhado:

```bash
sudo ufw status verbose
```

- Regras numeradas:

```bash
sudo ufw status numbered
```

- Ver IP e interface (pra usar em regras por interface):

```bash
ip a
```

---

## Notas finais

- Se você usa Docker: o Docker pode mexer em regras de rede por conta própria. Em alguns cenários, você precisa integrar UFW com Docker para que as regras do UFW valham para containers publicados.
- Para serviços expostos à internet, prefira permitir por **porta + protocolo** (ex.: `22/tcp`) e, quando possível, restringir por IP.
