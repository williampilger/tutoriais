# Instalando e Configurando XAMPP Server, do zero, no Ubuntu

Primeiramente, faça o download do software no [site oficial](https://www.apachefriends.org/pt_br/index.html).

## Instalação

Após a realização do download, abra as propriedades do app.run e permita que ele seja executado como programa.

Abra um terminal e execute-o como administrador:

> sudo ./NOME_DO_APP.run

Conclua a instalação pela interface gráfica.

## Configuração Inicial

Ao Iniciar a aplicação, Vá para a guia `Manage Servers` e ative o MySQL server.

Abra o navegador e acesse [localhost/phpmyadmin](http://localhost/phpmyadmin) para abrir o gerenciamento do servidor SQL.

## Alterando senha root e Controles de acesso

Por padrão, o Servidor phpMyAdmin não exige senha ao logar, o que pode ser um problema, principalmente se este servidor ficar exposto na rede.
Nos proximos passos, vamos definir uma senha, e configurar o acesso adequado para tal.

 Acesse o painel do phpmyadmin, encontre a guia `Contas de utilizador` e localize o usuário root. Em seguida clique em `Alterar Senha`, insira uma senha, e confirme clicando em `Executar`. Obs.: Mais de um usuário Root será exibido, indico que seja definida a senha em todos.
 
 Feito isto, provavelmente seu acesso será banido.
 
 Acesse novamente o terminal do seu servidor e execute:
 
 > sudo nano /opt/lampp/phpmyadmin/config.inc.php

Localise o trecho abaixo,

```
$cfg['Servers'][$i]['auth_type'] = '';
$cfg['Servers'][$i]['user'] = 'root';
$cfg['Servers'][$i]['password'] = '';
$cfg['Servers'][$i]['extension'] = 'mysqli';
$cfg['Servers'][$i]['AllowNoPassword'] = false;
$cfg['Lang'] = '';
```

E o preencha da seguinte forma:

```
$cfg['Servers'][$i]['auth_type'] = 'cookie';
$cfg['Servers'][$i]['user'] = 'root';
$cfg['Servers'][$i]['password'] = 'digite aqui sua senha';
$cfg['Servers'][$i]['extension'] = 'mysqli';
$cfg['Servers'][$i]['AllowNoPassword'] = true;
$cfg['Lang'] = 'pt_BR';
```

Salve as alterações, e recarregue a página do phpMyAdmin.


## Permitindo conexão externa ao phpMyAdmin

Pelo terminal, edite o arquivo de configuração do XAMPP usando:

> sudo gedit /opt/lampp/etc/extra/httpd-xampp.conf

E procure pela chave abaixo:

```
<Directory "/opt/lampp/phpmyadmin">
    AllowOverride AuthConfig Limit
    Require all granted
    ErrorDocument 403 /error/XAMPP_FORBIDDEN.html.var
</Directory>
```

Como pode perceber, trocamos `Required local` por `Required all granted`. Salve as alterações, e reinicie o XAMPP usando:

> sudo /opt/lampp/lampp reload
