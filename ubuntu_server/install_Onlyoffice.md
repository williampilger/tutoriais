# Instalando o OnlyOffice

Veja o [Tudorial completo no site oficial](https://helpcenter.onlyoffice.com/installation/workspace-install-linux.aspx);


## Instalando no Docker

Eu iniciei a instalação em um container criado com base na imagem `ubuntu`, instalação limpa, pois não foi muito fácil usar o container já existente.

ABANDONADO


## Instalando no Ubuntu Server 23.04 LTS

### 1 - Instale o Ubuntu nume VM ou na máquina local

### 2 - Atualizar os pacotes atuais e instalar essenciais

> sudo apt update && sudo apt upgrade

### 3 - Instalar o Onlyoffice

> wget https://download.onlyoffice.com/install/workspace-install.sh

> chmod +x workspace-install.sh

> sudo ./workspace-install.sh

**OBS.:** Usar opção `N` no diálogo (não instalar usando Docker)

### 4 - Reiniciar
