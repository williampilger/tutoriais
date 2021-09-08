# Instalar pacote .deb com dependências

Como o caso do VirtualBox, existem dependências que precisam ser resolvidas ao instalar o pacote.

Instale o .deb em questão:

> sudo dpkg -i SEU_PACOTE.deb

Instale todas as dependências:

> sudo apt-get -f install
