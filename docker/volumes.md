# Trabalhando com Volumes

Criar um volume:
  ```sh
  docker volume create your-volume
  ```

Você pode usar um container temporário para copiar dados entre volumes, por exemplo:
  ```sh
  docker run --rm -it \
    -v volume-destino:/origem \
    -v volume-destino:/destino \
    ubuntu bash -c "cp -a /origem/. /destino/"
  ```

Usando o volume para um container:
  ```sh
  docker run -d \
      --name meu-container \ # opcional
      -v meu_volume_db:/var/lib/mysql \ # EXEMPLO: Caminho `/var/lib/mysql` é o caminho de montagem quando for executar um banco MySQL com um volume
      -e MYSQL_ROOT_PASSWORD=sua_senha \ # EXEMPLO: Variável de ambiente
      mysql:latest # EXEMPLO: use sua imagem aqui
  ```

# Sobre

By: **William Pilger** | github.com/williampilger

2025/02/24 11:53 | Bom Princípio - RS - Brasil
