# Criar uma Container para executar um banco de dados de desenvolvimento

No título, chamei de 'container', pois criaremos um banco de dados que podemos ficar retomando e continuar desenvolvendo. A imagem que utilizaremos não terá nada de mais.

Também veremos como salvar a imagem e continuar sua execução em outra máquina sem perder os dados, e sem trabalhar com concentos diferentes dos "convencionais" quando falamos em containeres.

(se você não percebeu, estamos falando em levar um `container` para outra máquina, não uma `imagem`, como se faz tradicionalmente)


---


## Criando um Container com a Imagem defauld

```sh
MYSQL_ROOT_PASSWORD="password"

docker run --name meu-banco -e MYSQL_ROOT_PASSWORD=$MYSQL_ROOT_PASSWORD -p 3306:3306 -d mysql:latest
```

Agora, acesse seu banco:

> mysql -h 127.0.0.1 -u root -p

Por curiosidade, você pode importar um backup executando:

> mysql -h 172.0.0.1 -u root -P password -i 'your_backup.sql'


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
