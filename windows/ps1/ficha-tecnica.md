# Ficha Técnica do PC — Coleta via PowerShell

Use estes comandos para levantar um inventário avançado de hardware, drivers e sistema. Todos funcionam no PowerShell 5+ (Windows 10/11).
Dica: prefira `Get-CimInstance` em vez de `Get-WmiObject` por ser mais moderno.

## Tabela rápida de comandos

| Item                           | Comando PowerShell                                                                                    |
| ------------------------------ | ----------------------------------------------------------------------------------------------------- |
| Fabricante, modelo do PC       | `Get-CimInstance Win32_ComputerSystem \| Select-Object Manufacturer, Model, SystemType, TotalPhysicalMemory` |
| Identificação do produto       | `Get-CimInstance Win32_ComputerSystemProduct \| Select-Object Vendor, Name, Version, UUID, IdentifyingNumber` |
| Placa-mãe                      | `Get-CimInstance Win32_BaseBoard \| Select-Object Manufacturer, Product, Version, SerialNumber`      |
| BIOS/UEFI                      | `Get-CimInstance Win32_BIOS \| Select-Object SMBIOSBIOSVersion, Manufacturer, Version, ReleaseDate` |
| CPU                            | `Get-CimInstance Win32_Processor \| Select-Object Name, Manufacturer, NumberOfCores, NumberOfLogicalProcessors, MaxClockSpeed, SocketDesignation` |
| GPU (modelo)                   | `Get-CimInstance Win32_VideoController \| Select-Object Name, AdapterCompatibility, AdapterRAM, DriverVersion, DriverDate` |
| Driver de vídeo assinado       | `Get-CimInstance Win32_PnPSignedDriver -Filter "ClassName='Display'" \| Select-Object DeviceName, DriverVersion, DriverDate, Manufacturer` |
| Memória RAM — módulos          | `Get-CimInstance Win32_PhysicalMemory \| Select-Object BankLabel, Capacity, Manufacturer, PartNumber, Speed, ConfiguredClockSpeed, SerialNumber` |
| Slots de memória               | `Get-CimInstance Win32_PhysicalMemoryArray \| Select-Object MemoryDevices, MaxCapacity, MaxCapacityEx` |
| Armazenamento — discos físicos | `Get-PhysicalDisk \| Select-Object FriendlyName, MediaType, BusType, Size, SerialNumber, FirmwareVersion, HealthStatus` |
| Armazenamento — discos lógicos | `Get-CimInstance Win32_DiskDrive \| Select-Object Model, InterfaceType, Size, SerialNumber, FirmwareRevision` |
| Partições e volumes            | `Get-Disk; Get-Partition; Get-Volume`                                                                |
| Controladoras                  | `Get-CimInstance Win32_SCSIController, Win32_IDEController \| Select-Object Name, Manufacturer, PNPDeviceID` |
| Placas de rede ativas          | `Get-NetAdapter \| Where-Object {$_.Status -eq 'Up'} \| Select-Object Name, InterfaceDescription, LinkSpeed, MacAddress, DriverVersion` |
| Driver de rede assinado        | `Get-CimInstance Win32_PnPSignedDriver -Filter "ClassName='Net'" \| Select-Object DeviceName, DriverVersion, DriverDate, Manufacturer` |
| Áudio                          | `Get-CimInstance Win32_SoundDevice \| Select-Object Name, Manufacturer, Status`                      |
| Monitor                        | `Get-CimInstance WmiMonitorID -Namespace root\wmi \| ForEach-Object { [PSCustomObject]@{ Manufacturer=([System.Text.Encoding]::ASCII.GetString($_.ManufacturerName)).Trim([char]0); Product=([System.Text.Encoding]::ASCII.GetString($_.UserFriendlyName)).Trim([char]0); Serial=([System.Text.Encoding]::ASCII.GetString($_.SerialNumberID)).Trim([char]0) } }` |
| Sistema Operacional            | `Get-CimInstance Win32_OperatingSystem \| Select-Object Caption, Version, BuildNumber, OSArchitecture, InstallDate, LastBootUpTime` |
| Hotfixes/patches               | `Get-CimInstance Win32_QuickFixEngineering \| Select-Object HotFixID, Description, InstalledOn`      |
| BitLocker                      | `Get-BitLockerVolume \| Select-Object MountPoint, VolumeType, ProtectionStatus, EncryptionMethod`    |
| TPM                            | `Get-Tpm`                                                                                            |
| Bateria (se laptop)            | `Get-CimInstance Win32_Battery \| Select-Object Name, BatteryStatus, EstimatedChargeRemaining`       |
| Sensores térmicos*             | `Get-CimInstance MSAcpi_ThermalZoneTemperature -Namespace root\wmi \| Select-Object InstanceName, CurrentTemperature` |
| Periféricos USB                | `Get-PnpDevice -Class USB \| Select-Object FriendlyName, InstanceId, Status`                        |
| Dispositivos com erro          | `Get-PnpDevice \| Where-Object Status -ne 'OK' \| Select-Object Class, FriendlyName, Status, InstanceId` |
| Serviços                       | `Get-Service \| Sort-Object Status, DisplayName \| Select-Object Status, Name, DisplayName`         |
| Programas instalados           | `Get-Package \| Select-Object Name, Version, ProviderName, Source`                                   |


---


## Coleta completa em um único objeto

### Versão para arquivo .ps1 (recomendada)

Baixe o [script para criar um relatório JSON](./resources/technical-report.ps1) e execute com o *PowerShell* para criar um arquivo de relatório contendo os dados do PC.

### Versão simplificada para colar no console

Se preferir colar diretamente no PowerShell (menos recomendado):

```powershell
$r = @{}; $r.PC = Get-CimInstance Win32_ComputerSystem | Select Manufacturer,Model,TotalPhysicalMemory; $r.CPU = Get-CimInstance Win32_Processor | Select Name,NumberOfCores; $r.RAM = Get-CimInstance Win32_PhysicalMemory | Select Capacity,Speed; $r.GPU = Get-CimInstance Win32_VideoController | Select Name,AdapterRAM,DriverVersion; $r.Disk = Get-PhysicalDisk | Select FriendlyName,Size,HealthStatus; $r.OS = Get-CimInstance Win32_OperatingSystem | Select Caption,Version; $r | ConvertTo-Json -Depth 3
```


## Exportações úteis

```powershell
# CSVs separados por categoria
Get-CimInstance Win32_PhysicalMemory | Select BankLabel,Capacity,Manufacturer,PartNumber,Speed,ConfiguredClockSpeed,SerialNumber | Export-Csv RAM.csv -NoTypeInformation -Encoding UTF8
Get-CimInstance Win32_VideoController | Select Name,AdapterCompatibility,AdapterRAM,DriverVersion,DriverDate | Export-Csv GPU.csv -NoTypeInformation -Encoding UTF8
Get-PhysicalDisk | Select FriendlyName,MediaType,BusType,Size,SerialNumber,FirmwareVersion,HealthStatus | Export-Csv DiscosFisicos.csv -NoTypeInformation -Encoding UTF8
Get-Disk | Select Number,FriendlyName,SerialNumber,PartitionStyle,OperationalStatus | Export-Csv DiscosLogicos.csv -NoTypeInformation -Encoding UTF8
Get-NetAdapter | Select Name,InterfaceDescription,Status,LinkSpeed,MacAddress,DriverVersion | Export-Csv Redes.csv -NoTypeInformation -Encoding UTF8
Get-CimInstance Win32_OperatingSystem | Select Caption,Version,BuildNumber,OSArchitecture,InstallDate,LastBootUpTime | Export-Csv SO.csv -NoTypeInformation -Encoding UTF8
```

## Verificações rápidas de saúde

```powershell
# Uptime
(New-TimeSpan -Start (Get-CimInstance Win32_OperatingSystem).LastBootUpTime -End (Get-Date))

# Espaço em disco crítico
Get-Volume | Where-Object {$_.SizeRemaining -lt 10GB} | Select DriveLetter, SizeRemaining, Size

# Estado de discos físicos Storage Spaces
Get-PhysicalDisk | Select FriendlyName, HealthStatus, OperationalStatus

# Integridade do BitLocker
Get-BitLockerVolume | Select MountPoint, ProtectionStatus, LockStatus
```

## Observações e soluções para problemas comuns

### Problemas ao colar scripts longos no PowerShell

1. **Buffer do console**: Scripts muito longos podem causar erros de cursor/buffer
2. **Parsing de linha**: O PowerShell pode interpretar incorretamente quebras de linha
3. **Timeout de entrada**: Comandos muito extensos podem exceder limites

### Soluções recomendadas

1. **Use arquivos .ps1**: Sempre prefira salvar como arquivo e executar
2. **Execute por partes**: Divida scripts grandes em seções menores
3. **ISE ou VS Code**: Use editores que suportam melhor scripts PowerShell

### Comandos rápidos para teste

```powershell
# Teste rápido de funcionamento
Get-CimInstance Win32_ComputerSystem | Select Manufacturer, Model
Get-CimInstance Win32_Processor | Select Name, NumberOfCores
Get-PhysicalDisk | Select FriendlyName, Size, HealthStatus
```

### Alternativa: Script modular

Para máxima compatibilidade, use este approach:

```powershell
# Execute cada seção separadamente
$report = @{}

# Seção 1: Básico
$report.Sistema = Get-CimInstance Win32_ComputerSystem | Select Manufacturer, Model, TotalPhysicalMemory
$report.CPU = Get-CimInstance Win32_Processor | Select Name, NumberOfCores, MaxClockSpeed

# Seção 2: Armazenamento  
$report.Discos = Get-PhysicalDisk | Select FriendlyName, MediaType, Size, HealthStatus
$report.Volumes = Get-Volume | Select DriveLetter, FileSystem, Size, SizeRemaining

# Seção 3: Rede
$report.Rede = Get-NetAdapter | Where Status -eq 'Up' | Select Name, LinkSpeed, MacAddress

# Exportar
$path = "$env:PUBLIC\PC_Report_$(Get-Date -f 'yyyyMMdd_HHmmss').json"
$report | ConvertTo-Json -Depth 4 | Out-File $path -Encoding utf8
Write-Host "Salvo em: $path"
```
