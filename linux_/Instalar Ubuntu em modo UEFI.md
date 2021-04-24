# Instalando o Ubuntu no modo de boot UEFI
Neste exemplo foi utilizado o Ubuntu 20.04 LTS (Mas tende a ser igual para as demais verções) e um Asus Aspire 5.

## Download da ISO do sistema
Bom, primeiramente precisaremos do LiveCD do Sistema Operacional que queremos instalar. Recomendo que faça o download no site oficial: [Ubuntu Desktop Download](https://ubuntu.com/download/desktop).

## Gravando a imagem do sistema em um pendrive
Acredito que atualmente esta é a melhor forma de realizar essa tarefa, pois leitores de disco estão cada vez menos presentes. Para nos auxiliar com isso, indico o Balena Etcher, que também é free e pode ser baixado do site oficial: [Balena Etcher](https://www.balena.io/etcher/).

O Etcher será baixado no formato AppImage, apos descomprimido. Então basta dar dois clics e iniciar a aplicação imediatamente. 
- Abra o Balena Etcher;
- Clique em **Flash from file** e navegue até a iso do Ubuntu que você baixou anteriormente;
- Caso seu pendrive ainda não esteja selecionado, seleciona-o, mas MUITA ATENÇÃO, pois **todos os dados serão apagados do pendrive que você selecionar**. Também é importante lembrar que o dispositivo que você for usar aqui não será facilmente formatado depois, vai exigir um pouco de trabalho;
- Clique em **Flash**;
- Digite sua senha de administrador, e aguarde o término do processo;

## Preparando a BIOS para receber o sistema
Como se trata de um Aspire 5, no nosso caso teremos que desativar o modo **Secure Boot** na BIOS para podermos bootar pelo pendrive. OBS: Estou seguindo o caminha da primeira instalação, caso estas configurações já estejam setadas, estes passos poderão ser pulados.
Então:
- Esteja com o notebook DESLIGADO;
- Ligue o computador e pressione F2 para acessar a BIOS (para outros modelos a tecla pode variar);
- Navegue até a aba **Security** e defina uma senha em **Set Supervisor Password**, nesse caso é necessário uma senha para que você consiga desativar o Secure Boot no proximo passo. Caso não queira correr o risco de esquecer a senha da sua BIOS, aconselho que remova a senha logo apos fazer as alterações;
- Na guia **Boot** altere o campo **Secure Boot** para **Disabled**;
- Na guia **Main** defina **F12 Boot Menu** para **Enabled**, isso vai nos ajudar a bootar pelo pendrive;
- Ainda na guia **Main**, será ecessário desabilitar o Intel RST (funcionalidade que não irei explicar, disponível em computadores que usam SSD para armazenamento principal). Caso esta funcionalidade não esteja aparecendo, pressione **CTRL+S**. Altere **SATA Mode** para **AHCI**;
- Pressione **F10** no seu teclado, e confirme as alterações. Lembre-se de remover a senha antes deste passo, se for o caso;

## Iniciando a instalação do sistema
Novamente, com seu computador DESLIGADO, siga os passos:
- Plugue o Pendrive que gravou nos passos anteriores;
- Ligue o computador, e rapidamente pressiona a tecla F12 no seu teclado. Ou, no caso de outro modelo, pesquise pela tecla que acessa o boot menu;
- Selecione seu pendrive. Caso ele não esteja aparecendo, revise os passos anteriores;
- Confirme o inicio do **Ubuntu** pressionando enter;
- Escolha a linguagem de preferência, e clique em **Install Ubuntu**. Importante lembrar que nesse momento você pode escolher Try Ubuntu e testar o sistema operacional antes mesmo de instalar, claro que as funcionalidades são reduzidas, mas para quem é novo no linux, é válido verificar a interface e as primeiras impressões no Ubuntu;
- Selecione o Layout de teclado, que provavelmente estará correto. Para testar se tudo está certo, indico que teste seu teclado no campo disponível para isto. Teste principalmente os acentos, simbolos e o Ç. Clique em **Continuar**;
- No proximo passo, aconselho que conecte-se a internet se tiveres uma conexão razoável, e tempo. Conecte-se, e clique em **Continuar**.
- Aconselho que utilize a **Instalação normal** e marque as opções **Baixar atualizações enquanto instala Ubuntu** e **Instale softwares de terceiros para...**. Clique em **Continuar**;
- Para iniciantes aconselho utilizar a opção **Apagar disco e reinstalar o Ubuntu**. Clique em **Instalar agora**. OBS: Não será possível reverter isso. Todo o disco será Apagado.
- Confirme a instalação clicando em **Confirmar**;
- Agora, enquanto o sistema moceça a ser instalado, preencha os dados de fuso horário e o que mais for pedido. Clique em **Continuar**;
- Hora de preencher seus dados de usuário. Uma senha será necessária. O nome de usuari não deve conter espaços. Quando pronto, clique em **Continuar** e aguarde a instalação. No caso do meu Aspire 5, por contar com SSD, não levará pouco menos de 10 minutos, mas instalações em discos convencionais poderá levar mais de meia hora. Caso tenha escolhido atualizar durante a instalação, o término também dependerá da velocidade da sua conexão com a internet;
- Ao finalizar a instalação, confirme o reinicio do sistema, e remova a unidade USB quanso solicitado. Pressione enter.

Pronto