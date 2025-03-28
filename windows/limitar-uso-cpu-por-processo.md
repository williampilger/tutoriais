# Limitar o uso de CPU por processo

Este método define a afinidade de núcleo para o processo em questão.

*PowerShell*
```ps1
$Process = Get-Process -Name nome_do_processo
$Process.ProcessorAffinity = 0b1111
```

Neste caso estão sendo setados os núcleos do 0 ao 3.

Você pode setar ele em valor binário, como `0b1111` ou em decimal, sendo `0x7` a correspondência no caso.

---

## Utilidade: Script para auxiliar na configuração da afinidade de CPU no Windows

*limitar-nucleos.ps1*: - *Este Script está também no [Repositório de Utilidades](https://github.com/williampilger/utilidades_gerais/blob/master/WindowsScripts/limitar-nucleos-por-processo.ps1)*
```ps1
$TotalCores = (Get-CimInstance Win32_Processor).NumberOfLogicalProcessors # obtem o numero total de nucleos disponiveis no sistema

while ($true) {
    $ProcessName = Read-Host "Digite o nome do processo"
    $Process = Get-Process -Name $ProcessName -ErrorAction SilentlyContinue
    if ($Process) { break }
    Write-Host "Processo nao encontrado. Tente novamente."
}
$Process = Get-Process -Name $ProcessName -ErrorAction Stop
$CurrentAffinity = $Process.ProcessorAffinity
$CurrentCores = ([Convert]::ToString([int]$CurrentAffinity, 2).ToCharArray() -match '1').Count

Write-Host "Total de nucleos disponiveis: $TotalCores"
Write-Host "Nucleos atualmente em afinidade com o processo: $CurrentCores"

# solicita um novo numero de nucleos
$NewCoreCount = Read-Host "Quantos nucleos deseja conceder ao processo? (1 - $TotalCores)"
$NewCoreCount = [int]$NewCoreCount
if ($NewCoreCount -lt 1 -or $NewCoreCount -gt $TotalCores) {
    Write-Host "Numero invalido de nucleos. Saindo..."
    Start-Sleep -Seconds 5
    exit
}
$NewAffinity = [int]([math]::Pow(2, $NewCoreCount) - 1)
$Process.ProcessorAffinity = $NewAffinity

Write-Host "Afinidade do processo atualizada com sucesso para $NewCoreCount nucleo(s)!"
Start-Sleep -Seconds 5
```

#### ⚠️ Pode ser necessário liberar a excecução de scripts

Entenda mais sobre isso na [pagina da Microsoft](https://learn.microsoft.com/pt-br/powershell/module/microsoft.powershell.core/about/about_execution_policies?view=powershell-7.5).

*Exemplo - PowerShell*
 > Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
