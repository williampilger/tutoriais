# Kismet - Software para analizar todo o tráfego de rede ao seu redor

Para instalar, siga a [documentação oficial](https://www.kismetwireless.net/packages/);

*Ou, no caso do Ubuntu 25.04 (outro Ubuntu, é outra versão!!)*
```bash
wget -O - https://www.kismetwireless.net/repos/kismet-release.gpg.key --quiet | gpg --dearmor | sudo tee /usr/share/keyrings/kismet-archive-keyring.gpg >/dev/null
echo 'deb [signed-by=/usr/share/keyrings/kismet-archive-keyring.gpg] https://www.kismetwireless.net/repos/apt/release/plucky plucky main' | sudo tee /etc/apt/sources.list.d/kismet.list >/dev/null
sudo apt update
sudo apt install kismet

# se ainda não tem, instale também:
sudo apt install -y iw
```

Depois, execute com:
```bash
# Descubra sua interface de rede:
iw dev

# Execute o Kismet
sudo kismet -c wlan0  # Substitua wlan0 pela sua interface
```

> Agora, acesse [localhost:2501](http://localhost:2501), configure seu usuário e inicie a exploração.


## Utilizando

*No geral, para usar, no MEU Ubuntu, eu uso:*
```bash
# Ver dados da sua interface
sudo lshw -C network

INTERFACE=wlp2s0

# Ativar modo monitor
sudo ip link set $INTERFACE down
sudo iw dev $INTERFACE set type monitor
sudo ip link set $INTERFACE up

sudo kismet -c $INTERFACE

# Desativar modo monitor
sudo ip link set $INTERFACE down
sudo iw dev $INTERFACE set type managed
sudo ip link set $INTERFACE up

# Liberar serviços
sudo rfkill unblock wifi
sudo rfkill unblock all
sudo airmon-ng check kill


# Reiniciar serviço de rede
sudo systemctl restart NetworkManager
# Reiniciar Drivers, se ainda não voltar o wifi
sudo modprobe -r iwlwifi
sudo modprobe iwlwifi
```
