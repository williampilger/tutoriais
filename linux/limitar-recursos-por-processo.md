# Limitar o uso de recursos por PID

Pode ser necessário instalar o comando:

> sudo apt install util-linux

O comando para limitar fica semelhante a isso:

```sh
sudo prlimit --pid $PID --cpu=60 --rss=524288
# Nesse caso:
#    CPU limitada a 60%
#    Memória em 512MB
```
