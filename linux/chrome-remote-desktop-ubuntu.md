# Instalando e configurando o Google Remote Desktop no Ubuntu

Versão do meu sistema: `24.04 LTS`;

Obs: <span style="color:red;">Ativar o acesso remoto desta forma <strong>IMPOSSIBILITA O ACESSO FÍSICO À MÁQUINA</strong> depois de acessa-la remotamente. Depois de reiniciar, o acesso físico volta a funcionar. Isso ocorre por que o software não foi feito pra rodar com o weyland, mas eu uso assim.</span>

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
