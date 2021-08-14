# Exemplo de configuração de Ubuntu Server

Para realização deste passo a passo estarei usando um `Ubuntu Server 20.04 LTS` (Aconselho que utilize as versões LTS sempre que for trabalhar com servidores que exijam disponibilidade e confiabilidade).

## Instalação do sistema

Instalei o servidor em uma máquina virtual, basicamente no 'next netx finish', então não irei descrever a instalação.

## Preparação básica

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

## Gerenciando seu servidor

**Apache:**

| **Comando** | **Função** |
| ----------- | ----------- |
| `hostname -I` | Para obter o endereço do seu servidor |
| `sudo systemctl stop apache2` | Parar servidor web |
| `sudo systemctl start apache2` | Iniciar o servidor quando ele for parado |
| `sudo systemctl restart apache2` | Parar e então iniciar o serviço novamente |
| `sudo systemctl reload apache2` | Recarregar configurações sem reiniciar serviço |
| `sudo systemctl disable apache2` | Tira o apache do início automático |
| `sudo systemctl enable apache2` | reativar o serviço de inicialização no boot |


## Referências

- [Como Instalar o Servidor Web Apache no Ubuntu 20.04](https://www.digitalocean.com/community/tutorials/how-to-install-the-apache-web-server-on-ubuntu-20-04-pt);
- 
