# Aula 1 - Git e Github

Esta aula está (ou ao menos estava) disponível [no YouTube](https://www.youtube.com/watch?v=zOdV7bBcS0E).



## Configurando GIT

Instale o GIT, e o Visual Studio Code, normalmente.

Configurando o seu nome e email para os commits

> git config --global user.name "<seu nome>"
> git config --global user.email "<seu email>"

Configurando o VS Code como editor de texto padrão

> git config --global core.editor "code -wait"



## Criando um repositório

Dentro de uma pasta, dê o comando para criar um repositório local:

> git init



## Status e LOG

Obter o status do seu repositório

> git status

Para ver seu histórico de commits, use:

> git log

Para ver o LOG de forma um pouco mais gráfica, pode-se usar:

> git log --graph --all



## Adicionar arquivos ao repositório e/ou à branch atual

Adicionar arquivos ao seu repositório:

> git add fileName.c

Você pode adicionar arquivos usando `git add .` para adicionar tudo, ou usar `git add /pasta/**/*.js`  por exemplo.



## Criar, Excluir e migrar de branch

Criando uma branch

> git branch nome_da_branch

Você também poderá ver em qual chanch está digitando apenas `git branch`.

Migrar para uma branch:

> git checkout nome_da_branch

Ou ainda, pode criar e migrar para uma branch com um único comando:

> git checkout -b nome_da_branch

Para deletar uma branch use:

> dig branch -D nome_da_branch



## Commit e merge

Criar um commit:

> git commit -m "mensagem de commit"

Mesclar branches (merge). No exemplo abaixo, a **master_branch** será mergida à **branch atual** (que você pode ver usando `git status`) .

> git merge master_branch

O comando `git merge` mantém a ordem cronológica de todas suas alterações. Caso você prefira, podem ser aplicadas as alterações todas em cascata, usando o `git rebase`, veja abaixo:

> git rebase master_branch

No exemplo acima, **são perdidos os detalhes da ordem cronológica das alterações**, mas o efeito final é o mesmo. a branch **atual** foi mesclada à **master_branch**.



## Interagindo com um repositório remoto

Cloar um repositório:

> git clone https://url.do.seu/repositorio/remoto.git

Ou baixar alterações do repositório remoto para o local, usam-se os `fetch` e `pull`. O git pull faz um git fetch seguido de um merge, ou seja, aplica as alterações do repositório remoto já na sua branch local.

> git fetch

> git pull

Para enviar seus commits do repositório local para o remoto, use o `push`:

> git push
  


## Alterando o caminho do reposiorio remoto

Temos um exemplo abaixo:

> git remote set-url origin git@github.com:williampilger/academic.git

Pode-se ver qual o diretório atual do remoto digitando:

> git remote -v
