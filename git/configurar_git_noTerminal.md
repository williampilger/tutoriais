# Configurando o GIT via terminal

Este passo a passo é semelhante para **Windows 10**, **MAC** e **Linux**.



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



## Copiando os dados da sua chave SSH

Você pode fazer isso manualmente, ou via linha de comando:

  **Linux** (precisa xclip instalado, use `apt-get install xclip`, por exemplo.)

  > xclip -sel clip < ~/.ssh/id_ed25519.pub

  **MAC OS**

  > tr -d '\n' < ~/.ssh/id_ed25519.pub | pbcopy

  **Windows** (no Git Bash)

  > cat ~/.ssh/id_ed25519.pub | clip



## Adicionando sua chave SSH no GIT

Obviamente para isso, você já instalou o git no seu computador. Se ainda não, providencie.

1. Faça login no GitLab.

2. Na barra superior, no canto superior direito, selecione seu avatar.

3. Selecione **Preferências**.

4. Na barra lateral esquerda, selecione **Chaves SSH**.

5. Na caixa Chave , cole o conteúdo da sua chave pública. Se você copiou manualmente a chave, certifique-se de copiar a chave inteira, que começa com `ssh-ed25519` ou `ssh-rsae` pode terminar com um comentário.

6. Na caixa Título , digite uma descrição, como `Work Laptop`ou `Home Workstation`.

7. Opcional. Na caixa Expira em , selecione uma data de expiração. ( Introduzido no GitLab 12.9.).

8. Selecione **Adicionar chave**.



# Sobre

**Algumas referências**
- [Start using Git on the command line](https://docs.gitlab.com/ee/gitlab-basics/start-using-git.html);
- [Install Git](https://docs.gitlab.com/ee/topics/git/how_to_install_git/index.html);
- [GitLab and SSH keys](https://docs.gitlab.com/ee/ssh/index.html);

By: will.i.am | Balneário Camboriú - SC
