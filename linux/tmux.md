# TMUX

| Comando               | Descrição                                   |
|-----------------------|---------------------------------------------|
| `tmux`                | Inicia uma nova sessão tmux.                |
| `tmux new -s [nome]`  | Cria nova sessão com nome.                  |
| `tmux ls`             | Lista sessões ativas.                       |
| `tmux attach -t [nome]` | Anexa a uma sessão existente pelo nome.    |
| `tmux kill-session -t [nome]` | Encerra a sessão especificada.          |
| `Ctrl+b "`            | Divide o painel atual horizontalmente.      |
| `Ctrl+b %`            | Divide o painel atual verticalmente.        |
| `Ctrl+b o`            | Alterna entre painéis.                      |
| `Ctrl+b c`            | Cria uma nova janela.                       |
| `Ctrl+b n`            | Move para a próxima janela.                 |
| `Ctrl+b p`            | Move para a janela anterior.                |
| `Ctrl+b &`            | Fecha a janela atual.                       |
| `Ctrl+b [`            | Entra no modo de rolagem. Use as setas para navegar. Pressione `q` para sair. |
| `Ctrl+b d`            | Desanexa da sessão atual e retorna ao terminal. |
| `Ctrl+b x`            | Fecha o painel atual.                       |
