# Exemplo de configuração de Ubuntu Server

Para realização deste passo a passo estarei usando um `Ubuntu Server 20.04 LTS` (Aconselho que utilize as versões LTS sempre que for trabalhar com servidores que exijam disponibilidade e confiabilidade).

## Instalação do sistema

Instalei o servidor em uma máquina virtual, basicamente no 'next netx finish', então não irei descrever a instalação.

## Preparação básica

### Suporte à SSH

Para acessar remotamente, indico que seja instalado o serviço SSH, e o pacote net-tools.

> sudo apt-get install openssh-server

> sudo service ssh start

> sudo apt-get install net-tools

## Preparando o Apache

**Instalando o apache:**

> sudo apt-get update

> sudo apt-get install apache2

**Configurando o Firewall:**
Execute o comando abaixo para ver as opções:

> sudo ufw app list

Você verá as seguintes opções:

- **Apache**: Este perfil abre apenas a porta 80 (normal, tráfego Web não criptografado);
- **Apache Full**: Este perfil abre ambas as portas 80 (normal, tráfego Web não criptografado) e 443 (tráfego TLS/SSL criptografado);
- **Apache Secure**: Este perfil abre apenas a porta 443 (tráfego TLS/SSL criptografado);

É recomendável que habilite o perfil mais restritivo que ainda assim permitirá o tráfego que você configurou. Como ainda não configurou o SSL para seu servidor neste guia, nós precisaremos apenas permitir o tráfego na porta 80:

> sudo ufw allow 'Apache'
 
Você pode verificar a mudança digitando:

> sudo ufw status

**Verificando a instalação:**

No final do processo de instalação, o Ubuntu 20.04 inicia o Apache. O servidor Web já deve estar em funcionamento.

Verifique com o sistema init systemd para garantir que o serviço esteja funcionando digitando:

> sudo systemctl status apache2
 
Output:
```
● apache2.service - The Apache HTTP Server
     Loaded: loaded (/lib/systemd/system/apache2.service; enabled; vendor preset: enabled)
     Active: active (running) since Thu 2020-04-23 22:36:30 UTC; 20h ago
       Docs: https://httpd.apache.org/docs/2.4/
   Main PID: 29435 (apache2)
      Tasks: 55 (limit: 1137)
     Memory: 8.0M
     CGroup: /system.slice/apache2.service
             ├─29435 /usr/sbin/apache2 -k start
             ├─29437 /usr/sbin/apache2 -k start
             └─29438 /usr/sbin/apache2 -k start
```

Acesse-o atravéz do IP em um navegador.

OBS: Os arquivos do seu site serão salvos em `/var/www/htlm`.

**Configurando hosts Virtuais (Recomendado)**

Crie e configure a pasta do seu site e dê as permissões:

> sudo mkdir /var/www/nome_do_seu_site

> sudo chown -R $USER:$USER /var/www/your_domain

> sudo chmod -R 755 /var/www/your_domain

OBS: Caso no futuro tenha problemas de acesso à arquivos, use:

> sudo chmod -R 777 /var/www/your_domain

> sudo chown -R $USER:www-data /var/www/your_domain

Cole seus arquivos do site na pasta criada. Vamos criar uma página de amostra:

> sudo nano /var/www/your_domain/index.html
 
Dentro, adicione a seguinte amostra HTML:

``` html
<html>
    <head>
        <title>Welcome to Your_domain!</title>
    </head>
    <body>
        <h1>Success!  The your_domain virtual host is working!</h1>
    </body>
</html>
```

Salve o arquivo.

Para que o apache server entenda que este agora deve ser o site, configure usando:

> sudo nano /etc/apache2/sites-available/your_domain.conf

e cole o conteúdo abaixo:

```
<VirtualHost *:80>
    ServerAdmin webmaster@localhost
    ServerName your_domain
    ServerAlias www.your_domain
    DocumentRoot /var/www/your_domain
    ErrorLog ${APACHE_LOG_DIR}/error.log
    CustomLog ${APACHE_LOG_DIR}/access.log combined
</VirtualHost>
```

Salve e feche o arquivo.

Vamos habilitar o arquivo com a ferramenta a2ensite:

> sudo a2ensite your_domain.conf
 
Desabilite o site padrão definido em 000-default.conf:

> sudo a2dissite 000-default.conf
 
Em seguida, vamos testar à procura de erros de configuração:

> sudo apache2ctl configtest
 
Você deve receber a seguinte saída:

```
Output
Syntax OK
```

Reinicie o Apache para implementar as suas alterações:

> sudo systemctl restart apache2

**Gerenciando seu servidor Apache**

| **Comando** | **Função** |
| ----------- | ----------- |
| `hostname -I` | Para obter o endereço do seu servidor |
| `sudo systemctl stop apache2` | Parar servidor web |
| `sudo systemctl start apache2` | Iniciar o servidor quando ele for parado |
| `sudo systemctl restart apache2` | Parar e então iniciar o serviço novamente |
| `sudo systemctl reload apache2` | Recarregar configurações sem reiniciar serviço |
| `sudo systemctl disable apache2` | Tira o apache do início automático |
| `sudo systemctl enable apache2` | reativar o serviço de inicialização no boot |


## Preparando Servidor FTP

> sudo apt-get -y install vsftpd

Altere as configurações:

> sudo nano /etc/vsftpd.conf

Obs.: Para permitir escrite, descomente a linha `write_enable=YES`.

Reinicie o serviço após altrerar as configurações:

> sudo /etc/init.d/vsftpd restart

Obs.: Por padrão, o diretório raiz do servidor será `/home/username`.


## Instalando mySQL

> sudo apt -y install mysql-server

Use o comando abaixo para configurar o MySQL:

> sudo mysql_secure_installation

Para acessar o servidor SQL use:

> sudo mysql

Iremos criar ainda um usuário e dar os privilégios totais a ele. Primeiro, acesse o sqlserver digitando:

> sudo mysql

Crie um novo usuário:

> CREATE USER 'novo_usuário'@'localhost' IDENTIFIED BY 'senha';

Dê todos os privilégios à ele:

> GRANT ALL PRIVILEGES ON * . * TO 'novo_usuario'@'localhost';

Atualize as permissões:

> FLUSH PRIVILEGES;


## Instalando o interpretador PHP

> sudo apt install -y php libapache2-mod-php php-mysql


## Referências

- [Como Instalar o Servidor Web Apache no Ubuntu 20.04](https://www.digitalocean.com/community/tutorials/how-to-install-the-apache-web-server-on-ubuntu-20-04-pt);
- [Como Instalar Linux, Apache, MySQL, PHP (Pilha LAMP) no Ubuntu 20.04](https://www.digitalocean.com/community/tutorials/how-to-install-linux-apache-mysql-php-lamp-stack-on-ubuntu-20-04-pt);
- [Como Criar Usuário MySQL e Conceder Privilégios: Guia para Iniciantes](https://www.hostinger.com.br/tutoriais/como-criar-usuario-mysql-e-conceder-privilegios);
- [Forbidden You don't have permission to access / on this server. Additionally, a 403 Forbidden error was encountered](https://www.digitalocean.com/community/questions/forbidden-you-don-t-have-permission-to-access-on-this-server-additionally-a-403-forbidden-error-was-encountered);
