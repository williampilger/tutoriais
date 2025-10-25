# Ativando a descoberta de Rede no Ubuntu (mDNS Avahi)

Isso serve para que seu dispositivo apareça na rede com o Hostname (tipo `meu-pc.local`) na rede local.

## Instalando o Avahi

> sudo apt install avahi-daemon libnss-mdns


## Vendo se está rodando

> sudo systemctl status avahi-daemon
