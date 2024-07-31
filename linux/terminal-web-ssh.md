# Disponibilizar acesso ao terminal via Browser

**Esta funcionalidade JAMAIS deve ser usada em produção!!!**

Instalar o Shell In a Box:
```sl
sudo apt update
sudo apt install shellinabox
```

Edite as configurações:
```sh
sudo nano /etc/default/shellinabox
```

e procure pela entrada abaixo, ajustanto-a:
```txt
SHELLINABOX_ARGS="--no-beep --disable-ssl -s /:SSH:localhost"
```

Reinicie o serviço:
```sh
sudo systemctl restart shellinabox
```sh
