# Montar Unidades Físicas no sistema de arquivos

Este turorial se aplica a discribuições baseadas no `Ubuntu`.


## 🔐 Desproteger unidade Criptografada com senha

Para desbloquear a unidade use (observer que o nome do sipositivo pode variar):
> sudo cryptsetup luksOpen /dev/sda1 NOME_DE_MONTAGEM

Pode ser necessário instalar algo (quase nunca):
> sudo apt update && sudo apt install cryptsetup


## 💽 Montar uma unidade (normal ou criptografada)

```sh
DEVICE="/dev/mapper/sda1"
MOUNT_DIR="/media/user/data"
sudo mount $DEVICE $MOUNT_DIR
```


---

# Sobre

Curiosidades
- [Problema ao montar unidade criptografada](https://unix.stackexchange.com/questions/552915/mount-fail-unknown-filesystem-type-crypto-luks);


By: williampilger | 25.05.26
