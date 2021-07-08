# Compilando e Instalando OpenSSL

OpenSSL é uma biblioteca completa e bastante avançada para criptografia e cálculo de cógigos Hash, para C++.
O passo a passo completo pode ser visto:
[Windows Notes](https://github.com/openssl/openssl/blob/master/NOTES-WINDOWS.md) e [Build and Install](https://github.com/openssl/openssl/blob/master/INSTALL.md)
Para instalar com um local diferente de `C:\Program Files (x86)\OpenSSL` ou uma versão diferente da de `32 Bits` consulte a documentação completa.

## Pré-Requisitos
- Visual Studio 2019 com:
  - Desenvolvimento para desktop com C++;
  - Desenvolvimento para desktop com .NET (Opcional);
  - Desenvolvimento com a Plataforma Universal do Windows (Opcional);
  - **Desenvolvimento para Linux com C++**
- Instalar (ou extrair) Perl, e adiciona-lo ao PATH do sistema (`...\perl\bin\`);
  - Download: [Site Oficial](http://strawberryperl.com/)
- Instalar (ou extrair) NASM, e adiciona-lo ao PATH do sistema;
  - Download: [Site Oficial](https://www.nasm.us/)

## Compilação e Instalação
- Abrir pasta do OpenSSL no Visual Studio 2019 (**COM PRIVILÉGIOS DE ADMINISTRADOR**)
  - Download: [OpenSSL - Repositório GitHub](https://github.com/openssl/openssl.git)
- Abrir terminal do compilador:
  - Terminal -> Novo Terminal
- Executar ferramenta VCVARSALL, compilar e instalar, para 32bits **(Tempo Necessário: Mais de 45min)**
  - > `C:\"Program Files (x86)"\"Microsoft Visual Studio"\2019\Professional\VC\Auxiliary\Build\vcvarsall.bat x86`
  - > `perl Configure VC-WIN32`
  - > `nmake`
  - > `nmake test`
  - > `nmake install`
  - **COMANDO COMPLETO**: `C:\"Program Files (x86)"\"Microsoft Visual Studio"\2019\Professional\VC\Auxiliary\Build\vcvarsall.bat x86 && perl Configure VC-WIN32 && nmake && nmake test && nmake install`
  - Adicionar a OpenSSL no PATH do sistema.

## Utilização

- Para usar a biblioteca, adicione a pasta de instalação do OpenSSL à lista de vinculação do pré-processador do Projeto:
  - Abrir propriedades do **projeto**.
  - Navegue até `Vinculador` -> `Entrada`-> `Dependências Adicionais` -> `Editar`
  - Adicione **o caminho completo** até o arquivo `.lib` compilado da OpenSSL. Exemplo: `C:\Program Files (x86)\OpenSSL\lib\libcrypto.lib`.
- Adicione a biblioteca ao Path do projeto:
  - Abrir propriedades do **projeto**.
  - Navegue até `C/C++` -> `Geral`-> `Diretórios de Inclusão Adicionais` -> `Editar`
  - Adicione **o caminho completo** até os arquivos de cabeçalho da biblioteca `.h` da OpenSSL. Exemplo: `C:\Program Files (x86)\OpenSSL\include\`.
- Confirme e salve as alterações.
