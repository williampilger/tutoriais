# EXEMPLO: Criando uma instância de banco de dados "portátil"

É relativamente portátil. Ainda precisará manipular algumas coisas para colocar o negócio para rodar.

- Será necessário o Backup de duas "Partes"
  - **Imagem** (obrigatório apenas se a versão do MySQL tiver sido atualizada, por exemplo)
    - Isso acaba sendo necessário quase sempre, pois as pequenas atualizações do software já impede a restauração da imagem automaticamente (e sem muita mão-de-obra).
  - **Volume de Armazenamento**
    - O MySQL salva o banco em uma pasta no container. Então se coloca (e por padrão já é assim) em um volume gerenciado pelo Docker. Isso garante a portailidade do servidor sem depender de plataforma.
    - Outra alternativa, é mapear o diretório do MySQL para uma pasta local, assim, você leva sua pasta, e depois só coloca o servidor para rodar montando a pasta.

**PS.:** *Eu usei nomes de exemplo, e não os identifiquei, pois este tutorial **não** é para um iniciante no docker.*

---

## Restaurar o Backup / Retomar a instância

- Restaurando o **Volume**:
      - Criar o volume:
          - ```sh
            docker volume create mysql-dev-volume
            ```
      - Popular o volume:
          - ```sh
            docker run --rm \
              -v "mysql-dev-volume":/restore-volume \
              -v "$(pwd)":/backup \
              busybox \
              tar -zxvf /backup/db-backup.tar.gz -C /restore-volume
            ``` 
- Restaurando a **Imagem** criada (opcional (nem tanto)):
    - ```sh
      docker load -i DOCKER_IMAGE_mysql-dev.tar"
      ```
- Executando o Container pela **primeira vez**:
    - Usando a **Imagem Salva/Criada**:
        - ```sh
          docker run -d \
            --name mysql-dev \
            -v "mysql-dev-volume":/var/lib/mysql \
            -e MYSQL_ROOT_PASSWORD=password \
            -p 3306:3306 \
            mysql-dev:backup
          ```
    - **ou,** usando a **Imagem genérica**:
        - ```sh
          docker run -d \
            --name mysql-dev \
            -v "mysql-dev-volume":/var/lib/mysql \
            -e MYSQL_ROOT_PASSWORD=password \
            -p 3306:3306 \
            mysql:latest
          ```
- Executando o container pela segunda vez:
    - ```sh
      docher start mysql-dev
      ```

Será possível acessa-lo usando:

> mysql -h 127.0.0.1 -u root -P password


---

## Criação do backup

Caso você esteja iniciando seu servidor agora, e queira criar uma instância vazia, execute também:
```
docker run --name mysql-dev -e MYSQL_ROOT_PASSWORD=password -p 3306:3306 -d mysql:latest
```

**Executando o Backup** (depois de ter o banco de dados no estado em que se quer o backup)

- Do **Volume**
    - ```sh
      docker run --rm \
          -v "mysql-dev-volume":/backup-volume \
          -v "$(pwd)":/backup \
          busybox \
          tar -zcvf /backup/db-backup.tar.gz -C /backup-volume .
      ```
- Do **Container**:
    - ```sh
      docker commit mysql-dev mysql-dev:backup
      docker save -o DOCKER_IMAGE_mysql-dev.tar mysql-dev:backup
      ```


