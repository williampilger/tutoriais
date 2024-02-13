# Instalar Speam via Terminal

## Fazer o download do instalador convencional
> Invoke-WebRequest -Uri "https://cdn.cloudflare.steamstatic.com/client/installer/SteamSetup.exe" -OutFile "setup.exe"

## Executar o instalador convencional

> Start-Process -FilePath "setup.exe" -ArgumentList "/S"

ou

> start /wait setup.exe /S


## Instalar usando o PowerShell e baixar da MS Store

Instalar o winget
> Install-Module -Name winget -Force -AllowClobber

Instalar a Steam
> winget install Steam --source msstore

