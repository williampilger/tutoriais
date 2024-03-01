# Monitorar o Uso da CPU via terminal

Isto pode ser útil em casos de acesso via SSH, para saber como está o desempenho da máquina.

```p1
$cpuCounter = New-Object System.Diagnostics.PerformanceCounter("Processor", "% Processor Time", "_Total")
while ($true) {
    Write-Host "CPU Usage: $($cpuCounter.NextValue())%"
    Start-Sleep -Seconds 1
}

``` 
