# Visualizar Fotos dentro de um terminal Linux (inclusive via SSH)

> Neste exemplo, estou usando um `Ubuntu 25.04` e um `Zorin` também da mesma versão.


## Método 1: Terminais simples - *A imagem fica bem pixelada, mas dá pra ter uma boa ideia do que é.*

```bash
# Instalar a biblioteca
sudo apt install chafa   # ou catimg, ou viu

# Visualizando a imagem
chafa /caminho/imagem.png
```

## Método 2: Para terminais com suporte avançado

```bash
# kitty
sudo apt isntall kitty
kitten icat /caminho/imagem.png

# iTerm2 (precisa do imgcat, vem com o iTerm2 utils)
sudo apt install iTerm2
imgcat /tmp/shot.png

# genérico via Sixel (se o terminal suportar)
sudo apt install libsixel-bin
img2sixel /tmp/shot.png
```
