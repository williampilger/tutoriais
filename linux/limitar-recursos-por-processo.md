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


# Definir afinidade de Núcleos

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



# Alterar a prioridade de um ou mais processos (alterar o `nice` do processo)

O valor de `nice` nos processos em um sistema linux varia de `-19` (mais prioritário) a `20` (menor prioridade);

Alterar o valor da prioridade de um processo:
> $ sudo renice 10 -p <PID>

Onde `10` é o novo valor de prioridade.
Use `renice --help` para saber mais.

### Alterar a prioridade de vários processos:

Você pode usar a função `pgrep` para filtrar os processos por nome, e em seguida combiná-lo com `xatgs` para alterar a prioridade de vários processos. Veja um exemplo mudando a prioridade dos processos do google chrome:
> pgrep chrome | xargs sudo renice 10 -p

