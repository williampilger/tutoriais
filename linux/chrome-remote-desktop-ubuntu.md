# Instalando e configurando o Google Remote Desktop (GRD) no Ubuntu

> Testado nos sistemas
> 
>    `Ubuntu 24.04 LTS` - **Fev. 2025**
> 
>    `Ubuntu 25.04` - **Mar. 2026**
> 
> **Atenção:** Ativar o acesso remoto desta forma **IMPOSSIBILITA O ACESSO FÍSICO À MÁQUINA** depois de acessá-la remotamente. Depois de reiniciar, o acesso físico volta a funcionar. Isso ocorre porque o software não foi feito para rodar com o Wayland, mas eu uso assim.
>
> **Funcionamento**: Também é importante notar que o GRD inicia uma seção gráfica no momento que o serviço é iniciado, no boot.
> Se por algum motivo você precisar encerrar esta seção manualmente, o serviço do google fica indisponível.

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


## Habilitar/Desabilitar o Serviço

*Parar o serviço temporariamente*
```bash
sudo systemctl stop chrome-remote-desktop@seu_usuario
```

*Reiniciar o serviço*
```bash
sudo systemctl restart chrome-remote-desktop@seu_usuario
```

*Parar o serviço e desabilitar ele no boot* 
```bash
sudo systemctl disable chrome-remote-desktop@seu_usuario
```

*Iniciar o serviço e habilitar ele no boot* 
```bash
sudo systemctl enable chrome-remote-desktop@seu_usuario
```

---


# Solução de Problemas

> **Problema:** Não consigo fazer login na máquina física ou pelo RDP após ter aberto uma seção remota com o GRD.
> 
> Opções:
> 
> **a)** Reiniciar o PC ou o serviço (veja acima como);
> 
> **b)** Encerrar a ou as seções manualmente [veja como](./loginctl.md). Você pode encerrar apenas a seção do GRD, ou todas as seções do usuário;



