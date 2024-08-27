# Brincadeiras para fazer via SSH (ou CMD, se tiver acesso)



## Abrir a gaveta de CD/DVD

> powershell -command "(New-Object -ComObject Shell.Application).Namespace(17).ParseName('E:').InvokeVerb('Eject')"

Trocar, obviamente, a unidade pela letra correta.
A letra da unidade pode ser vista com:

> wmic logicaldisk where "DriveType=5" get DeviceID, VolumeName



## Desligar a tela (até que o mouse seja movido)

> FALTA DESCOBRIR COMO (KKKKK, eu tinha isso em algum lugar)
