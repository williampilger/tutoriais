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

Utilidade:

```ps1
$TotalCores = (Get-CimInstance Win32_Processor).NumberOfLogicalProcessors # obtém o número total de núcleos disponíveis no sistema

while ($true) {
    $ProcessName = Read-Host "Digite o nome do processo"
    $Process = Get-Process -Name $ProcessName -ErrorAction SilentlyContinue
    if ($Process) { break }
    Write-Host "Processo não encontrado. Tente novamente."
}
$Process = Get-Process -Name $ProcessName -ErrorAction Stop
$CurrentAffinity = $Process.ProcessorAffinity
$CurrentCores = [Convert]::ToString($CurrentAffinity, 2).ToCharArray() -match "1" | Measure-Object | Select-Object -ExpandProperty Count

Write-Host "Total de núcleos disponíveis: $TotalCores"
Write-Host "Núcleos atualmente em afinidade com o processo: $CurrentCores"

# solicita um novo número de núcleos
$NewCoreCount = Read-Host "Quantos núcleos deseja conceder ao processo? (1 - $TotalCores)"
$NewCoreCount = [int]$NewCoreCount
if ($NewCoreCount -lt 1 -or $NewCoreCount -gt $TotalCores) {
    Write-Host "Número inválido de núcleos. Saindo..."
    Start-Sleep -Seconds 5
    exit
}
$NewAffinity = (2 ** $NewCoreCount) - 1
$Process.ProcessorAffinity = $NewAffinity

Write-Host "Afinidade do processo atualizada com sucesso para $NewCoreCount núcleo(s)!"
Start-Sleep -Seconds 5
```
