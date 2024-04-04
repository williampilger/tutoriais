# Montar Unidades Físicas no sistema de arquivos

Este turorial se aplica a discribuições baseadas no `Ubuntu`.


## Desproteger unidade Criptografada com senha

Para desbloquear a unidade use (observer que o nome do sipositivo pode variar):
> sudo cryptsetup luksOpen /dev/sda1 NOME_DE_MONTAGEM

Pode ser necessário instalar algo (quase nunca):
> sudo apt update && sudo apt install cryptsetup


## Montar uma unidade normal

```sh
DEVICE="NOME_DE_MONTAGEM"
MOUNT_DIR="/media/user/data"
sudo mount /dev/mapper/$DEVICE $MOUNT_DIR
```
