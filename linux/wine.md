# Instalar e configurar Wine no Ubuntu


## Instalar Wine e utilidades

Instalando o Wine:

> sudo apt-get install wine

Instalar o WineTricks, que é bem útil para instalar serviços extras:

> sudo apt-get install winetricks

Caso pretenda utilizar alguma aplicação com .NET:

> winetricks dotnet45

## Utilizando

Para abrir as configurações do wine use:

> winecfg

Para iniciar o explorador de arquivos do seu WinePrefix default, use:

> wine explorer

## Criando um novo WinePrefix

> WINEPREFIX=~/.wine_new_prefix winecfg

Onde `~/.wine_new_prefix` pode ser substituido pelo diretório/nome que você preferir.

Para criar um prefix x32, isso deve ser informado explicitamente:

> WINEPREFIX=~/.wine_new_prefix WINEARCH="win32" winecfg

## Remover seu prefix

> rm -rf ~/.wine_new_prefix

## Usando o novo WinePrefix

Para abrir o explorer, o exemplo é:

> WINEPREFIX=~/.wine_new_prefix wine explorer


## Interfaces Simples

Algumas interfaces e programinhas que facilitam o uso do wine:

- [Bootles - FlatHub](https://flathub.org/apps/details/com.usebottles.bottles);
- [WinBox - Snapcraft](https://snapcraft.io/winbox);


## Sobre

By: will.i.am | Balneário Camboriú - SC
