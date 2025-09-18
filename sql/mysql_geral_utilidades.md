# Utilidades gerais -> MySQL no Ubuntu Server

## Instalar o SERVER no Ubuntu e Conectar a um Banco

> sudo apt update && sudo apt install mysql-server -y

Comandos para controle:
```bash
# Forçar o início do Servidor
sudo systemctl start mysql

# Verificar se está rodando
systemctl status mysql

# Desativar a inicialização automática (ou ativar, com `enable`)
sudo systemctl disable mysql

# Parar o Servidor
sudo systemctl stop mysql
```


## Listar usuários

Para saber quais usuários estão cadastrados no seu servidor MySQL, logue como administrador:

> sudo mysql

E Liste os usuários:

> Select user from mysql.user;

## Alterar senha de algum usuário MySQL

**Para usuário ROOT**

Altere a senha rodando a configuração do MySQL:

> sudo mysql_secure_installation

**Para os demais usuários**

Para isso, acesse o terminal do mysql com algum usuário com privilégios de administrador:

> sudo mysql

ou

> mysql -u root -p

E defina a nova senha:

> SET PASSWORD FOR 'user'@'localhost' = 'NovaSenha';

---

## Instalar o CLIENTE no Ubuntu e Conectar a um Banco

> sudo apt update && sudo apt install default-mysql-client -y

```sh
DB_HOST=192.168.0.1
DB_USER="seu-usuario"
DB_NAME="database"
mysql -u $DB_USER -p -h $DB_HOST $DB_NAME
```

---

## Sobre

By: will.i.am | Balneário Camboriú - SC

2021.10.11
