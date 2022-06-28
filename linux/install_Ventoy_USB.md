# Instalar Ventoy em um pendrive

Liste as unidades conectadas, e localise o nome da sua com:

> lsblk

Baixe o ventoy do [site oficial](https://www.ventoy.net/), e extraia o conteúdo do arquivo compactado. Navegue em seguida até o diretório dos scripts e:

> sudo chmod +x *.sh

> sudo ./Ventoy2Disk.sh -s -I sdc

Substituindo `sdc` pela sua unidade correta.
