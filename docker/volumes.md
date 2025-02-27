# Trabalhando com Volumes

Volumes são como unidades removíveis ou fixas.

---

## Criando e Usando um Volume

Criar um volume:
```sh
docker volume create your-volume
```

Você pode usar um container temporário para copiar dados entre volumes, por exemplo:
```sh
docker run --rm -it \
  -v volume-destino:/origem \
  -v volume-destino:/destino \
  ubuntu bash -c "cp -a /origem/. /destino/"
```

Usando o volume para um container:
```sh
docker run -d \
    --name meu-container \ # opcional
    -v meu_volume_db:/var/lib/mysql \ # EXEMPLO: Caminho `/var/lib/mysql` é o caminho de montagem quando for executar um banco MySQL com um volume
    -e MYSQL_ROOT_PASSWORD=sua_senha \ # EXEMPLO: Variável de ambiente
    mysql:latest # EXEMPLO: use sua imagem aqui
```

---

## Salvando / Copiando / Restaurando um Volume

Bom, volumes nada mais são que pastas normais dentro do seu sistema de arquivos, você pode compactar ele e restaurar normalmente.

Criando um arquivo de backup:
```sh
VOLUME_NAME="my-volume"
docker run --rm \
      -v "$VOLUME_NAME":/backup-volume \
      -v "$(pwd)":/backup \
      busybox \ # Lembrando que você pode usar qualquer imagem que tenha o comando tar
      tar -zcvf /backup/my-backup.tar.gz /backup-volume
```
Restaurando o backup:
```sh
VOLUME_NAME="my-volume"
docker run --rm \
    -v "$VOLUME_NAME":/restore-volume \
    -v "$(pwd)":/backup \
    busybox \
    tar -zxvf /backup/my-backup.tar.gz -C /restore-volume
```

---

## Sobre

By: **William Pilger** | github.com/williampilger

2025/02/24 11:53 | Bom Princípio - RS - Brasil
