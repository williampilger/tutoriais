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
 
Salve o script abaixo, substituindo a variávei `INTERFACE` pelo valor correto.

```sh
INTERFACE="enp4s0"

apt-get install -y wakeonlan

echo """
#!/bin/sh
/sbin/ethtool -s $INTERFACE wol g
""" > /etc/network/if-up.d/wol_fix.sh
sudo chmod +x /etc/network/if-up.d/wol_fix.sh
echo """
[Unit]
Description=Fix

[Service]
ExecStart=/etc/network/if-up.d/wol_fix.sh
Type=oneshot
RemainAfterExit=yes

[Install]
WantedBy=multi-user.target
""" > /etc/systemd/system/wol_fix.service
systemctl daemon-reload
systemctl enable wol_fix.service
#reboot
```

Reinicie o PC para que funcione.
