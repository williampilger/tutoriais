# Configurando IP Estático no Ubuntu Server

A configuração de IP no Ubuntu server é feita por meio de um arquivo, do Netplan.

Acesse o diretório `/etc/netplan/`:

> cd /etc/netplan

Edite o arquivo `config.yaml` que tiver lá.

> sudo nano 00-installer-config.yaml

E você verá o seguinte arquivo (se ainda for o padrão):

```
# This is the network config written by 'subiquity'
network:
  ethernets:
    enp0s3:
      dhcp4: true
  version: 2
```

Adicione os campos de IP e gateway, como abaixo:

```
# This is the network config written by 'subiquity'
network:
  ethernets:
    enp0s3:
      dhcp4: true
      addresses: [192.168.2.250/24]
      gateway4: 192.168.2.1
  version: 2
  ```
  
  Salve as alterações, e aplique as alterações:
  
  > sudo netplan apply

Você pode verificar as alterações usando:

> sudo netplan get -ip

