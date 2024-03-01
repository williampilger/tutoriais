# Monitorar o Uso da CPU via terminal

Isto pode ser útil em casos de acesso via SSH, para saber como está o desempenho da máquina.

## PowerShell

```p1
$cpuCounter = New-Object System.Diagnostics.PerformanceCounter("Processor", "% Processor Time", "_Total")
while ($true) {
    Write-Host "CPU Usage: $($cpuCounter.NextValue())%"
    Start-Sleep -Seconds 1
}

``` 

## Ou, em Python

Instale primeiro o `psutil`:

> pip install psutil

*cpu_monitor.py*
```py
import psutil
import time

def monitor_system(interval=1):
    print(f"{'Tempo':<10}{'CPU (%)':<10}{'Memória (%)':<12}{'Disco (%)':<10}")
    print("-" * 42)

    start_time = time.time()
    while True:
        current_time = time.time() - start_time
        cpu_usage = psutil.cpu_percent(interval=interval)
        memory_usage = psutil.virtual_memory().percent
        disk_usage = psutil.disk_usage('/').percent

        print(f"{current_time:<10.2f}{cpu_usage:<10}{memory_usage:<12}{disk_usage:<10}")

if __name__ == "__main__":
    monitor_system()

```
