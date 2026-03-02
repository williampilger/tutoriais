# EXEMPLO: Criando uma instância de banco de dados PostgreSQL "portátil"

É relativamente portátil. Ainda precisará manipular algumas coisas para colocar o negócio para rodar.

- Será necessário o Backup de duas "Partes"
  - **Imagem** (obrigatório apenas se a versão do PostgreSQL tiver sido atualizada)
    - Na prática, quase sempre necessário, pois atualizações menores do Postgres podem impedir a restauração automática do volume.
  - **Volume de Armazenamento**
    - O PostgreSQL salva o banco em `/var/lib/postgresql/data` dentro do container. Colocamos isso em um volume gerenciado pelo Docker para garantir portabilidade.
    - Alternativa: mapear para uma pasta local com `-v ./pgdata:/var/lib/postgresql/data`.

**PS.:** *Usei nomes de exemplo e não os identifiquei, pois este tutorial **não** é para iniciantes em Docker.*

---

## Criação do servidor (antes do primeiro backup)

Caso você esteja iniciando seu servidor agora, e queira criar uma instância vazia, execute:

> ⚠️ Diferente do MySQL, o PostgreSQL **exige POSTGRES_DB**, se não ele cria um banco de dados com o mesmo nome de User.  

```sh
docker volume create pg-dev-volume

docker run -d \
  --name pg-dev \
  -e POSTGRES_USER=postgres \
  -e POSTGRES_PASSWORD=password \
  -e POSTGRES_DB=portal_transparencia \
  -p 5432:5432 \
  -v pg-dev-volume:/var/lib/postgresql/data \
  postgres:16
```
```ps1
# Microsoft PowerShell
docker volume create pg-dev-volume

docker run -d `
  --name pg-dev `
  -e POSTGRES_USER=postgres `
  -e POSTGRES_PASSWORD=password `
  -e POSTGRES_DB=portal_transparencia `
  -p 5432:5432 `
  -v "pg-dev-volume:/var/lib/postgresql/data" `
  postgres:16
```

Para acessar o servidor pelo terminal:
```bash
psql -h 127.0.0.1 -U postgres -d portal_transparencia
```
> Será solicitada a senha configurada em `POSTGRES_PASSWORD`.

> o pacote `postgresql-client` precisa estar instalado no seu Linux (se for seu caso)

Ou, de dentro do container:
```bash
docker exec -it pg-dev psql -U postgres -d portal_transparencia
```

Criando o básico do(s) banco(s) e usuário(s):
```sql
-- Criar banco (se ainda não existir)
CREATE DATABASE portal_transparencia;

-- Criar usuário da aplicação
CREATE USER app_user WITH PASSWORD 'password';

-- Conceder permissões ao usuário
GRANT SELECT, INSERT, UPDATE, DELETE ON ALL TABLES IN SCHEMA public TO app_user;

-- Garantir que tabelas futuras também receberão as permissões
ALTER DEFAULT PRIVILEGES IN SCHEMA public
  GRANT SELECT, INSERT, UPDATE, DELETE ON TABLES TO app_user;

-- OU, para conceder tudo (não recomendado em produção):
-- GRANT ALL PRIVILEGES ON DATABASE portal_transparencia TO app_user;
```

---

## Criação do backup

**Executando o Backup** (depois de ter o banco de dados no estado em que se quer o backup)

### Backup Lógico (recomendado — portátil entre versões)

```sh
# Linux — Gera um arquivo .sql com todo o banco
docker exec pg-dev pg_dump -U postgres portal_transparencia > db-backup.sql
```
```ps1
# Microsoft PowerShell
docker exec pg-dev pg_dump -U postgres portal_transparencia | Out-File -Encoding utf8 db-backup.sql
```

> Use `pg_dumpall` se quiser exportar **todos** os bancos e roles:
> ```sh
> docker exec pg-dev pg_dumpall -U postgres > db-backup-all.sql
> ```

### Backup do Volume (cópia binária dos dados)

- ```sh
  # Linux
  docker run --rm \
    -v "pg-dev-volume":/backup-volume \
    -v "$(pwd)":/backup \
    busybox \
    tar -zcvf /backup/db-backup.tar.gz -C /backup-volume .
  ```
- ```ps1
  # Microsoft PowerShell
  docker run --rm `
    -v "pg-dev-volume:/backup-volume" `
    -v "${PWD}:/backup" `
    busybox `
    tar -zcvf /backup/db-backup.tar.gz -C /backup-volume .
  ```

### Backup da Imagem do Container

```sh
docker commit pg-dev pg-dev:backup
docker save -o DOCKER_IMAGE_pg-dev.tar pg-dev:backup
```

---

## Restaurar o Backup / Retomar a instância

### Restaurando pelo Backup Lógico (.sql)

1. Crie um container vazio (como na seção de criação acima)
2. Restaure o banco:
    ```sh
    # Linux
    cat db-backup.sql | docker exec -i pg-dev psql -U postgres -d portal_transparencia
    ```
    ```ps1
    # Microsoft PowerShell
    Get-Content db-backup.sql | docker exec -i pg-dev psql -U postgres -d portal_transparencia
    ```

### Restaurando pelo Volume

1. Criar o volume:
    ```sh
    docker volume create pg-dev-volume
    ```

2. Popular o volume:
    - ```sh
      # Linux
      docker run --rm \
        -v "pg-dev-volume":/restore-volume \
        -v "$(pwd)":/backup \
        busybox \
        tar -zxvf /backup/db-backup.tar.gz -C /restore-volume
      ```
    - ```ps1
      # Microsoft PowerShell
      docker run --rm `
        -v "pg-dev-volume:/restore-volume" `
        -v "${PWD}:/backup" `
        busybox `
        tar -zxvf /backup/db-backup.tar.gz -C /restore-volume
      ```

### Restaurando a Imagem criada

```sh
docker load -i DOCKER_IMAGE_pg-dev.tar
```

### Executando o Container pela primeira vez

- Usando a **Imagem Salva/Criada**:
    - ```sh
      # Linux
      docker run -d \
        --name pg-dev \
        -v "pg-dev-volume":/var/lib/postgresql/data \
        -e POSTGRES_PASSWORD=password \
        -p 5432:5432 \
        pg-dev:backup
      ```
    - ```ps1
      # Microsoft PowerShell
      docker run -d `
        --name pg-dev `
        -v "pg-dev-volume:/var/lib/postgresql/data" `
        -e POSTGRES_PASSWORD=password `
        -p 5432:5432 `
        pg-dev:backup
      ```

- **ou,** usando a **Imagem genérica**:
    - ```sh
      # Linux
      docker run -d \
        --name pg-dev \
        -v "pg-dev-volume":/var/lib/postgresql/data \
        -e POSTGRES_PASSWORD=password \
        -p 5432:5432 \
        postgres:16
      ```
    - ```ps1
      # Microsoft PowerShell
      docker run -d `
        --name pg-dev `
        -v "pg-dev-volume:/var/lib/postgresql/data" `
        -e POSTGRES_PASSWORD=password `
        -p 5432:5432 `
        postgres:16
      ```

- Executando o container pela segunda vez:
    ```sh
    docker start pg-dev
    ```

- Caso você queira que o container inicie automaticamente junto com a máquina/docker:
    ```sh
    docker update --restart=unless-stopped pg-dev
    ```
    - Lembrando que:
        - `unless-stopped`: Sempre que não for parado manualmente
        - `on-failure`: Quando o container falhar
        - `always`: Sempre
        - `no`: Padrão — Nunca
    - Você pode adicionar essa flag no início também!

Será possível acessá-lo usando:
```bash
psql -h 127.0.0.1 -U postgres -d portal_transparencia
```

---

## Extra: Ativar e acompanhar LOGs do PostgreSQL em tempo real

O PostgreSQL já registra logs por padrão. Para acompanhar em tempo real:

```bash
docker logs -f pg-dev
```

Para ativar logs mais detalhados (todas as queries), acesse o `psql` e execute:
```sql
ALTER SYSTEM SET log_statement = 'all';
SELECT pg_reload_conf();
```

Para verificar a configuração atual:
```sql
SHOW log_statement;
SHOW log_directory;
SHOW log_filename;
```

Para desativar depois:
```sql
ALTER SYSTEM SET log_statement = 'none';
SELECT pg_reload_conf();
```

> **Dica:** Diferente do MySQL, o PostgreSQL não precisa de `FLUSH PRIVILEGES`. Alterações de permissão são aplicadas imediatamente. As configurações de sistema (`ALTER SYSTEM`) requerem um `pg_reload_conf()` ou restart.

---

## Extra: Comandos úteis do psql

| Comando | Descrição |
|---------|-----------|
| `\l` | Listar todos os bancos de dados |
| `\c nome_do_banco` | Conectar a outro banco |
| `\dt` | Listar tabelas do schema atual |
| `\d nome_tabela` | Descrever estrutura de uma tabela |
| `\du` | Listar usuários/roles |
| `\dn` | Listar schemas |
| `\q` | Sair do psql |
| `\x` | Alternar exibição expandida (vertical) |
| `\timing` | Ativar/desativar exibição do tempo de execução |

---

## Sobre

By: William Pilger | github.com/williampilger

2026-03-02 | Baseado no tutorial equivalente para MySQL
