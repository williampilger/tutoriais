# Servidor Node - Colocar Apps em Produção com PM2

Este tutorial é para quem **já entende de Node, e já sabe colocar um app para rodar da forma tradicional!**

Com suas dependências já instaladas, e a aplicação **já totalmente funcional**, sendo capaz de roda o servidor **já com a versão otimizada para produção** (ou seja, você já deu um npm run build, e já tem ela compilada).

---

### Instalando a ferramenta e configurando o Startup

Instale as dependências (`Linux`, obviamente):

```bash
sudo npm install pm2 -g
```

Para que o `pm2` seja inicializado junto com a máquina sempre, use:

```bash
# Rode o comando abaixo e COPIE E RODE O COMANDO QUE A FUNÇÂO RETORNA
pm2 startup
```

Agora, o gerenciador será sempre iniciado com o PC.
Mas, para garantir que ele sempre inicie os aplicativos que você precisa, lembre-se de rodar TAMBÉM o comando abaixo após ter iniciado sua aplicação:

```bash
pm2 save
```

Este comando salva o estado atual do MP2, e o restaura na inicialização.


---

### Iniciando a aplicação

Estando no diretório adequado, coloque a aplicação para rodar:

```bash
APP_NAME="sample-name"
pm2 start npm --name $APP_NAME -- start
```

Não preciso dizer que você não precisa usar a variável, se não quiser...

Lembre-se também que, depois de ter adicionado/removido os aplicativos que você quer que iniciem com o PC, você precisa novamente rodar:
```bash
pm2 save
```

---

### Outros Comandos - Observidade

*Ver status dos serviços rodando*
```bash
pm2 status
```

---

# Sobre

By: [William Pilger](https://github.com/williampilger)
