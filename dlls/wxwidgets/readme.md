# WX Widgets

Biblioteca para desenvolvimento de interfaces gráficas em C++.
Disponível para **Windows**, **MAC** e **Linux**.
Acesse o [site oficial](https://www.wxwidgets.org/) para saber mais, e fazer o download das releases.

Este tutorial segue os passos do *Pietro Martins De Oliveira*, no [Vídeo - Interfaces Gráficas (GUI) em C++ no Visual Studio 2019 (wxWidgets) - Tutorial 2020](https://www.youtube.com/watch?v=ueLhcsXGS_M)


## Instalação da Biblioteca com Visual Studio 2019

- Para começar, é necessário baixar os arquivos (atenção para usar a versão **STABLE**):
	- **Header Files** (Cabeçalhos. São arquivos universais, independente da arquitetura)
	- **Development Files** (Específicos para cada arquitetura -> **x32** ou **x64**)
	- **Release DLLs**  (Específicos para cada arquitetura -> **x32** ou **x64**)
- Extraia os três arquivos para um diretório de sua preferência. Aqui tomarei como exemplo `C:\MDA_PORT\bibliotecas\wxwidgets\`. Alguns arquivos conflitarão, podes sobrescrever ou ignorar, pois são idênticos.
- Criar e editar as variáveis de ambiente e o path do windows
	- Pesquise por *Variáveis de ambiente* no iniciar, e acesse **Editar as variáveis de ambiente do sistema**. Ou navegue por `Este Computador -> Propriedades -> Propriedades do sistema -> Avançado -> Variáveis de ambiente`.
	- Nas **Variáveis de ambiente do Sistema**, clique em **Novo...** e crie a variável `wxwin` com o valor de acordo com o caminho da sua extração. No exemplo ficou `C:\MDA_PORT\bibliotecas\wxwidgets`.
	- Adicione o caminho das bibliotecas `.lib` ao Path do Windows, nas **Variáveis de ambiente do Sistema**. No exemplo temos: `C:\MDA_PORT\bibliotecas\wxwidgets\lib\vc14x_dll`.

## Criando um pojeto teste.

- Abrir **Visual Studio** e criar novo projeto
	- Novo projeto de **Aplicativo do Windows Desktop** em **C++**;
	- No exemplo, nomeei como `WXWidgetsTeste`;
	- Por se tratar de um projeo de base, vêm acompanhado de uma série de arquivos desnecessários. Os *Arquivos de orgidem* podem ser todos eliminados. O conteúdo do arquivo *WXWidgetsTeste.cpp* também pode ser liminado. Na pasta *Arquivos de Cabeçalho* basta deixar o *framework.h* e *targetver.h*.
- Configurações do projeto;
	- Clique com  botão direito sobre o projeto, e em abra as **propriedades**;
	- No campo configuração mantenha **Todas as configurações**, defina a plataforma adequada (no meu caso, `x32`);
	- Na aba **C/C++** -> **Geral**, e edite os **Diretórios de inclusão Adicionais**, incluindo os diteórios `$(wxwin)/include/msvc` e `$(wxwin)/include` no primeiro campo;
	- Salve as alterações;
	- Na aba **C/C++** -> **Pré-Processador** edite o campo **Definições do pré-processador**, e acima da marcação **<opções diferentes>** no primeiro campo adicione `WXUSINGDLL`, `wxMSVC_VERSION_AUTO`, e `_CRT_SECURE_NO_WARNINGS`, um por linha, e aplique as alterações;
	- Na aba **C/C++** -> **Geração de código**, altere o campo **Biblioteca em Tempo de Execução** para **DLL de depuração Multithread(/MDd)**;
	- Salve as alterações;
	- Na aba **Vinculador** -> **Geral** e edite o campo **Diretórios de Bibliotecas Adicionais**, colocando o diretório para sua biblioteca. No exemplo temos `$(wxwin)/lib/vc142_dll`, que pode mudar conforme a versão da biblioteca baixada.
	- Aplique, e salve as alterações feitas nas propriedades.
- Compilando o projeto teste:
	- Cole o codigo exemplo de Hello World que você pode encontrar no final [página do proprio projeto](https://docs.wxwidgets.org/trunk/overview_helloworld.html) no seu arquivo `WXWidgetsTeste.cpp`
	- Execute a aplicação.

## Projeto exemplo

O projeto configurado e funcional está disponível [neste repositório](/WXWidgetsTeste).

## Outra forma de instalar a biblioteca (Sem Sucesso):

Como sujestão do Visual Studio, a biblioteca pode ser instalada através da linha de comando abaixo:

> vcpkg install wxwidgets:x86-windows
