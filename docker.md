# Docker

Esse arquivo resume o que se precisa saber para começar com Docker

## Comandos básicos

| Comando | Função | Exemplo |
| --- | --- | --- |
| `docker run` | Criar um container com base em uma imagem | `docker run hello-world` |
| `docker run -d` | Cria um container ... Detachd - Inicia SEM travar o terminal no containet | `docker run -d hello-world` |
| `docker run -p` | Cria um container ... fazendo mapeamento de portas | `docker run -p 8080:3000 hello-world` |
| `docker run -P` | Cria um container ... atribuindo as portas automaticamente (aleatórias) | `docker run -P hello-world` |
| `docker run` | Criar um container com base em uma imagem | `docker run hello-world` |
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
| `` |  | `` |

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

