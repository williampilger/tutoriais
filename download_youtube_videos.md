# Baixar vídeos do Youtube em alta definição

Este método foi usado por um simples motivo: Nem eu sendo o proprietário dos vídeos, consigo salvá-los em alta definição.

**Este método funciona em ambientes linux**. Você pode usar docker para isso:

*Windows - CMD*
> docker run -it --rm --network host -v "%userprofile%\Downloads":/Downloads ubuntu

*Windows - PowerShell*
> docker run -it --rm --network host -v "${USERPROFILE}/Downloads:/Downloads" ubuntu

*Linux*
> docker run -it --rm --network host -v "~/Downloads":/Downloads ubuntu


## Usando a ferramenta

```sh
# Instalando dependências
apt update
apt install curl python3

# "Instalando" o script
curl -L https://github.com/yt-dlp/yt-dlp/releases/latest/download/yt-dlp -o /usr/local/bin/yt-dlp
chmod a+rx /usr/local/bin/yt-dlp

# Fazer o download
yt-dlp -f bestvideo+bestaudio [URL_DO_VÍDEO]
```

### União de Audio+Video

Em alguns casos, em vídeos de alta qualidade de vídeo e/ou áudio, os dois serãoo baixados separadamente.
Para unir, você pode usar a mesma áquina Docker e:

```hs
# Instalar a dependência
apt install ffmpeg

# Unindo o Vídeo + Audio
ffmpeg -i video.mp4 -i audio.webm -c:v copy -c:a aac -strict experimental output.mp4
```


## Ou, tente também

Existe uma ferramenta instalável, no entanto, não está disponível em quase nenhuma região.

```sh
sudo apt update
sudo apt install youtube-dl

youtube-dl -f bestvideo+bestaudio [URL_DO_VÍDEO]
```
