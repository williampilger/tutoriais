# Habilitar o Acesso SSH no Windows

Caso você queira deixar sua máquina `Windows` acessível via `SSH`, siga os passos abaixo:

---

## Método 2 - Via Interface Gráfica

Vá para `Configurações`->`Sistema`->`Recursos Opcionais`->`Adicionar Recurso`

Procure por `OpenSSH Server` (ou `Servidor OpenSSH` em Português) e instale-o.

Abra o `Gerenciado de Serviços` (No executar, digite `services` e pressione enter)

Procure pelo `OpenSSH SSH Server`, e modifique a configuração de inicialização para **Automático** (e inicie o serviço manualmente se quiser usa-lo logo)

---

## Método 1 - Via Interface Texto (Power Shell)

Abra o `PowerShell` **com privilégios de administrador**, e:

Para verificar se os serviços estão instalados:
> Get-WindowsCapability -Online | ? Name -like 'OpenSSH*'

Para instalar:
> Add-WindowsCapability -Online -Name OpenSSH.Server~~~~0.0.1.0

Iniciar o serviço agora:
> Start-Service sshd

Configurar o serviço para iniciar automaticamente com o computador:
> Set-Service -Name sshd -StartupType 'Automatic'

Verificando se o SSH está liberado no Firewall:
> Get-NetFirewallRule -Name *ssh*

Configurar o PowerShell como padrão para o SSH:
> New-ItemProperty -Path "HKLM:\SOFTWARE\OpenSSH" -Name DefaultShell -Value "C:\Windows\System32\WindowsPowerShell\v1.0\powershell.exe" -PropertyType String -Force

**Comando completo**
```ps1
Add-WindowsCapability -Online -Name OpenSSH.Server~~~~0.0.1.0
Set-Service -Name sshd -StartupType 'Automatic'
New-ItemProperty -Path "HKLM:\SOFTWARE\OpenSSH" -Name DefaultShell -Value "C:\Windows\System32\WindowsPowerShell\v1.0\powershell.exe" -PropertyType String -Force
Start-Service sshd
```

Caso você precise trocar o padrão do CMD para o PowerShell, já pelo SSH, você pode usar:
```ps1
powershell -Command "New-ItemProperty -Path 'HKLM:\SOFTWARE\OpenSSH' -Name DefaultShell -Value 'C:\Windows\System32\WindowsPowerShell\v1.0\powershell.exe' -PropertyType String -Force"
```

Ou, para o Powershell 7 (se instalado)
```ps1
powershell -Command "New-ItemProperty -Path 'HKLM:\SOFTWARE\OpenSSH' -Name DefaultShell -Value 'C:\Program Files\PowerShell\7\pwsh.exe' -PropertyType String -Force"
```

## Habilitando transmissão de interface gráfica

Para que seja possível executar aplicações gráficas usando SSH, é necessário instalar um servidor `X` no host.

Baixe a versão "oficial" na [origem oficial, no sourceforce](https://sourceforge.net/projects/xming/).

Para acessar a máquina usando o servidor X, use:
> ssh -X user@hostname



## About

By: **Will.i.am** | **github.com/williampilger**

Fonts:

- [vídeo do Monflix no YouTube](https://www.youtube.com/watch?v=E8ziCZeaeoU);
- [Artigo SIEMENS sobre o SSH](https://docs.plm.automation.siemens.com/content/polarion/19.3/help/en_US/polarion_linux_installation/configure_ole_object_support_and_attachment_preview_generator/install_openssh.html);
