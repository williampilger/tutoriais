# Wake Up On LAN - Linux

Eu, pessoalmente, estou usando um `PopOS! 22.04 LTS` para realizar o procedimento.

## 1 - Obtenha os dados da sua placa de rede

Pode ser feito de duas formas, observando o retorno dos comandos:

> ifconfig

ou

> ip a

Você precisará dos dados `nome da interface` e `MAC`.

 
## 2 - Configurar o Wake-On-LAN
 
Salve o script abaixo, substituindo a variávei `INTERFACE` pelo valor correto.

```sh
INTERFACE="enp4s0"

apt-get install -y ethtool

echo """
[Unit]
Description=Habilitar Wake On Lan

[Service]
Type=oneshot
ExecStart = /sbin/ethtool --change $INTERFACE wol g

[Install]
WantedBy=basic.target
""" > /etc/systemd/system/wol_fix.service

systemctl daemon-reload
systemctl enable wol.service
```

Execute o script como root:

> sudo chmod +x script.sh & sudo ./script.sh

Reinicie o PC para que funcione.

# Sobre

Baseado [nesse tutorial completo](https://necromuralist.github.io/posts/enabling-wake-on-lan/).

By: **will.i.am** | Bom Princípio - RS
