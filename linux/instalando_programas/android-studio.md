# Instalando o Android Studio

Baixe o aplicativo diretamente pelo [site oficial do google](https://developer.android.com/studio?hl=pt-br);

Você receberá um arquivo `.tar.gz`, para extrair e instalar:

```sh
tar -xzf android-studio-*.tar.gz
sudo mv android-studio /opt/
cd /opt/android-studio/bin
./studio.sh
```

Siga as instruções para instalar...



## Criando o atalho na interface gráfica

> sudo nano /usr/share/applications/android-studio.desktop

Cole o seguinte conteúdo:

```txt
[Desktop Entry]
Version=1.0
Type=Application
Name=Android Studio
Exec=/opt/android-studio/bin/studio.sh
Icon=/opt/android-studio/bin/studio.png
Terminal=false
StartupNotify=true
Categories=Development;IDE;
```
