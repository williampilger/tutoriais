# Nginx no PC local para subdomínios, junto com PM2, Apache e outras ferramentas

Objetivo: acessar várias aplicações locais por subdomínio, com Nginx na porta 80/443 roteando para serviços em portas internas (PM2, Apache, Docker, etc).

Exemplo:
- app1.authentylocal.com.br -> 127.0.0.1:3001
- api.authentylocal.com.br -> 127.0.0.1:3002
- admin.authentylocal.com.br -> 127.0.0.1:3003




## 1) DNS local (subdomínios apontando para o PC)

Tenha certeza de que o DNS do seu PC (ou da sua rede) resolve os domínios e subdomínios para o IP do seu PC.
Caso contrário, o Nginx não receberá as requisições.

Você tem as duas opções:

### Para a rede toda (outros PCs e celular)
Use DNS do roteador, Pi-hole ou AdGuard:
- Crie registros A apontando para o IP do seu PC (ex: 192.168.1.50)
- Se puder, use wildcard: *.authentylocal.com.br -> 192.168.1.50


### Só no seu próprio PC

#### Linux

Edite o hosts:
```bash
sudo nano /etc/hosts
```

Adicione:
```text
127.0.0.1  authentylocal.com.br
127.0.0.1  app1.authentylocal.com.br
127.0.0.1  api.authentylocal.com.br
127.0.0.1  admin.authentylocal.com.br
```

Valide:
```bash
getent hosts app1.authentylocal.com.br
```

#### Windows

Abra o **Bloco de Notas** como **Administrador** e abra o arquivo `C:\Windows\System32\drivers\etc\hosts`.

```text
127.0.0.1  authentylocal.com.br
127.0.0.1  app1.authentylocal.com.br
127.0.0.1  api.authentylocal.com.br
127.0.0.1  admin.authentylocal.com.br
```

Valide:
```bat
nslookup app1.authentylocal.com.br
# OU
ping app1.authentylocal.com.br
```

Se estiver usando cache e não atualizar, limpe o DNS e teste de novo:

```bat
ipconfig /flushdns
nslookup app1.authentylocal.com.br
```




## 2) Subir apps em portas internas (PM2, Docker, serviços)

Coloque seus apps para rodar, em portas internas, como as 3001, 3002, 3003, etc.





## 3) Instalar e habilitar o Nginx

```bash
sudo apt update
sudo apt install -y nginx
sudo systemctl enable nginx
sudo systemctl start nginx
```

Checar:
```bash
sudo systemctl status nginx --no-pager -l
sudo nginx -t
```

Ps.: Se tiver Apache instalado, ele pode estar usando a porta 80. Veja o passo 6 para coexistência.




## 4) Configurar o Nginx para subdomínios

Crie um arquivo de site:
```bash
sudo nano /etc/nginx/sites-available/authentylocal
```

Exemplo de configuração (HTTP 80):
```nginx
server {
  listen 80;
  server_name app1.authentylocal.com.br;

  location / {
    proxy_pass http://127.0.0.1:3001;
    proxy_set_header Host $host;
    proxy_set_header X-Real-IP $remote_addr;
    proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
    proxy_set_header X-Forwarded-Proto $scheme;
  }
}

server {
  listen 80;
  server_name api.authentylocal.com.br;

  location / {
    proxy_pass http://127.0.0.1:3002;
    proxy_set_header Host $host;
    proxy_set_header X-Real-IP $remote_addr;
    proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
    proxy_set_header X-Forwarded-Proto $scheme;
  }
}

server {
  listen 80;
  server_name admin.authentylocal.com.br;

  location / {
    proxy_pass http://127.0.0.1:3003;
    proxy_set_header Host $host;
    proxy_set_header X-Real-IP $remote_addr;
    proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
    proxy_set_header X-Forwarded-Proto $scheme;
  }
}
```

Habilite o site:
```bash
sudo ln -s /etc/nginx/sites-available/authentylocal /etc/nginx/sites-enabled/
```

Opcional: desabilitar o site default para evitar confusão:
```bash
sudo rm -f /etc/nginx/sites-enabled/default
```

Recarregue:
```bash
sudo nginx -t
sudo systemctl reload nginx
```



## 5) HTTPS local (opcional, recomendado se o navegador força HTTPS) - !NÃO TESTADO!

Em ambiente local, o jeito mais simples é usar mkcert.

Instale e configure:
```bash
sudo apt install -y mkcert libnss3-tools
mkcert -install
```

Gere certificado wildcard:
```bash
mkcert "*.authentylocal.com.br" authentylocal.com.br
```

Mova para um local padrão:
```bash
sudo mkdir -p /etc/nginx/certs
sudo mv *.pem /etc/nginx/certs/
sudo chmod 600 /etc/nginx/certs/*.pem
```

Adicione blocos 443 (repita por subdomínio):
```nginx
server {
  listen 443 ssl;
  server_name app1.authentylocal.com.br;

  ssl_certificate     /etc/nginx/certs/_wildcard.authentylocal.com.br+1.pem;
  ssl_certificate_key /etc/nginx/certs/_wildcard.authentylocal.com.br+1-key.pem;

  location / {
    proxy_pass http://127.0.0.1:3001;
    proxy_set_header Host $host;
    proxy_set_header X-Forwarded-Proto $scheme;
  }
}
```

Recarregue:
```bash
sudo nginx -t
sudo systemctl reload nginx
```







## 6) Nginx com Apache (coexistência)

### Caso A: Apache como upstream por subdomínio
Deixe o Apache em uma porta interna (ex: 8080 ou 8081) e o Nginx na 80/443.

Apache porta 8080:
- Ajuste o Apache para escutar em 8080 e o VirtualHost correspondente.
- Nginx aponta para http://127.0.0.1:8080

Exemplo Nginx:
```nginx
server {
  listen 80;
  server_name sitephp.authentylocal.com.br;

  location / {
    proxy_pass http://127.0.0.1:8080;
    proxy_set_header Host $host;
  }
}
```

### Caso B: Apache e Nginx competindo pela porta 80
Se Apache estiver na 80, o Nginx não consegue subir ou fica inacessível.
Veja quem está usando 80:
```bash
sudo ss -ltnp | egrep ':80|:443'
```

Se for Apache e você quer Nginx na frente:
```bash
sudo systemctl stop apache2
sudo systemctl disable apache2
```
Depois configure o Apache para outra porta e religue.

## 7) Firewall (se for acessar pela rede)

```bash
sudo ufw allow 80
sudo ufw allow 443
```





## 8) Testes e diagnóstico rápido

Verificar Nginx e portas:
```bash
sudo systemctl status nginx --no-pager -l
sudo nginx -t
sudo ss -ltnp | egrep ':80|:443'
```

Testar roteamento pelo Host:
```bash
curl -I -H "Host: app1.authentylocal.com.br" http://127.0.0.1
```

Testar upstream direto:
```bash
curl -I http://127.0.0.1:3001
pm2 ls
pm2 logs --lines 80
```

Logs do Nginx:
```bash
sudo journalctl -u nginx -b --no-pager -n 200
sudo tail -n 200 /var/log/nginx/error.log
```



## 9) Dicas práticas

- Padronize portas: 3001, 3002, 3003 para apps Node.
- Mantenha um arquivo por ambiente: authentylocal, staging, etc.
- Se o navegador insistir em HTTPS, configure 443 com `mkcert` ou use um domínio `*.test` que o Chrome aceita sem HTTPS.



# Sobre

Tutorial por `William Pilger`, e reescrito e organizado por `Github Copilot`.
