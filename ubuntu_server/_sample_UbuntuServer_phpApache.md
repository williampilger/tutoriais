# Exemplo de configuração de Ubuntu Server

Para realização deste passo a passo estarei usando um `Ubuntu Server 20.04 LTS` (Aconselho que utilize as versões LTS sempre que for trabalhar com servidores que exijam disponibilidade e confiabilidade).

Acesse o script completo [aqui](#script-completo)

## Instalação do sistema

Instalei o servidor em uma máquina virtual, basicamente no 'next netx finish', então não irei descrever a instalação.

## Preparação básica

### Suporte à SSH

Para acessar remotamente, indico que seja instalado o serviço SSH, e o pacote net-tools.

> sudo apt-get install openssh-server

> sudo service ssh start

> sudo apt-get install net-tools

## Preparando o Apache

### Instalando o apache

> sudo apt-get update

> sudo apt-get install apache2

### Configurando o Firewall

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

### Verificando a instalação

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

### Configurando hosts Virtuais (Recomendado)

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

### Gerenciando seu servidor Apache

| **Comando** | **Função** |
| ----------- | ----------- |
| `hostname -I` | Para obter o endereço do seu servidor |
| `sudo systemctl stop apache2` | Parar servidor web |
| `sudo systemctl start apache2` | Iniciar o servidor quando ele for parado |
| `sudo systemctl restart apache2` | Parar e então iniciar o serviço novamente |
| `sudo systemctl reload apache2` | Recarregar configurações sem reiniciar serviço |
| `sudo systemctl disable apache2` | Tira o apache do início automático |
| `sudo systemctl enable apache2` | reativar o serviço de inicialização no boot |

### Configurando acesso HTTPS ao seu servidor

Esta configuração é opcional, e possivelmente não gere um certificado "confiável" para seu site.

#### Ativar suporte ao SSL

> sudo a2enmod ssl

> sudo systemctl restart apache2

#### Emitir um certificado para seu site

Abaixo, o comando para criar um **Certificado SSL Auto-assinado**

> sudo openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout /etc/ssl/private/server.SEU_DOMINIO.key -out /etc/ssl/certs/server.SEU_DOMINIO.crt

Você precisará preencher os seguintes dados:

```
Country Name (2 letter code) [AU]:
State or Province Name (full name) [Some-State]:
Locality Name (eg, city) []:
Organization Name (eg, company) [Internet Widgits Pty Ltd]:
Organizational Unit Name (eg, section) []:
Common Name (e.g. server FQDN or YOUR name) []:
Email Address []:
```

#### Configurando Site com SSL

Crie uma cópia do arquivo de configuração do se site (já criado no passo anterior onde foi configurado o sie HTTP):

> sudo cp -a /etc/apache2/sites-available/SEU_DOMINIO{.conf,-ssl.conf}

Edite o novo arquivo:

> sudo nano /etc/apache2/sites-available/SEU_DOMINIO-ssl.conf

Trocando a porta: `<VirtualHost *:80>` por `<VirtualHost *:443>`.

E acrescentando as seguintes três linhas:

```
SSLEngine on
SSLCertificateKeyFile /etc/ssl/private/server.SEU_DOMINIO.key
SSLCertificateFile /etc/ssl/certs/server.SEU_DOMINIO.crt
```
 Acrescente seu site às configurações do apache2:
 
 > sudo a2ensite SEU_DOMINIO-ssl.conf

Reinicie o serviço:

> sudo systemctl restart apache2

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

# Script Completo

```sh
sudo su
DomainName='localserver'
local_user='ubuntu' #inform the name of the local user that will administrate the domain
server_ip='192.168.0.15' #inform the static IP fot yout server
server_gateway='192.168.0.1' #inform the static subnet mask

apt update
apt upgrade -y
apt install -y openssh-server net-tools
service ssh start

#CONFIGURAÇÕES DE REDE
cp /etc/netplan/00-installer-config.yaml /etc/netplan/00-installer-config.yaml.bkp
echo "
network:
  ethernets:
    eth0:
      dhcp4: true
      addresses: [${server_ip}/24]
      gateway4: ${server_gateway}
  version: 2
" > /etc/netplan/00-installer-config.yaml
netplan apply #aplica nova política de IP

#CONFIGURANDO APACHE
apt install -y apache2
ufw allow 'Apache'
mkdir /var/www/${DomainName}
chown -R $local_user:www-data /var/www/${DomainName}
chmod -R 777 /var/www/${DomainName}
echo "
<html>
    <head>
        <title>Welcome to ${DomainName}!</title>
    </head>
    <body>
        <h1>Success!  The ${DomainName} virtual host is working!</h1>
    </body>
</html>
" > /var/www/${DomainName}/index.html
echo "
<VirtualHost *:80>
    ServerAdmin webmaster@localhost
    ServerName ${DomainName}
    ServerAlias www.${DomainName}
    DocumentRoot /var/www/${DomainName}
    ErrorLog ${APACHE_LOG_DIR}/error.log
    CustomLog ${APACHE_LOG_DIR}/access.log combined
</VirtualHost>
" > /etc/apache2/sites-available/${DomainName}.conf
a2ensite ${DomainName}.conf #habilitando nova configuração (HTTP)
echo "
<VirtualHost *:443>
    ServerAdmin webmaster@localhost
    ServerName ${DomainName}
    ServerAlias www.${DomainName}
    DocumentRoot /var/www/${DomainName}
    ErrorLog ${APACHE_LOG_DIR}/error.log
    CustomLog ${APACHE_LOG_DIR}/access.log combined
    SSLEngine on
    SSLCertificateKeyFile /etc/ssl/private/server.${DomainName}.key
    SSLCertificateFile /etc/ssl/certs/server.${DomainName}.crt
</VirtualHost>
" > /etc/apache2/sites-available/${DomainName}-ssl.conf
a2ensite ${DomainName}-ssl.conf #habilitando nova configuração (HTTPS)
a2dissite 000-default.conf #deshabilitando antiga
a2enmod ssl #habilitar SSL (https connections)
openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout /etc/ssl/private/server.${DomainName}.key -out /etc/ssl/certs/server.${DomainName}.crt #criar chave SSL
systemctl restart apache2

#CONFIGURANDO FTP
apt -y install vsftpd
ufw allow OpenSSH
ufw allow 20/tcp
ufw allow 21/tcp
ufw allow 990/tcp
ufw allow 40000:50000/tcp
cp /etc/vsftpd.conf /etc/vsftpd.conf.bkp
echo "write_enable=YES" >> /etc/vsftpd.conf
echo "chroot_local_user=YES" >> /etc/vsftpd.conf
echo "allow_writeable_chroot=YES" >> /etc/vsftpd.conf
echo "secure_chroot_dir=/var/www/${DomainName}" >> /etc/vsftpd.conf
/etc/init.d/vsftpd restart

#CONFIGURANDO PHP
apt install -y php libapache2-mod-php php-mysql php-curl php-mbstring composer

#CONFIGURANDO MYSQL
apt -y install mysql-server

```
