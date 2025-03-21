# Comandos básicos

| Comando | Função | Exemplo |
| --- | --- | --- |
| `docker run` | Criar um container com base em uma imagem | `docker run hello-world` |
| `docker run -d` | Cria um container ... Detachd - Inicia SEM travar o terminal no containet | `docker run -d hello-world` |
| `docker run -p` | Cria um container ... fazendo mapeamento de portas | `docker run -p 8080:3000 hello-world` |
| `docker run -it` | Cria um container ... em modo interativo (terminal aberto) | `docker run -it ubuntu bash` |
| `docker run -P` | Cria um container ... atribuindo as portas automaticamente (aleatórias) | `docker run -P hello-world` |
| `docker run -v` | Criar um container ... Montando uma pasta local no container | `docker run -v /home/user/sample:sample -it ubuntu` |
| `docker run --mount` | Criar um container ... Montando uma pasta local no container | `docker run --mount type=bind,source=/home/user/sample,target=/sample -it ubuntu` |
| `docker run --mount` | Criar um container ... Montando uma pasta local no container, usando volumes gerenciados pelo docker | `docker run --mount source=novo-volume,target=/sample -it ubuntu` |
| `docker run --tmpfs` | Criar um container ... montando um diretório temporário (útil para criar um diretório de arquivos temporários que não estará na camada de read/write do container) | `docker run --tmpfs=/tempdir -it ubuntu` |
| `docker run --name NAME` | Criar um container ... Definindo um nome manual para o container | `docker run --name ubuntu-server-1 -it ubuntu` |
| `docker run --network NAME` | Criar um container ... Definindo uma interface de rede | `docker run -it --name ubuntu-server-1 --network minha-rede-exemplo ubuntu` |
| `docker container rm` | Remove um container específico | `docker container rm 11dd643585s45` |
| `docker container ls` | Listar containers | `docker container ls` |
| `docker container ls -a` | Listar containers, incluindo parados | `docker container ls -a` |
| `docker rmi` | Excluir uma imagem | `docker rmi 954565d84ddd8` |
| `docker rmi --force` | Excluir uma imagem, mesmo que ela esteja sendo usada | `docker rmi --force 954565d84ddd8` |
| `docker ps` | Lista os containers rodando | `docker ps` |
| `docker ps -s` | Lista containers, incluindo o tamanho dele | `docker ps -s` |
| `docker ps -a` | Lista containers, incluindo os parados | `docker ps -sa` |
| `docker volume ls` | Lista os volumes gerenciados pelo docker | `docker volume ls` |
| `docker volume create` | Criar um novo volume gerenciado | `docker volume create meu-volume-novo` |
| `docker inspect` | Inspeciona um container (apresenta dados do container) | `docker inspect 3977e4012729` |
| `docker network ls` | Lista as conexões de rede disponíveis | `docker network ls` |
| `docker network create` | Criar uma interface de rede breadge | `docker network create --help` para ver mais |
| `docker network create --driver bridge` | Criar uma interface de rede bridge | `docker network create --driver bridge minha-rede-exemplo` |
| `docker logs -f <container_name>` | Exibir logs do container. o `-f` acompanha em tempo real os LOGs. | `docker logs -f mysql-dev` |

## Combinações úteis

*Excluir todas as imagens*
```sh
docker rmi $(docker image ls -aq)
```

*Excluir todas os containers*
```sh
docker container rm $(docker container ls -aq)
```

*Parar o ÙNICO container rodando*
```sh
docker stop $(docker ps -q)
```

*Criar container "reutilizável" pra rodar Linux no Windows melhor que o WSL 😅*
```bat
# Primeira rodada
cd %userprofile% #navegue até o ponto onde dezeja montar no ubuntu
docker run -v ".:/media/windows" --network host --name meu-ubuntu -it ubuntu

# Proximas Rodadas
docker start meu-ubuntu
docker exec -it meu-ubuntu /bin/bash
```
