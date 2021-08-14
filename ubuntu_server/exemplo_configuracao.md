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


## Referências

- [Como Instalar o Servidor Web Apache no Ubuntu 20.04](https://www.digitalocean.com/community/tutorials/how-to-install-the-apache-web-server-on-ubuntu-20-04-pt);
- 
