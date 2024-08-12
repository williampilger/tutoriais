# Comandos gerais para inspeção de rede

Para instalar todos estes utilitários use:

```sh
sudo apt install /
	nettools /
	aircrack-ng

```



## ifconfig

Comando geral para listagem das interfaces de rede.
> ifconfig



## ip

Listar interfaces de rede
> ip link show

Ativar/Desativar uma interface
> sudo ip link set [interface] down
> sudo ip link set [interface] up



## nmcli
 
Listar interfaces de rede:
> nmcli

Listar Redes Wi-Fi disponíveis
> nmcli dev wifi list



## iwconfig

Listar interfaces Wi-Fi
> iwconfig


Colocar uma interface em modo "Ouvinte"
```sh
sudo ip link set [interface] down
sudo iwconfig [interface] mode monitor
sudo ip link set [interface] up
```


## iwlist

Listar redes wi-fi ao alcance de uma interface específica
> sudo iwlist [interface] scan

Você pode ir aplicando filtros para reduzir a informação:
> sudo iwlist [interface] scan | grep -E 'SSID|Channel' | grep -v 'Channel 0'



## lsusb

Listar dispositivos USB conectados
> lsusb



