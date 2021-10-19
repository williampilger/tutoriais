# Configurando o GIT via terminal

Este passo a passo é semelhante para **Windows 10**, **MAC** e **Linus**.

## Criando um par de chaves SSH

Se você já possui um, pule esta etapa. Vamos criar a seguir um par de chaves **ED25519**, que é a mais segura atualmente.

Abra um terminal e digite:

> ssh-keygen -t ed25519 -C "'< comment >"

Onde o `< comment >`é um comentário qualquer.

Você verá algo semelhante a:

```
Generating public/private ed25519 key pair.
Enter file in which to save the key (/home/wilger/.ssh/id_ed25519):
```

Sugiro que apenas confirme, a menos que queira salvá-la em outro local. Mas como a chave não servirá para outra máquina, não ha motivos para isso.

Na sequência, especifique duas vezes uma senha forte, a tela será como abaixo:

```
Enter passphrase (empty for no passphrase): 
```

Ao configrmar, sua chave estará criada e será exibida.
