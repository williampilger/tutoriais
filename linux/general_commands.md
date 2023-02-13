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

