# Monitorar uso de CPU por processos no PowerShell

```
✅ Esta funcionalidade funciona via SSH
```

Cole a definição da função no terminal (ou use ela no seu script):
```ps1
function TopCPU {
  param([int]$Seconds = 5)
  $cores = (Get-CimInstance Win32_ComputerSystem).NumberOfLogicalProcessors
  $p1 = Get-Process | Select-Object Id, Name, CPU
  Start-Sleep -Seconds $Seconds
  $p2 = Get-Process | Select-Object Id, Name, CPU
  $list = foreach ($p in $p2) {
    $prev = $p1 | Where-Object Id -eq $p.Id
    if ($prev) {
      $delta = ($p.CPU - $prev.CPU)
      [pscustomobject]@{
        Id         = $p.Id
        Name       = $p.Name
        PercentCPU = [math]::Round(($delta / $Seconds) * 100 / $cores, 1)
      }
    }
  }
  $list | Where-Object PercentCPU -gt 0 |
         Sort-Object PercentCPU -Descending |
         Select-Object -First 12
}
```

Execute o comando
```ps1
TopCPU 5
```

