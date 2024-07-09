# Limitar o uso de CPU por processo

Este método define a afinidade de núcleo para o processo em questão.

*PowerShell*
```ps1
$Process = Get-Process -Name nome_do_processo
$Process.ProcessorAffinity = 0b1111
```

Neste caso estão sendo setados os núcleos do 0 ao 3.

Você pode setar ele em valor binário, como `0b1111` ou em decimal, sendo `0x7` a correspondência no caso.
