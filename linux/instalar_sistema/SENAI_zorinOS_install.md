# Instalando o ZorinOS nos computadores do SENAI

Este guia tem como objetivo detalhar o procedimento para instalação do ZorinOS, um sistema operacional baseado no Linux, nos computadores do SENAI.
O processo é relativamente simples, incluindo o download da ISO, instalação padrão, e execução do post-install; e pode ser realizado por qualquer pessoa com conhecimentos básicos de informática.




## Download da ISO do sistema

Primeiramente, precisamos do LiveCD do Sistema Operacional que queremos instalar.

- 1. Acesse o site oficial do ZorinOS: [ZorinOS Download](https://zorin.com/os/download/);
- 2. Localize a verão Core (neste momento, a versão `Zorin OS 18.1 Core`);
- 3. Clique em **Download**;
- 4. Na próxima tela clique em `skip do Download` (ou preencha seu email, mas **isso é opcional**);
- 5. Aguarde o término do download da ISO (que possui `3,6 GB`).


## Gravando a imagem do sistema em um pendrive

Você pode fazer isso, basicamente, de duas formas:

#### Opção 1: Utilizando o Balena Etcher

Neste caso, siga [este guia](../../flash_usb_balena-etcher.md).

#### Opção 2: Usando o Ventoy

Se você ainda não tem um pendrive com o Ventoy, siga [este guia](../../flash_usb_ventoy.md) para criar um.

Tendo ele em mãos, basta copiar a ISO do ZorinOS para o pendrive, e ele já estará pronto para ser utilizado.



---



## Instalação do sistema

1. Insira a mídia de instalação (pendrive) no computador onde deseja instalar o ZorinOS;
2. Inicie o computador dando boot pelo pendrive
   1. Ou, caso esteja com um Windows com Secure Boot e UEFI, reinicie no modo avançado (segurando o Shift)
3. Selecione a opção de instalação do ZorinOS;
4. Selecione `Try os Install Zorin OS` para iniciar o processo de instalação;
5. Já na interface gráfica, selecione o idioma `Português do Brasil` e clique em `Instalar o Zorin OS`;
6. O layout do teclado deve estar certo, então basta clicar em `Continuar` (ou ajuste, se necessário);
7. Deixe a opção `Instalar programas de terceiros[...]` marcada, e clique em `Continuar`;
8. Marque a opção `Apagar disco e instalar o Zorin OS` e clique em `Instalar agora`;
   1. Confirme a formatação do disco clicando em `Continuar`;
9. Selecione o fuso horário `Brasília` e clique em `Continuar`;
10. Preencha os dados de usuário e senha, e clique em `Continuar`
    1.  Seu nome: `Administrador`;
    2.  Nome do computador deve ser único na rede, no caso do SENAI, é algo como `MICRO-001`;
    3.  Nome de usuário: `administrador` (já vai estar certo);
    4.  Senha: **Preencher a senha default do administrador**;
    5.  Marque a opção `Solicitar minha senha para entrar` e clique em `Continuar`;
    6.  **NÃO** marque a opção do Active Directory.
    7.  Clique em `Continuar` para iniciar a instalação do sistema.
11. Aguarde o término da instalação, e clique em `Reiniciar agora`.
    1.  Ele vai pedir pra remover a mídia e dar um Enter. Faça.


## Configuração pós-instalação

Agora, com o sistema instalado e ligado, acesse o usuário `Administrador` que você criou.

Quando o usuário acessa pela primeira vez, o sistema inicia um "tour", clique em `Não, Obrigado`.

Caso o `Atualizador de Programas` abra oferecendo uma atualização neste meio tempo, feche a janela (nós faremos a atualização com o script). 

1. Abra o navegador (nesse caso, o Brave), que costuma ser o primeiro item fixado na barra de tarefas (depois do menu);
2. Acesse o repositório com o script [github.com/williampilger/williampilger] e procure pelo post-install do Senai;
   1. A URL Exata dele é [essa](https://github.com/williampilger/williampilger/blob/main/PostInstallScripts_LinuxShell/ACI_SENAI_BasicWorkstation_ZorinOS.sh);
3. No topo do script, você verá um comando para rodar o script diretamente, sem baixar:
   1. O comando exato é `bash -c "$(curl -fsSL https://raw.githubusercontent.com/williampilger/williampilger/main/PostInstallScripts_LinuxShell/ACI_SENAI_BasicWorkstation_ZorinOS.sh)"`
   2. Copie esse comando
4. No Zorin, abra o terminal (pressionando `Ctrl + Alt + T`), ou clicando no menu e pesquise pelo terminal;
5. Cole o comando (Com `Ctrl`+`Shift`+`V` ou clicando com o direito e em `Colar`) e dê Enter para executar o script;
6. Dê um enter para confirmar a execução do script, digite a senha do administrador para confirmar;
7. Aguarde o término da execução do script, e reinicie o computador para aplicar as mudanças (pode digitar `reboot` no terminal).




---

## Sobre

Este guia foi elaborado por [William Pilger](https://github.com/williampilger);

**28 de Março de 2026** | Bom Princípio - RS