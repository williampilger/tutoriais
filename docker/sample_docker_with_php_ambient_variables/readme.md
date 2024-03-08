# Usando variáveis de ambiente no PHP, dentro do container (Docker)

Para compilar o exemplo, execute neste diretório:
> docker build -t sample-image .

Para executar ela você pode:

- Considerando as variáveis dentro do `.env`:
  - `docker run -it -p 8080:80 --env-file .env sample-image`
- Não incluindo o `.env`:
  - `docker run -it -p 8080:80 sample-image`
- Incluindo variáveis na linha de comando:
  - `docker run -it -p 8080:80 -e TEST_VAR_FORA="Valor definido na linha de comando" sample-image`



## Sobre

Feito com *ajuda* do **ChatGPT 4.0**

[Veja a conversa aqui](https://chat.openai.com/share/0b0d0826-c311-43c5-bdfb-0d123d7a7c46)