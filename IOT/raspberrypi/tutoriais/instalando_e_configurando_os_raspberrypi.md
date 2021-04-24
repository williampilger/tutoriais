# Instalando e configurando o OS na Raspberry Pi

## Usando Raspi Imager

Caso queira utilizar a ferramenta automática para criação do SD Card, acesse [o site oficial](https://www.raspberrypi.org/software/) e procure pelo instalador do Raspi Imager.

Se estiver usando linux, poderá instalá-la usando:

> sudo apt install rpi-imager

## Baixando imagem e criando mídia manualmente (standallone)

- Baixe a imagem de sistema desejada na [página de downloads](https://www.raspberrypi.org/software/operating-systems/)
- Baixe também o Balena Etcher, disponível no [site oficial](https://www.balena.io/etcher/?)
- Extraia a imagem que acabou de baixar;
- Execute o Balena Etcher;
- Selecione **Flash from file** e navegue até a ISO que você extraiu;
- Insira e selecione o cartão SD que deseja utilizar (aconselhamos o uso de SD classe 10);
- Clique em **Flash** e digite sua senha de administrador, caso necessário.

## Ativando e acessando o servidor SSH

Você pode ativá-lo sem ter acesso à area de trabalho da Raspberry criando um arquivo vazio na partição **boot** com o nome de **ssh**.

Após bootar a raspberry pi, e conectá-la na rede, você pode procurar o IP dela usando o comando abaixo no seu linux:

> nmap 192.168.1.0/24

Que obviamente pode mudar conforme a configuração da sua rede.

Sabendo agora o Endereço da raspberry pi, acesse-a usando o SSH:

> ssh pi@192.168.1.20

Se esse for o endereço dela, a senha será pedida, e a padrão da rasp é `raspberry`

Agora você já está executando comandos diretamente na raspberry pi remota.

## Instalando interface gráfica na versão lite

Bom, pode ser necessário instalara a interface gráfica após você já ter configurado a versão lite do OS. Para isso use:

> sudo apt install xserver-xorg

> sudo apt install raspberry-ui-mods

> reboot

## Acessando Interface gráfica via VNC

Caso você não tenha instalado o vnc server, instale ele usando (lembrando que é indicado dar um `sudo apt-get update`e `sudo apt-get upgrade`antes de iniciar isso):

> sudo apt-get install realvnc-vnc-server

Este serviço já é instalado por padrão na Raspberry Pi.

Acesse as configurações da rasp usando

> sudo raspi-config

E ative o CNV Server no menu **Interface Options**. Confirme, salve e saia. (Use `TAB`para pular entre as opções)

Acesse o [site do RealVNC](https://www.realvnc.com/pt/connect/download/viewer/) no dispositivo que desejas utilizar para fazer o acesso, e faça o download da aplicação para seu PC. (OBS.: Remmina não apresentou funcionamento correto para esta conexão VNC, com falhas de segurança)
