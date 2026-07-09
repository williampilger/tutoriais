# Pull Request cheia de arquivos com "file mode changed"

Quando aparece que teve "file mode changed" e algo como `100644 -> 100755` em um monte de arquivos na pull request, significa que alguém fez um commit marcando os arquivos como executáveis, o que não faz nenhum sentido.

```bash
# Procura todos os arquivos marcados como 100755 e remove a permissão de execução no Git
git ls-files --stage | grep 100755 | awk '{print $4}' | xargs git update-index --chmod=-x

# Cria o commit com a correção
git commit -m "fix: remove permissão de execução indevida de arquivos estáticos"
git push
```
