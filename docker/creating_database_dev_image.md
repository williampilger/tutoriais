# Criar uma Container para executar um banco de dados de desenvolvimento

No título, chamei de 'container', pois criaremos um banco de dados que podemos ficar retomando e continuar desenvolvendo. A imagem que utilizaremos não terá nada de mais.

Também veremos como salvar a imagem e continuar sua execução em outra máquina sem perder os dados, e sem trabalhar com concentos diferentes dos "convencionais" quando falamos em containeres.

(se você não percebeu, estamos falando em levar um `container` para outra máquina, não uma `imagem`, como se faz tradicionalmente)


---

## 'Instalando' a ferramenta para Criar/Recuperar o Backup

Em um futuro próximo, pretendo transformar isso em um software.
Atualmente, o funiconamento está limitado para **Linux** (testado em Ubuntu-based apenas).

### 📌 **Como usar:**
- **Criar um backup:**  
  ```sh
  ./backup_docker.sh save nome_ou_id_do_container
  ```
  - Gera um arquivo `backup_nome_do_container.dockerbk`
  
- **Restaurar um backup:**  
  ```sh
  ./backup_docker.sh load backup_nome_do_container.dockerbk
  ```
  
### 📜 **Script: `backup_docker.sh`**
Salve o conteúdo abaixo como `backup_docker.sh` e dê permissão de execução:
```sh
chmod +x backup_docker.sh
```

*/bin/backup_docker.sh*
```sh
#!/bin/bash

# Verifica argumentos
if [ "$#" -lt 2 ]; then
    echo "Uso: $0 save|load <container_id|container_name> (ou arquivo de backup para load)"
    exit 1
fi

ACTION=$1
CONTAINER=$2
BACKUP_DIR="./docker_backup"
EXT=".dockerbk"

mkdir -p "$BACKUP_DIR"

if [ "$ACTION" == "save" ]; then
    # Obtém o nome real do container
    CONTAINER_NAME=$(docker inspect --format='{{.Name}}' "$CONTAINER" 2>/dev/null | sed 's/^\/\+//')
    if [ -z "$CONTAINER_NAME" ]; then
        echo "Container '$CONTAINER' não encontrado."
        exit 1
    fi

    BACKUP_FILE="$BACKUP_DIR/backup_${CONTAINER_NAME}${EXT}"
    
    # Obtém os volumes do container
    VOLUMES=$(docker inspect --format='{{range .Mounts}}{{.Source}} {{end}}' "$CONTAINER")
    
    echo "📦 Criando backup do container '$CONTAINER_NAME'..."
    
    # Salva a imagem do container
    docker commit "$CONTAINER" "$CONTAINER_NAME:backup"
    docker save -o "$BACKUP_DIR/$CONTAINER_NAME.tar" "$CONTAINER_NAME:backup"

    # Compacta volumes
    TAR_CMD="tar czf \"$BACKUP_DIR/$CONTAINER_NAME-volumes.tar.gz\""
    for VOL in $VOLUMES; do
        if [ -d "$VOL" ]; then
            TAR_CMD="$TAR_CMD -C \"$VOL\" ."
        fi
    done
    eval "$TAR_CMD"

    # Junta tudo em um único arquivo
    zip -j "$BACKUP_FILE" "$BACKUP_DIR/$CONTAINER_NAME.tar" "$BACKUP_DIR/$CONTAINER_NAME-volumes.tar.gz"
    
    # Limpa arquivos temporários
    rm -f "$BACKUP_DIR/$CONTAINER_NAME.tar" "$BACKUP_DIR/$CONTAINER_NAME-volumes.tar.gz"
    
    echo "✅ Backup salvo em: $BACKUP_FILE"

elif [ "$ACTION" == "load" ]; then
    BACKUP_FILE="$CONTAINER"
    
    if [ ! -f "$BACKUP_FILE" ]; then
        echo "Arquivo de backup '$BACKUP_FILE' não encontrado."
        exit 1
    fi

    echo "🔄 Restaurando backup de '$BACKUP_FILE'..."
    
    # Extrai os arquivos do backup
    unzip -o "$BACKUP_FILE" -d "$BACKUP_DIR"
    
    CONTAINER_NAME=$(basename "$BACKUP_FILE" "$EXT" | sed 's/backup_//')
    
    # Restaura a imagem do container
    docker load -i "$BACKUP_DIR/$CONTAINER_NAME.tar"
    
    # Cria volume e restaura os dados
    docker volume create "$CONTAINER_NAME-data"
    tar xzf "$BACKUP_DIR/$CONTAINER_NAME-volumes.tar.gz" -C "/var/lib/docker/volumes/$CONTAINER_NAME-data/_data"
    
    # Inicia o container restaurado
    docker run --name "$CONTAINER_NAME" -d -p 3306:3306 -v "$CONTAINER_NAME-data:/var/lib/mysql" "$CONTAINER_NAME:backup"
    
    # Limpa arquivos temporários
    rm -f "$BACKUP_DIR/$CONTAINER_NAME.tar" "$BACKUP_DIR/$CONTAINER_NAME-volumes.tar.gz"
    
    echo "✅ Restauração concluída. Container '$CONTAINER_NAME' está rodando."
else
    echo "Ação inválida. Use 'save' ou 'load'."
    exit 1
fi
```




## Criando um Container com a Imagem defauld

```sh
MYSQL_ROOT_PASSWORD="password"

docker run --name meu-banco -e MYSQL_ROOT_PASSWORD=$MYSQL_ROOT_PASSWORD -p 3306:3306 -d mysql:latest
```

Agora, acesse seu banco:

> mysql -h 127.0.0.1 -u root -p

Por curiosidade, você pode importar um backup executando:

> mysql -h 127.0.0.1 -u root -p DATABASE_NAME < 'your_backup.sql'


## Salvando o container e movendo para outra máquina

Para mover esse container para outra máquina sem perder os dados, podemos fazer um commit e salvar como uma imagem temporária:

```sh
docker commit meu-banco meu-banco:backup
```

Depois, podemos exportar essa imagem:

```sh
docker save -o meu-banco.tar meu-banco:backup
```

No outro computador, basta importar a imagem:

```sh
docker load -i meu-banco.tar
```

Agora, podemos rodar o container novamente:

```sh
docker run --name meu-banco -p 5432:5432 -d meu-banco:backup
```

Dessa forma, mantemos o estado do banco de dados sem precisar configurar novamente.
