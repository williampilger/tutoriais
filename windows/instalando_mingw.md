# MinGW Compiller
MingW é um compilador minimalista para C/C++

## Instalando

Basta baixar o instalador no [site oficial](https://sourceforge.net/projects/mingw/files/Installer/mingw-get-setup.exe/download) e executar a instalação.
Mantenha o doretório padrão.

Apos a conclusão da primeira etapa de download e instalação, clique em **continuar** e selecione os médulos que deseja adicionar.

Navegue até **Installation** -> **Aply** e confirme a instalação.

Quando a instalação concluir, clique em **Close**, e feche o assistente de instalação.

## Adicionar o g++ ao path do windows

Pesquise no menu iniciar por `Variaveis de ambiente` e abra **Editar as variaveis de ambiente do sistema**. Confirme as permições de administrador.

Na guia **Avançado** clique no botão **Variaveis de Ambiente**.

Nas **Variaveis do sistema** localize o **Path** e clique em **Editar**.

Adicione uma linha com o endereço da instalação do WinGW, que deve ser `C:\MinGW\bin\`. Confirme as alterações e teste o comando no CMD, se tudo deu certo, deve funcionar.

