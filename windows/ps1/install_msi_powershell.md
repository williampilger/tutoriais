# Instalar MSI pelo PowerShell

Exemplo: Para baixar e isntalar o `Google Remote Desktop`:

```ps1
$msi = "$env:TEMP\chromeremotedesktophost.msi"

Invoke-WebRequest `
    -Uri "https://dl.google.com/edgedl/chrome-remote-desktop/chromeremotedesktophost.msi" `
    -OutFile $msi

Start-Process msiexec.exe `
    -ArgumentList "/i `"$msi`" /qn /norestart" `
    -Wait

```
