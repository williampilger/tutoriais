# Comandos GIT - Terminal




## Gerais

| Comando | Aplicação | Obs |
| --- | --- | --- |
| `git init` | Criar repositório | dentro de uma pasta, rode este comando para iniciar o controle de versionamento local |
| `git status` | Ver status da árvore atual | |
| `git log` | Histórico de commits | |
| `git log --graph --all` | Histórico de commits gráfico | isso é meio "gráfico" |
| `git add fileName.c` | Adicionar arquivo específico à árvore de trabalho | |
| `git rm <file-name>` | Remover um arquivo do repositório | |
| `git add .` | Adicionar diretório atual inteiro à árvore | Você pode informar um diretório aqui |
| `git push` | Enviar commits locais para a origem | |
| `git pull` | Baixar commits da origem | |
| `git fetch origin` | Sincronizar, todas as branches, com o repositório remoto | |
| `git branch <branch-name>` | Criar branch `<branch-name>` | |
| `git checkout <branch-name>` | Migrar para branch `<branch-name>` | |
| `git checkout <branch-name>` | Trocar para a branch `<branch-name>` | |
| `git checkout -b <branch-name>` | Criar e Migrar para branch `<branch-name>` | |
| `git branch -D <branch-name>` | Deletar uma branch `<branch-name>` | |
| `git branch -r` | Listar todas as branches remotas | |
| `git branch -a` | Listar todas as branches (locais e remotas) | |
| `git commit -m "mensagem de commit"` | Cria um commit | commit para branch ativa |
| `git merge <branch-name>` | Traz os commits da branch `<branch-name>` para a branch atualmente ativa | Comando `merge` mantém a ordem cronológica dos commits |
| `git rebase <branch-name>` | Une os commits da branch `<branch-name>` e aplica em uma única modificação na branch atual | Descarta a ordem cronológica dos commits |
| `git reset --hard` | Reverter a árvore de trabalho para o último commit | Perde todas as mudanças não commitadas |
| `git stash` | Guardar modificações não commitadas para aplicação posterior | Útil para limpar a árvore de trabalho sem perder as mudanças |
| `git stash pop` | Recuperar as modificações guardadas no stash | |
| `git remote add origin <url>` | Adicionar repositório remoto | Define a URL do repositório remoto |
| `git clone <url>` | Clonar um repositório remoto | Cria uma cópia local do repositório |
| `git diff` | Mostrar as diferenças não commitadas | |
| `git tag <tag-name>` | Criar uma tag | Usado para marcar pontos específicos na história do repositório |
| `` | | |


## Minha configuração Padrão

*terminal$*
```sh
git config --global user.name "<seu nome>"
git config --global user.email "<seu email>"
git config --global core.editor "code -wait"
```