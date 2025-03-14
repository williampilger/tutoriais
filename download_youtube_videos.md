# Baixar vídeos do Youtube em alta definição

Este método foi usado por um simples motivo: Nem eu sendo o proprietário dos vídeos, consigo salvá-los em alta definição.

**Este método funciona em ambientes linux**. Você pode usar docker para isso:

*Windows - CMD*
> docker run -it --rm --network host -v "%userprofile%\Downloads":/Downloads ubuntu

*Windows - PowerShell*
> docker run -it --rm --network host -v "${USERPROFILE}/Downloads:/Downloads" ubuntu

*Linux*
> docker run -it --rm --network host -v "~/Downloads":/Downloads ubuntu

---

## Instalando e Usando a ferramenta

**Instalação**:
```sh
# Instalando dependências
apt update
apt install -y curl python3 ffmpeg

# "Instalando" o script
curl -L https://github.com/yt-dlp/yt-dlp/releases/latest/download/yt-dlp -o /usr/local/bin/yt-dlp
chmod a+rx /usr/local/bin/yt-dlp
```

**Utilização**
```sh
# Fazer o download de um vídeo - Com qualidades máximas
yt-dlp -f bestvideo+bestaudio [URL_DO_VÍDEO]

# Verificando a qualidades disponíveis para um vídeo
yt-dlp -F [URL_DO_VÍDEO]
# Usando a qualidade escolhida
yt-dlp -f 614+233 [URL_DO_VÍDEO] #onde os números são a primeira coluna da tabela de qualidades
```

---

### União de Audio+Video

Em alguns casos, em vídeos de alta qualidade de vídeo e/ou áudio, os dois serãoo baixados separadamente.
Para unir, você pode usar a mesma áquina Docker e:

```hs
# Instalar a dependência (caso não o tenha feito anteriormente... Mas deve ter feito
apt install -y ffmpeg

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
