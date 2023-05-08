# GitLab localserver configuration sample

On this sample, we show you how to configurate a local server to GitLab.

I have used `Ubuntu Server 20.04 LTS` distro.

```sh
sudo su

server_ip='192.168.0.20' #inform the static IP fot yout server
server_gateway='192.168.0.1' #inform the static subnet mask

apt update
sudo apt -y upgrade

apt install -y openssh-server net-tools
service ssh start

#CONFIGURAÇÕES DE REDE
cp /etc/netplan/00-installer-config.yaml /etc/netplan/00-installer-config.yaml.bkp
echo "
network:
  ethernets:
    eth0:
      dhcp4: true
      addresses: [${server_ip}/24]
      gateway4: ${server_gateway}
  version: 2
" > /etc/netplan/00-installer-config.yaml
netplan apply #aplica nova política de IP


```
