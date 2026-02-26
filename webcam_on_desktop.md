# Como colocar a WebCam sobre o Desktop no Linux

Pode ser útil para vários cenários colocar a webcam sobre sua tela (e você mesmo ver ela).
E eu vou trazer aqui duas formas de fazer isso.

---

## Opção 1) A forma fácil e preguiçosa (e que funciona no windows também)


No Chrome, instale a extenção `Picture-in-picture` da [loja oficial](https://chromewebstore.google.com/detail/hkgfoiooedgoejojocmhlaklaeopbecg?utm_source=item-share-cb).


Agora, acesse algum site de teste de Webcam:
- [webcamtests.com](webcamtests.com);
- [pt.webcamtests.com](pt.webcamtests.com);
- ... Existem vários

Conceda acesso à sua Webcam;

E, por fim, quando já estiver vendo sua webcam na janela, clique sobre a extenção `Picture-in-picture` e voalá!


---


## Opção 2) Usando o `mpv` para colocar a câmera na tela (Apenas Linux)

Instale:
```bash
sudo apt update
sudo apt install -y mpv
```

E, execute:
```bash
mpv av://v4l2:/dev/video0 --no-border --ontop --profile=low-latency
```

Caso precise listar as câmeras:
```bash
ls /dev/video*
```


---


## Opção 3) Usando o VLC (Funciona no Windows tbm, mas APARECE A BORDA no Linux)

Abra o `VLC Media Player` e navegue até **Mídia** > **Abrir Dispositivos de Captura** e selecione sua camera.

Pressiona `Ctrl` + `H` para ocultar os menus.

Você pode acessar as configurações (`Ctrl`+`P`), selecionar o modo Avançado/Completo, ir até **Vídeo** e desmarcar a opção **Decoração de Janela** para TENTAR ocultar a janela. Isso não funciona no Gnome.
