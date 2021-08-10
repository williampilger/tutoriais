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

## Permitindo conexão externa ao phpMyAdmin

Pelo terminal, edite o arquivo de configuração do XAMPP usando:

> sudo gedit /opt/lampp/etc/extra/httpd-xampp.conf

E procure pela chave `<Directory "
