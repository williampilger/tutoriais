# Instalar o MongoDB

O **Pritunl** precisa do **MongoDB** para armazenar dados.

```bash
# Confira o passo a passo em https://www.mongodb.com/pt-br/docs/manual/tutorial/install-mongodb-on-ubuntu/

# Importar chave GPG do MongoDB
sudo apt-get install gnupg curl # Isso deve existir por padrão... mas dependendo do caso pode ser necessário
curl -fsSL https://www.mongodb.org/static/pgp/server-8.0.asc | \
   sudo gpg -o /usr/share/keyrings/mongodb-server-8.0.gpg \
   --dearmor

# Criar arquivo de lista (para Ubuntu 24.04, se for outro, leia a documentação, POR QUE MUDA MESMO!!!)
echo "deb [ arch=amd64,arm64 signed-by=/usr/share/keyrings/mongodb-server-8.0.gpg ] https://repo.mongodb.org/apt/ubuntu noble/mongodb-org/8.0 multiverse" | sudo tee /etc/apt/sources.list.d/mongodb-org-8.0.list

# Instalando
sudo apt update
sudo apt install -y mongodb-org

# Iniciando serviço
sudo systemctl start mongod

# Se receber o erro `Failed to start mongod.service: Unit mongod.service not found.`
# então execute $ sudo systemctl daemon-reload

# Para garantir que o serviço seja iniciado com o sistema
sudo systemctl enable mongod
```

Verifique se está rodando:
```bash
systemctl status mongod
```

Caso queira reiniciar o serviço, use:
```bash
sudo systemctl restart mongod
```
