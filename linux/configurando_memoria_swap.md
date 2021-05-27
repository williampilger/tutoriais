# Alterar tamanho da memoria SWAP no ubuntu
Para tal, abra o terminal e siga os paços:

Vá para o diretório raiz:
> cd /

Desative a memoria SWAP em uso no momento, se tiver:
> sudo swapoff /swapfile

Remova o arquivo swap velho:
> sudo rm /swapfile 

Crie um novo arquivo swap, do tamanho que achar melhor. Exemplo criando 5GB:
> sudo fallocate -l 5G /swapfile 

Dê as permições necessárias ao arquivo:
> sudo chmod 600 /swapfile

Configurar o arquivo para ser swap:
> sudo mkswap /swapfile

Ativar o swap novamente:
> sudo swapon /swapfile 


E é basicamente isso, se você precisar alterar novamente, é só repetir o processo. Caso o comando  fallocate não funcione é possível fazer de outro jeito também, mas você precisar criar o arquivo e encher ele de zeros para ficar do tamanho que você precisa sem outras informações, pode ser feito dessa forma:

> sudo dd if=dev/zero of=/mnt/5GiB.swap bs=1024 count=1048576

Tutorial tirado da página do [DIOLUNUX](https://diolinux.com.br/tutoriais/como-trabalhar-com-swap-files-ubuntu.html)
