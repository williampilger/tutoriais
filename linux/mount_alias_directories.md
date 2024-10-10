# Criando Atalhos ou Pontos de Montagem Simbólicos no Linux

Existem duas formas de fazer algo do tipo.

No caso do `mount` a pasta destino precisa existir, e o CONTEÙDO da pasta de origem será montado dentro da pasta destino.

No `ln` se cria literalmente um atalho.



## Mount --bind

Serve para montar um diretório fictício com o conteúdo de outro diretório.

```sh
mount --bind /caminho/com/nome/muito/grande /pasta-curta
```

Para desfazer:

```sh
umount /pasta-curta
```

*PS: Em diretórios como a raiz do sistema, será necessário executar como root.*





## ln -s

Serve para criar um atalho de uma pasta

```sh
ln -s /caminho/com/nome/muito/grande /pasta-curta
```

Para desfazer:

```sh
rm /pasta-curta
```

