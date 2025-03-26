# Usando o Image Magick no terminal (miltiplataforma)

Instale o ImageMagick no seu PC de acordo com o seu sistema operacional (no linux `sudo apt install imagemagick`), que pode ser baixado no [site oficial](https://imagemagick.org) gratuitamente.


## Exemplos de comandos e usos

| Comando | Aplicação |
| --- | --- |
| `convert input.png output.webp` | Converter a imagem de formato sem alterações de proporção e/ou qualidade (na medida do possível) |
| `convert input.jpg -quality 80 output.jpg` | Alterar a qualidade da imagem |
| `convert input.jpg -resize 150x output.jpg` | Reduzir a largura para 150px, mantendo a proporção |
| `convert input.jpg -resize x150 output.jpg` | Reduzir a altura para 150px, mantendo a proporção |
| `convert input.jpg -resize 150x150! output.jpg` | Reduzir para exatamente 150x150 pixels (sem manter a proporção, pode distorcer) |
| `convert input.jpg -resize 150x150^ -gravity center -extent 150x150 output.jpg` | Reduzir para 150x150, cortando o excesso (mantendo proporção) |

**ATENÇÃO:** Em algumas versões (e no windows) o comando é `magick` ao invés de `convert`.



## About

By: **will.i.am** | github.com/wiliampilger
2024.12.11 14:14
