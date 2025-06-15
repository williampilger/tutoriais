# Usando o Image Magick no terminal (multiplataforma)

Instale o ImageMagick no seu PC de acordo com o seu sistema operacional (no linux `sudo apt install imagemagick`), que pode ser baixado no [site oficial](https://imagemagick.org) gratuitamente.


## Exemplos de comandos e usos

| Comando | Aplicação |
| --- | --- |
| `convert input.png output.webp` | Converter a imagem de formato sem alterações de proporção e/ou qualidade (na medida do possível) |
| `mogrify -format jpg *.heic` | Converter todas as correspondências (no windows, pode ser necessário usar `convert mogrify`) |
| `mogrify -path PASTA -format jpg *.heic` | Converter todas as correspondências e salvar em `PASTA` (no windows, pode ser necessário usar `convert mogrify`) |
| `convert input.jpg -quality 80 output.jpg` | Alterar a qualidade da imagem |
| `convert input.jpg -resize 150x output.jpg` | Reduzir a largura para 150px, mantendo a proporção |
| `convert input.jpg -resize x150 output.jpg` | Reduzir a altura para 150px, mantendo a proporção |
| `convert input.jpg -resize 150x150! output.jpg` | Reduzir para exatamente 150x150 pixels (sem manter a proporção, pode distorcer) |
| `convert input.jpg -resize 150x150^ -gravity center -extent 150x150 output.jpg` | Reduzir para 150x150, cortando o excesso (mantendo proporção) |

**ATENÇÃO:** Em algumas versões (e no windows) o comando é `magick` ao invés de `convert`.


## Script para conversão de imagens para uma `Fujifilm Finepix S2980`

```sh
#!/bin/bash
# By DeepSeek + Wilger

# CONFIGURAÇÕES =======================
DESTINO="/media/$USER/disk"  # Caminho onde o cartão está montado
PASTA_DESTINO="$DESTINO/DCIM/129_FUJI"
MAX_RESOLUCAO="4288x3216"
QUALIDADE=85
# =====================================

# Verifica se o destino existe
if [ ! -d "$DESTINO" ]; then
  echo "❌ Cartão SD não encontrado em $DESTINO"
  echo "💡 Monte o cartão SD e edite a variável DESTINO no script, se necessário."
  exit 1
fi

mkdir -p "$PASTA_DESTINO"

# Cria pasta temporária
TMPDIR=$(mktemp -d)
echo "📂 Pasta temporária: $TMPDIR"

# Converte arquivos
echo "🔄 Convertendo imagens..."

count=1
for img in *.{jpg,jpeg,JPG,JPEG,png,PNG,heic,HEIC}; do
  [ -f "$img" ] || continue

  newname=$(printf "IMG_%04d.JPG" "$count")
  temp_output="$TMPDIR/$newname"

  echo "→ $img -> $newname"

  convert "$img" \
    -strip \
    -resize ${MAX_RESOLUCAO}\> \
    -sampling-factor 2x2 \
    -colorspace sRGB \
    -interlace none \
    -quality $QUALIDADE \
    "$temp_output"

  # Adiciona EXIF se estiver ausente
  exiftool -overwrite_original \
    -Make=FujiFilm \
    -Model=FinePix \
    -DateTimeOriginal="$(date '+%Y:%m:%d %H:%M:%S')" \
    -Artist="Imagem convertida" \
    "$temp_output" > /dev/null

  ((count++))
done

echo "✅ Conversão concluída. Total de imagens: $((count - 1))"

# Copia para o cartão
echo "📤 Copiando para o cartão SD em: $PASTA_DESTINO"
cp "$TMPDIR"/*.JPG "$PASTA_DESTINO/"

# Limpa temporários
rm -rf "$TMPDIR"

echo "🎉 Tudo pronto! Insira o cartão na FinePix e aproveite!"

```

## About

By: **will.i.am** | github.com/wiliampilger
2024.12.11 14:14
