# Instalar o Google Remote Desktop via SSH

Isso consiste em:
  1. Baixar o Instalador
  2. Executar o instalador
  3. Configurar o acesso

```ps1
$msi = "$env:TEMP\chromeremotedesktophost.msi"
Invoke-WebRequest -Uri "https://dl.google.com/edgedl/chrome-remote-desktop/chromeremotedesktophost.msi" -OutFile $msi
Start-Process msiexec.exe -ArgumentList "/i `"$msi`" /qn /norestart" -Wait
Remove-Item $msi
```

Depois, acesse o [Google Remote Desktop](https://remotedesktop.google.com) e acesse a guia **Configure por SSH**;

Pule a primeira etapa (que tem as orientações pra baixar);

Gere o comando, e cole ele no terminal SSH;
