# Docker Compose

O treco serve pra iniciar vários containers de forma coordenada, para que em apenas um comando todos os containers estejam rodando adequadamente.

Para tal, você deve criar um arquivo com o nome e diretório adequados:

*YMLS/docker-compose.yml*
```yml
version: "3.9"
services:
  mongodb:
    image: mongo:4.4.6
    container_name: meu-mongo
    networks:
      - compose-bridge
  alurabooks:
    image: aluradocker/alura-books:1.0
    container_name: alurabooks
    networks:
      - compose-bridge
    ports:
      - 3000:3000
    depends_on:
      - mongodb
networks:
  compose-bridge:
    driver: bridge
```

Para executar a aplicação como um todo, você pode executar:
> docker-compose up

ou
> docker-compose up -d

para não manter o terminal travado.

E para parar todo o conjunto:
> docker-compose down
