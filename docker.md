# Docker

Esse arquivo resume o que se precisa saber para começar com Docker

## Comandos básicos

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
| `docker container rm $(docker container ls -aq)` | Remover todos os containers | `docker container rm $(docker container ls -aq)` |
| `docker container ls` | Listar containers | `docker container ls` |
| `docker container ls -a` | Listar containers, incluindo parados | `docker container ls -a` |
| `docker rmi` | Excluir uma imagem | `docker rmi 954565d84ddd8` |
| `docker rmi --force` | Excluir uma imagem, mesmo que ela esteja sendo usada | `docker rmi --force 954565d84ddd8` |
| `docker rmi $(docker image ls -aq)` | Excluir todas as imagens | `docker rmi $(docker image ls -aq)` |
| `docker ps` | Lista os containers rodando | `docker ps` |
| `docker ps -s` | Lista containers, incluindo o tamanho dele | `docker ps -s` |
| `docker ps -a` | Lista containers, incluindo os parados | `docker ps -sa` |
| `docker volume ls` | Lista os volumes gerenciados pelo docker | `docker volume ls` |
| `docker volume create` | Criar um novo volume gerenciado | `docker volume create meu-volume-novo` |
| `docker inspect` | Inspeciona um container (apresenta dados do container) | `docker inspect 3977e4012729` |
| `docker network ls` | Lista as conexões de rede disponíveis | `docker network ls` |
| `docker network create` | Criar uma interface de rede breadge | `docker network create --help` para ver mais |
| `docker network create --driver bridge` | Criar uma interface de rede bridge | `docker network create --driver bridge minha-rede-exemplo` |
| `` |  | `` |
| `` |  | `` |
| `` |  | `` |
| `` |  | `` |



## Redes no Docker

Os containers rodando no docker podem se comunicar entre sí, estando conectados na mesma rede.
E você pode listar as redes disponíveis usando:
> docker network ls

Assim como também pode conferir emq ual rede um containter está conectado com:
> docker inspect 3977e4012729 #definindo o ID adequado...

Se pode comunicar entre os containers usando hostnames, faça isso criando primeiro uma rede nova (bom para isolar os itens. Depois Execute o container na nova rede e definindo o hostname.

> docker network create --driver bridge minha-rede-exemplo

> docker run -d --name ubuntu-1 --network minha-rede-exemplo ubuntu

Agora, se você criar mais containers na mesma rede poderá acessá-los entre sí pelo hostname.

As redes padrão do Docker tem as seguintes funcionalidades:

| NAME | Função |
| --- | --- |
| `bridge` (DEFAULT) | Coloca o container na mesma rede do host |
| `host` | O Container roda NO HOST. Ou seja a porta do container é a mesma porta do Host, e ele responde pelo mesmo IP do host |
| `none` | Container sem comunicação de rede |

## Dockerfile

```Dockerfile
FROM node:14
WORKDIR /app-node
COPY . .
RUN npm install
ENTRYPOINT npm start
```
Agora, definindo variável de ambiente para a porta a ser usada
```Dockerfile
FROM node:14
WORKDIR /app-node
ARG PORT_BUILD=6000
ENV PORT=$PORT_BUILD
EXPOSE $PORT_BUILD
COPY . .
RUN npm install
ENTRYPOINT npm start
```

