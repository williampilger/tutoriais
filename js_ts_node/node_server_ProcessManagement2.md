# Servidor Node - Colocar Apps em Produção com PM2

Este tutorial é para quem **já entende de Node, e já sabe colocar um app para rodar da forma tradicional!**

Com suas dependências já instaladas, e a aplicação **já totalmente funcional**, sendo capaz de roda o servidor **já com a versão otimizada para produção** (ou seja, você já deu um npm run build, e já tem ela compilada).

Instale as dependências (`Linux`, obviamente):

```bash
sudo npm install pm2 -g
```

E, estando no diretório adequado, coloque a aplicação para rodar:

```bash
APP_NAME="sample-name"
pm2 start npm --name $APP_NAME -- start
```

Não preciso dizer que você não precisa usar a variável, se não quiser...
