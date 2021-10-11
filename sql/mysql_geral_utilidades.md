# Utilidades gerais -> MySQL no Ubuntu Server

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

## Sobre

By: will.i.am | Balneário Camboriú - SC

2021.10.11
