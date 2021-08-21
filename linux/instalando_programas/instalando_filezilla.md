# Instalando o FileZilla no Ubuntu

Obs.: Estou usando o `Ubuntu 20.04 LTS`, mas o procedimento é semelhante em qualquer base Ubuntu.

## Download do Instalador

Faça o download (via navegador, ou terminal) do instalador que está disponível no [site oficial](https://filezilla-project.org).


## Instalando

Tenha certeza de que não existe uma instalação pendente. Se tiver dúvidas, execute os comandos de desinstalação primeiro.


Extraia o pacote baixado para um diretório de desejo:

> sudo tar -xjvf filezilla.tar.bz2 -C /opt/

Renomeie a pasta extraida:

> sudo mv /opt/FileZilla*/ /opt/filezilla

Crie um atalho, para facilitar sua vida:

> sudo ln -sf /opt/filezilla/bin/filezilla /usr/bin/filezilla

Criar o comando no terminal:

> echo -e '[Desktop Entry]\n Version=1.0\n Name=filezilla\n Exec=/opt/filezilla/bin/filezilla\n Icon=/opt/filezilla/share/icons/hicolor/48x48/apps/filezilla.png\n Type=Application\n Categories=Application' | sudo tee /usr/share/applications/filezilla.desktop


## Removendo o Filezilla

```
sudo rm -Rf /opt/filezilla*
sudo rm -Rf /usr/bin/filezilla
sudo rm -Rf /usr/share/applications/filezilla.desktop
```
