# Comandos Diversos

## Ver informações básicas do sistema

> uname --help

Exibe uma lista completa de opções que você tem de ver algo sobre o sistema.

## (2) Ver informações so sistema

> neofetch

Este comando precisa ser instalado (Com `sudo apt install -y neofetch`);

## Listar unidades de armazenamento

> lsblk

Comando lista todas as unidades de armazenamento reconhecidas pelos sitema.

## Copiar dados de uma unidade / para uma unidade

> dd if=in_file.ext of=out_file.ext

Use `dd --help` para entender o comando.

Um exemplo para criar uma ISO de disco:

> dd if=/dev/cdrom of=image_name.iso

## Buscar no histórico do Bash (do terminal)

`Ctrl+R` — busca incremental reversa no histórico.

Digite `Ctrl+R`, depois comece a digitar parte do comando. O bash vai mostrando o match mais recente em tempo real. Para navegar entre os resultados, continue pressionando `Ctrl+R`. Para executar, Enter. Para cancelar, `Ctrl+C` ou `Esc`.

Outras opções úteis:

- `history | grep <termo>` — lista todos os matches com número de linha; depois roda com `!<número>`
- `Ctrl+G` — sai da busca sem executar
- `!!` — repete o último comando
- `!<prefixo>` — executa o último comando que começa com aquele prefixo (ex: `!git`)

O `Ctrl+R` cobre 90% dos casos no dia a dia.
