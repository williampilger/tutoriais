# Instalando e configurando o Google Remote Desktop no Ubuntu

Versão do meu sistema: `24.04 LTS`;

> **Atenção:** Ativar o acesso remoto desta forma **IMPOSSIBILITA O ACESSO FÍSICO À MÁQUINA** depois de acessá-la remotamente. Depois de reiniciar, o acesso físico volta a funcionar. Isso ocorre porque o software não foi feito para rodar com o Wayland, mas eu uso assim.

## Pré-requisitos

- Tenha o Google Chrome Instalado



## Instalando

```sh
wget https://dl.google.com/linux/direct/chrome-remote-desktop_current_amd64.deb
sudo dpkg -i chrome-remote-desktop_current_amd64.deb
sudo apt-get -f install
```



## Configurando / Ativando

- Acesse o [Google Remote Desktop](https://remotedesktop.google.com);
- Na seção de configuração de acesso, aparecerá um link, onde você será orientado a abrir em outro PC. Abra-o em uma nova guia.
- Clique em "Seguinte". Se por acaso clicar no download, só ignore kkkk;
- Copie o código gerado, e cole no terminal;
- Informe o PIN;
- Confirme com a sua senha do PC;


Possivelmente será necessário acessar de uma guia anônima para seguir os passos.
Será necessário copiar um comando e cola-lo no terminal para autorizar o dispositivo.
