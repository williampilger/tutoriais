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

## Criação do servidor (antes do primeiro backup)

Caso você esteja iniciando seu servidor agora, e queira criar uma instância vazia, execute também:
```
docker run --name mysql-dev -e MYSQL_ROOT_PASSWORD=password -p 3306:3306 -d mysql:latest
```

E, para aressar ao servidor, use:
```bash
mysql -h 127.0.0.1 -u root -p
```

Criando o básico do(s) banco(s) e usuário(s):
```sql
CREATE DATABASE `sample-database`;

CREATE USER 'user'@'%' IDENTIFIED BY 'password';
GRANT SELECT, INSERT, UPDATE, DELETE ON `sample-database`.* TO 'user'@'%';
--GRANT ALL PRIVILEGES ON `sample-database`.* TO 'user'@'%';
FLUSH PRIVILEGES;
```

---

## Criação do backup

**Executando o Backup** (depois de ter o banco de dados no estado em que se quer o backup)

- Do **Volume**
    - ```sh
      # Linux
      docker run --rm \
          -v "mysql-dev-volume":/backup-volume \
          -v "$(pwd)":/backup \
          busybox \
          tar -zcvf /backup/db-backup.tar.gz -C /backup-volume .
      ```
    - ```ps1
      # Microsoft PowerShell
      docker run --rm `
        -v "mysql-dev-volume:/backup-volume" `
        -v "${PWD}:/backup" `
        busybox `
        tar -zcvf /backup/db-backup.tar.gz -C /backup-volume .
      ```
- Do **Container**:
    - ```sh
      docker commit mysql-dev mysql-dev:backup
      docker save -o DOCKER_IMAGE_mysql-dev.tar mysql-dev:backup
      ```

---

## Restaurar o Backup / Retomar a instância

- Restaurando o **Volume**:
    - Criar o volume:
        - ```sh
          docker volume create mysql-dev-volume
          ```
    - Popular o volume:
        - ```sh
          # Linux
          docker run --rm \
            -v "mysql-dev-volume":/restore-volume \
            -v "$(pwd)":/backup \
            busybox \
            tar -zxvf /backup/db-backup.tar.gz -C /restore-volume
          ```
        - ```ps1
          # Microsoft PowerShell
          docker run --rm `
            -v "mysql-dev-volume:/restore-volume" `
            -v "${PWD}:/backup" `
            busybox `
            tar -zxvf /backup/db-backup.tar.gz -C /restore-volume
          ```

          
- Restaurando a **Imagem** criada (opcional (nem tanto)):
    - ```sh
      docker load -i DOCKER_IMAGE_mysql-dev.tar"
      ```
- Executando o Container pela **primeira vez**:
    - Usando a **Imagem Salva/Criada**:
        - ```sh
          # Linux
          docker run -d \
            --name mysql-dev \
            -v "mysql-dev-volume":/var/lib/mysql \
            -e MYSQL_ROOT_PASSWORD=password \
            -p 3306:3306 \
            mysql-dev:backup
          ```
        - ```ps1
          # Microsoft PowerShell
          docker run -d `
            --name mysql-dev `
            -v "mysql-dev-volume:/var/lib/mysql" `
            -e MYSQL_ROOT_PASSWORD=password `
            -p 3306:3306 `
            mysql-dev:backup
          ```

    - **ou,** usando a **Imagem genérica**:
        - ```sh
          # Linux
          docker run -d \
            --name mysql-dev \
            -v "mysql-dev-volume":/var/lib/mysql \
            -e MYSQL_ROOT_PASSWORD=password \
            -p 3306:3306 \
            mysql:latest
          ```
        - ```ps1
          # Microsoft PowerShell
          docker run -d `
            --name mysql-dev `
            -v "mysql-dev-volume:/var/lib/mysql" `
            -e MYSQL_ROOT_PASSWORD=password `
            -p 3306:3306 `
            mysql:latest
          ```
- Executando o container pela segunda vez:
    - ```sh
      docher start mysql-dev
      ```

Será possível acessa-lo usando:

> mysql -h 127.0.0.1 -u root -P password

---

## Extra: Ativar e acompanhar LOGs do Mysql em tempo real

Existe, obviamente, outras formas de fazer isso. Mas, nesse caso, estou fazendo isso **depois do container já rodando, sem parar nada da execução**.

- Ativando o registro de LOGs e vendo onde está salvo:
  - Acesse o MySQL:
    - ```bash
      docker exec -it mysql-dev mysql -u root -p
      ```
    - Troque sua senha e nome do banco, obviamente, e digite sua senha.
  - Ative o LOG:
    - ```SQL
      SET GLOBAL general_log = 'ON';
      ```
  - Veja onde o arquivo será salvo:
    - ```SQL
      SHOW VARIABLES LIKE 'general_log_file';
      ```
    - Você deve ver algo como:
      - ```txt
        mysql> SHOW VARIABLES LIKE 'general_log_file';
        +------------------+---------------------------------+
        | Variable_name    | Value                           |
        +------------------+---------------------------------+
        | general_log_file | /var/lib/mysql/0471780b8d6e.log |
        +------------------+---------------------------------+
        1 row in set (0.116 sec)
        ```
    - Saia do MySQL com `exit;`
- Exibir e acompanhar os LOGs
  - ```bash
    docker exec -it mysql-dev tail -f /var/lib/mysql/0471780b8d6e.log
    ```
---

## Sobre

By: William Pilger | github.com/williampilger

2025-03-03 09:50:23 | Mariluz - RS - Brasil


