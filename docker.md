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
