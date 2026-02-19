# Limpar o cache do DNS do sistema


## 1) Usando `systemd-resolved` (O mais comum hoje)

A maioria das distribuições modernas (Ubuntu 20.04+, Fedora, Debian recente) utiliza o `systemd-resolved`.

*Para limpar*
```bash
sudo resolvectl flush-caches
```

*Verifique se foi limpo (O tamanho do cache deve ser zero)*
```bash
sudo resolvectl statistics
```

*Ou, em sistemas mais antigos, o comando pode ser:*
```bash
sudo systemd-resolve --flush-caches
```


## 2) Usando `nscd` (Name Service Cache Daemon)

Muito utilizado em servidores ou distros mais conservadoras.

*Para limpar o cache e reiniciar o serviço*
```bash
sudo systemctl restart nscd
# ou
sudo service nscd restart
```


## 3) Usando `Dnsmasq`

O Linux está sendo usado como um roteador ou se configurou o `dnsmasq` manualmente para ganhar performance.

*Para limpar:*
```bash
sudo systemctl restart dnsmasq
```
