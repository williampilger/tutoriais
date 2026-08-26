# Alterar Kernel da sua distribuição Ubuntu-based

Use uma plaicação que faça isso. Cujo repositŕoio está [disponível aqui](https://github.com/bkw777/mainline).

Um vídeo ótimo explicando essa pahaçada toda [está no Youtube do Diolinux](https://www.youtube.com/watch?v=Yrtr41nAxn0).

Para instalar basta rodar:

```bash
sudo add-apt-repository ppa:cappelikan/ppa
sudo apt update
sudo apt install mainline
```

Para executar o programa, busque o `Mainline` na sua lista de apps.

> Agora **depois de instalar a versão que você pretende rodar**,
> você ainda precisa escolher qual o kernel (dos instalados) que
> você pretende usar no boot. Pra isso:
>
> Pressione `shift` no teclado durante o boot para o GRUB ser exibido.
