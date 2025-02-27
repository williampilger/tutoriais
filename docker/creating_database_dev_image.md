# EXEMPLO: Criando uma instância de banco de dados "portátil"

É relativamente portátil. Ainda precisará manipular algumas coisas para colocar o negócio para rodar.

Outra alternativa, é mapear o diretório do MySQL para uma pasta local, assim, você leva sua pasta, e depois só coloca o servidor para rodar montando a pasta.

Mas, eu trabalharei com **Volumes do Docker**, inclusive para permitir migrações entre sistemas operacionais.


---

## Retomar a instância

Bom, para executar novamente um container parado com os passos do item **Criação da Instância** concluídos, basta:

> docher start mysql-dev

E acessa-lo usando:

> mysql -h 127.0.0.1 -u root -P password


---

## Criação da Instância

Criando o volume:
> docker volume create mysql-dev-volume

Fazendo um novo backup:
```sh
docker run --rm \
    -v "mysql-dev-volume":/backup-volume \
    -v "$(pwd)":/backup \
    busybox \
    tar -zcvf /backup/db-backup.tar.gz -C /backup-volume .
```

Restaurando o backup:
```sh
docker run --rm \
    -v "mysql-dev-volume":/restore-volume \
    -v "$(pwd)":/backup \
    busybox \
    tar -zxvf /backup/db-backup.tar.gz -C /restore-volume
```

Executando o container pela primeira vez:
```sh
docker run -d \
    --name mysql-dev \
    -v "mysql-dev-volume":/var/lib/mysql \
    -e MYSQL_ROOT_PASSWORD=password \
    -p 3306:3306 \
    mysql:latest
```
