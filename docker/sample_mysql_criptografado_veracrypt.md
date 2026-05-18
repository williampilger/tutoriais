# EXEMPLO: MySQL portátil no Docker com volume criptografado (VeraCrypt)

Combinação de duas abordagens:
- MySQL em container Docker com dados em **bind mount** (em vez de volume gerenciado pelo Docker)
- Diretório de dados dentro de um **container VeraCrypt** (arquivo `.vc` criptografado, portátil entre Windows/macOS/Linux)

O resultado é um único arquivo `.vc` que contém todos os dados do banco, criptografado em repouso, e que pode ser copiado para qualquer máquina com VeraCrypt e Docker instalados.

**PS.:** *Este tutorial assume familiaridade com Docker e com o VeraCrypt (criação e montagem de containers). Não é voltado para iniciantes.*

**PS.2:** Serão necessários [Docker](https://github.com/williampilger/tutoriais/blob/master/linux/instalando_programas/instalando_docker.md) e [VeraCrypt](https://veracrypt.io/) instalados.

---

## Criando o container VeraCrypt

Execute uma única vez, para criar o arquivo `.vc` que guardará os dados do banco.

```bash
# Linux — cria um container VeraCrypt de 10 GB
# Será solicitada a senha interativamente
veracrypt --text --create ~/mysql-data.vc \
  --size 10G \
  --encryption AES \
  --hash SHA-512 \
  --filesystem ext4 \
  --pim 0 \
  --keyfiles "" \
  --random-source /dev/urandom
```

No **Windows**, use a interface gráfica do VeraCrypt: *Create Volume → Create an encrypted file container → Standard VeraCrypt volume* e escolha AES + SHA-512.

> Dimensione com folga. O arquivo `.vc` tem tamanho fixo e não cresce automaticamente.

---

## Montando o volume

Antes de subir o MySQL, o container VeraCrypt precisa estar montado. Faça isso toda vez que for usar o banco.

```bash
# Linux
sudo mkdir -p /mnt/mysql-data
veracrypt --text --mount ~/mysql-data.vc /mnt/mysql-data \
  --pim 0 \
  --keyfiles "" \
  --protect-hidden no
# Será solicitada a senha
```

No **Windows**, monte pela interface gráfica do VeraCrypt para uma letra de unidade livre (ex: `M:`).

---

## Subindo o MySQL (primeira vez)

Com o volume montado, suba o container apontando o bind mount para o diretório montado:

```bash
# Linux
docker run -d \
  --name mysql-dev \
  -e MYSQL_ROOT_PASSWORD=password \
  -p 3306:3306 \
  -v /mnt/mysql-data:/var/lib/mysql \
  mysql:8.0
```

```ps1
# Windows PowerShell (volume montado como M:)
docker run -d `
  --name mysql-dev `
  -e MYSQL_ROOT_PASSWORD=password `
  -p 3306:3306 `
  -v "M:/:/var/lib/mysql" `
  mysql:8.0
```

---

## Acessando e configurando o banco

```bash
mysql -h 127.0.0.1 -u root -p
```

Criando banco e usuário:
```sql
CREATE DATABASE `sample-database`;

CREATE USER 'user'@'%' IDENTIFIED BY 'password';
GRANT SELECT, INSERT, UPDATE, DELETE ON `sample-database`.* TO 'user'@'%';
FLUSH PRIVILEGES;
```

---

## Parando tudo corretamente

A ordem importa: pare o MySQL **antes** de desmontar o VeraCrypt, para evitar corrupção dos dados.

```bash
# Linux
docker stop mysql-dev
veracrypt --text --dismount /mnt/mysql-data
```

No **Windows**, desmonte pela interface gráfica do VeraCrypt após parar o container.

---

## Retomando a instância

```bash
# Linux — montar o volume e iniciar o container existente
veracrypt --text --mount ~/mysql-data.vc /mnt/mysql-data \
  --pim 0 --keyfiles "" --protect-hidden no

docker start mysql-dev
```

> **Atenção:** O container Docker (`mysql-dev`) precisa existir na máquina. Ele guarda configurações de execução (variáveis de ambiente, mapeamento de porta, bind mount), mas **não** os dados — esses estão no `.vc`. Se o container foi removido, recriar com o mesmo `docker run` da seção anterior é suficiente; os dados já estarão lá.

---

## Portabilidade / Migração para outra máquina

1. Pare o MySQL e desmonte o VeraCrypt (ver seção acima).
2. Copie o arquivo `mysql-data.vc` para a nova máquina (pen drive, nuvem, etc.).
3. Na nova máquina, com VeraCrypt e Docker instalados:
   ```bash
   # Monte o volume
   sudo mkdir -p /mnt/mysql-data
   veracrypt --text --mount ~/mysql-data.vc /mnt/mysql-data \
     --pim 0 --keyfiles "" --protect-hidden no

   # Suba o container — mesma versão do MySQL usada originalmente
   docker run -d \
     --name mysql-dev \
     -e MYSQL_ROOT_PASSWORD=password \
     -p 3306:3306 \
     -v /mnt/mysql-data:/var/lib/mysql \
     mysql:8.0
   ```

> Use a **mesma versão da imagem MySQL** que gerou os dados. Versões incompatíveis podem impedir a inicialização. Se necessário, salve também a imagem: `docker save -o mysql-dev-image.tar mysql:8.0`.

---

## Backup

O backup é simplesmente copiar o arquivo `.vc` — ele já está criptografado.

```bash
# Linux — parar tudo, depois copiar
docker stop mysql-dev
veracrypt --text --dismount /mnt/mysql-data

cp ~/mysql-data.vc ~/backups/mysql-data-$(date +%Y%m%d).vc
```

Não é necessário nenhum procedimento especial de dump SQL para o backup do volume. Guarde o arquivo `.vc` em local seguro; sem a senha, ele é ilegível.

---

## Sobre o auto-start

**Não é possível configurar restart automático** (`--restart=unless-stopped`) de forma útil neste setup, pois o container tentaria iniciar antes do volume VeraCrypt estar montado — e falharia por não encontrar os dados.

O fluxo correto sempre será manual:
1. Montar o VeraCrypt (requer senha)
2. `docker start mysql-dev`

---

## Sobre

By: William Pilger | github.com/williampilger

2026-05-18 | Mariluz - RS - Brasil
