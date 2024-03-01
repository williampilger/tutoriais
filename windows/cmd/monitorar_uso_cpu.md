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

def monitor_cpu(interval=1):
    while True:
        # Uso total da CPU
        cpu_usage_total = psutil.cpu_percent(interval=interval)
        print(f"Uso total da CPU: {cpu_usage_total}%")

        # Uso da CPU por núcleo
        cpu_usage_per_core = psutil.cpu_percent(interval=None, percpu=True)
        for i, usage in enumerate(cpu_usage_per_core):
            print(f"Núcleo {i}: {usage}%")

        print("-" * 20)
        time.sleep(interval)

if __name__ == "__main__":
    monitor_cpu()
```
