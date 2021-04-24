# Instalar/Desinstalar TeamViewer no Ubuntu

Neste exemplo realizei o processo com o Ubuntu 20.04 LTS

## Obtendo o Instalador

Baixe o instalados do site oficial da [TeamViewer](https://www.teamviewer.com/pt-br/download/linux/).

## Instalando

1. Instalando o pacode .deb:
    > sudo dpkg -i teamviewer.deb
Obviamente, substitua o nome do pacote pelo nome do seu instalador.

2. Instalando as dependências:
    > sudo apt-get install -f -y

## Desinstalando

1. Desinstalando o pacote
    > sudo apt-get remove teamviewer

2. Desinstalando as dependências
    > sudo apt-get autoremove