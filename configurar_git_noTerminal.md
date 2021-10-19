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

## Adicionando sua chave SSH no GIT

Obviamente para isso, você já instalou o git no seu computador. Se ainda não, providencie.

1. Copie o conteúdo da sua chave para a área de colagem. você pode fazer isso via linha de comando:

**Linux** (precisa xclip instalado)

> xclip -sel clip < ~/.ssh/id_ed25519.pub

**MAC OS**

> tr -d '\n' < ~/.ssh/id_ed25519.pub | pbcopy

**Windows** (no Git Bash)

> cat ~/.ssh/id_ed25519.pub | clip

2. Faça login no GitLab.

3. Na barra superior, no canto superior direito, selecione seu avatar.

4. Selecione **Preferências**.

5. Na barra lateral esquerda, selecione **Chaves SSH**.

6. Na caixa Chave , cole o conteúdo da sua chave pública. Se você copiou manualmente a chave, certifique-se de copiar a chave inteira, que começa com ssh-ed25519ou ssh-rsae pode terminar com um comentário.

7. Na caixa Título , digite uma descrição, como Work Laptopou Home Workstation.

8. Opcional. Na caixa Expira em , selecione uma data de expiração. ( Introduzido no GitLab 12.9.).

9. Selecione **Adicionar chave**.

