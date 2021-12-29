# Instalando e rodando o Ubuntu Server para hospedar um site a Raspberry Pi

Estou usando, neste tutorial uma **Raspberry Pi 3 model B**.

## Instalando o sistema operacional

Atualmente, instalado o **Ubuntu Server 20.04 LTS x32 (RPI 2/3/4/400)**, utilizando o **Raspberry Pi Immager**.

Para instalar o immager, use:

> sudo snap install rpi-imager


## Primeiro boot

**IMPORTANTE**: Lembre que o login padrão do ubuntu server é `ubuntu` e `ubuntu` como usuário e senha.
Será solicitada a alteração imediata no primeiro login, então digite novamente a **senha atual** e então informe a nova.

Sempre é bom atualizar os aplicativos (**Mas esteja preparado para esperar algumas HORAS, o processo é demorado**):

> sudo apt-get update

> sudo apt-get upgrade -y

## Concluindo configuração

Siga o [tutorial para configuração de ubuntu server](https://github.com/williampilger/tutoriais/blob/master/ubuntu_server/exemplo_configuracao.md), também escrito por mim, mas que serve para instalações em máquinas convencionais também.
