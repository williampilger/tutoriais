# Cadastrar scripts no menu de contexto do Nautilus

Os scripts ficam localizados no diretório abaixo:

```sh
~/.local/share/nautilus/scripts/
```

Qualquer coisa que você colocar neste diretório, com permissão de ser executado, agora aparecerá no menu de contexto.
Você pode usar o parâmetro `$1` para executar tarefas.

## Exemplo de aplicação

Script para abrir um diretório no VScode:

*~/.local/share/nautilus/scripts/open-with-vscode.sh*
```sh
#!/bin/bash
code "$1"
```
