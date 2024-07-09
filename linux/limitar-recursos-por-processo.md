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


## Definir afinidade de Núcleos

Iniciar um processo com afinidade de núcleo(s):
```sh
taskset -c 0,1 seu_processo # Núcleos 0 e 1
```

Definir a afinidade de núcleos para um processo em andamento:
```sh
taskset -cp 0,1 $PID
# OU
taskset -p 0x3 $PID
# OU
taskset -p 0b11 $PID
```

Para verificar a afinidade de um processo:
> taskset -cp $PID

