# `ffmpeg` - Linux e/ou Windows

Aqui vou ir anotando o que eu achar útil.


## Cortar um Vídeo

```bash
ffmpeg -i video_original.mp4 -ss 00:00:10 -to 00:00:30 -c copy video_cortado.mp4
```
