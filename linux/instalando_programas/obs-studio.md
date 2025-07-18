# Instalação do OBS Studio no Linux - `Ubuntu-Based`

Realizei vários testes e, no meu caso, para uso de streamings de entrada variados, incluindo `Browser` (Usado pelo `IP Webcam Pro`, por exemplo), e a Camera vircual, a melhor opção foi usando Flatpack.

```bash
# Para instação simples, quase tudo funciona
flatpak install flathub com.obsproject.Studio

# Suporte para vamera virtual
flatpak install org.kde.Platform//5.15-21.08
flatpak override com.obsproject.Studio --enable-features=Camera
flatpak override com.obsproject.Studio --filesystem=/dev/video0
sudo modprobe v4l2loopback devices=1 video_nr=10 card_label="OBS Cam" exclusive_caps=1
```

## Sobre

By: **will.i.am** | github.com/williampilger
