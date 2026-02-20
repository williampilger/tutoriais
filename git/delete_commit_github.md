# Excluir e/ou desfazer um commit no GitHub


O "como", depende se o commit **já foi enviado pro GitHub (push)** e se outras pessoas já puxaram ele. Aqui vão os jeitos certos, do mais seguro ao mais “apaga da história”.

## Caso A: o commit já está no GitHub e o branch é compartilhado

O mais seguro é **reverter** (cria um novo commit que desfaz o anterior). Não reescreve histórico.

### Reverter o último commit

```bash
git revert HEAD
git push
```

### Reverter um commit específico

```bash
git revert <hash_do_commit>
git push
```

No GitHub (web), também dá pra abrir o commit ou PR e usar “Revert” (quando disponível). Isso faz essencialmente um `git revert`.

## Caso B: o commit já está no GitHub, mas é teu branch e tu quer “apagar” da história

Aí é **reset + force push** (reescreve histórico). Use `--force-with-lease`, não `--force`.

### Apagar o último commit (e perder as alterações dele)

```bash
git reset --hard HEAD~1
git push --force-with-lease
```

### Apagar o último commit, mas manter as alterações no teu working tree (pra commitar de novo)

```bash
git reset --soft HEAD~1
git push --force-with-lease
```

## Caso C: o commit ainda NÃO foi enviado pro GitHub (só local)

Só faz reset e pronto (sem force push).

### Apagar o último commit

* Mantendo alterações (pra re-commitar):

```bash
git reset --soft HEAD~1
```

* Jogando fora as alterações:

```bash
git reset --hard HEAD~1
```

## Caso D: “quero excluir um commit do meio” (não é o último)

Se já foi pro GitHub e é compartilhado: **revert** desse commit (Caso A).
Se é teu branch e pode reescrever histórico: **rebase interativo**.

```bash
git rebase -i <hash_antes_do_commit>
```

Vai abrir uma lista. Troca `pick` por `drop` (ou apaga a linha) no commit que tu quer remover, salva e fecha.

Depois:

```bash
git push --force-with-lease
```

---

*Conteúdo gerado por IA.*
