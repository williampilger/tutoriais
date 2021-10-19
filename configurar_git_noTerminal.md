# Configurando o GIT via terminal

Este passo a passo é semelhante para **Windows 10**, **MAC** e **Linus**.

## Criando um par de chaves SSH

Se você já possui um, pule esta etapa. Vamos criar a seguir um par de chaves **ED25519**, que é a mais segura atualmente.

Abra um terminal e digite:

> ssh-keygen -t ed25519 -C "'< comment >"

Onde o `< comment >`é um comentário qualquer.
