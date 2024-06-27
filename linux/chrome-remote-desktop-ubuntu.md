# Instalando e configurando o Google Remote Desktop no Ubuntu



## Pré-requisitos

- Tenha o Google Chrome Instalado



## Instalando

```sh
wget https://dl.google.com/linux/direct/chrome-remote-desktop_current_amd64.deb
sudo dpkg -i chrome-remote-desktop_current_amd64.deb
sudo apt-get -f install
```

Crie o arquivo de configuração:

> sudo nano /etc/chrome-remote-desktop-session

e cole o seguinte conteúdo:

```txt
exec /usr/sbin/lightdm-session "gnome-session --session=gnome"
```

Criando grupo de usuários e adicionando o seu:

```sh
sudo groupadd chrome-remote-desktop
sudo usermod -a -G chrome-remote-desktop $USER
```

Iniciando o Serviço:

```sh
sudo systemctl enable chrome-remote-desktop@$USER
sudo systemctl start chrome-remote-desktop@$USER
```



## Configurando / Ativando

Acesse o [Google Remote Desktop](https://remotedesktop.google.com), e siga os passos.
Provavelmente será necessário acessar de uma guia anônima para seguir os passos.
Será necessário copiar um comando e cola-lo no terminal para autorizar o dispositivo.
