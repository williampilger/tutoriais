# Wake Up On LAN - Linux

Eu, pessoalmente, estou usando um `PopOS! 22.04 LTS` para realizar o procedimento.

## 1 - Obtenha os dados da sua placa de rede

Pode ser feito de duas formas, observando o retorno dos comandos:
 
```sh
sudo apt-get install -y nettools
ifconfig
```
**ou**
 
```sh
sudo apt-get install -y ethtool
ip a
```

Você precisará dos dados `nome da interface` e `MAC`.

 
## 2 - Configurar o Wake-On-LAN
 
Instalando a ferramenta:
 
> sudo apt-get install -y wakeonlan

Crie o arquivo de configurações `/etc/network/if-up.d/wol_fix.sh`

> sudo nano /etc/network/if-up.d/wol_fix.sh

Defina o conteúdo, e salve:

```txt
#!/bin/sh
/sbin/ethtool -s %INTERFACE% wol g
```

Script completo pra isso:
```sh
INTERFACE = "enp4s0"
MAC = "00:00:00:00:00:00"

apt get install -y wakeonlan
echo """
#!/bin/sh
/sbin/ethtool -s $INTERFACE wol g
""" > /etc/network/if-up.d/wol_fix.sh
```
