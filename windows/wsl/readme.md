# WSL - Windows Subsistem for Linux


## Instalação

Por "padrão", o WSL não vem instalado, mas se você digital `wsl` no terminal (`cmd` ou `PowerShell`) a instalação se inicia automaticamente.

Caso você já use Docker, o WSL já está instalado no seu sistema, e provavelmente o `docker-desktop` é sua "distribuição padrão" no WSL (o que não é bom).

Então, ou, instale usando:

> wsl --install -u Ubuntu

**PS.:** Caso você queira usar outra distro, faça a alteração no comando, ou liste as opções disponíveis por padrão com `wsl --list --online`.

Ou, acesse a *Loja do WIndows* (*Microsoft Store*), e produte por `Ubuntu`.


## Comandos Básicos

| Comando | Descrição |
| --- | --- |
| `--list` | Listar as distribuições disponíveis na sua instalação |
| `wsl -l -v` | Listar as distribuições disponíveis na sua instalação, com a respectiva versão |
| `--list --online` | Listar as distribuições disponíveis para download |
| `wsl --set-default Ubuntu` | Tornar `Ubuntu` sua distribuição padrão |
