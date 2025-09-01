# Ficha Técnica do PC — Coleta via PowerShell

Use estes comandos para levantar um inventário avançado de hardware, drivers e sistema. Todos funcionam no PowerShell 5+ (Windows 10/11).
Dica: prefira `Get-CimInstance` em vez de `Get-WmiObject` por ser mais moderno.

## Tabela rápida de comandos

| Item                           | Comando PowerShell                                                     |                                                                                                                                                                                                                                                                                                                     |                                                                                  |
| ------------------------------ | ---------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------- |
| Fabricante, modelo do PC       | `Get-CimInstance Win32\_ComputerSystem`                                | `Select-Object Manufacturer, Model, SystemType, TotalPhysicalMemory`                                                                                                                                                                                                                                                |                                                                                  |
| Identificação do produto       | `Get-CimInstance Win32_ComputerSystemProduct`                         | `Select-Object Vendor, Name, Version, UUID, IdentifyingNumber`                                                                                                                                                                                                                                                      |                                                                                  |
| Placa-mãe                      | `Get-CimInstance Win32_BaseBoard`                                     | `Select-Object Manufacturer, Product, Version, SerialNumber`                                                                                                                                                                                                                                                        |                                                                                  |
| BIOS/UEFI                      | `Get-CimInstance Win32_BIOS`                                          | `Select-Object SMBIOSBIOSVersion, Manufacturer, Version, ReleaseDate`                                                                                                                                                                                                                                               |                                                                                  |
| CPU                            | `Get-CimInstance Win32_Processor`                                     | `Select-Object Name, Manufacturer, NumberOfCores, NumberOfLogicalProcessors, MaxClockSpeed, SocketDesignation`                                                                                                                                                                                                      |                                                                                  |
| GPU (modelo)                   | `Get-CimInstance Win32_VideoController`                               | `Select-Object Name, AdapterCompatibility, AdapterRAM, DriverVersion, DriverDate`                                                                                                                                                                                                                                   |                                                                                  |
| Driver de vídeo assinado       | `Get-CimInstance Win32_PnPSignedDriver -Filter "ClassName='Display'"` | `Select-Object DeviceName, DriverVersion, DriverDate, Manufacturer`                                                                                                                                                                                                                                                 |                                                                                  |
| Memória RAM — módulos          | `Get-CimInstance Win32_PhysicalMemory`                                | `Select-Object BankLabel, Capacity, Manufacturer, PartNumber, Speed, ConfiguredClockSpeed, SerialNumber`                                                                                                                                                                                                            |                                                                                  |
| Slots de memória               | `Get-CimInstance Win32_PhysicalMemoryArray`                           | `Select-Object MemoryDevices, MaxCapacity, MaxCapacityEx`                                                                                                                                                                                                                                                           |                                                                                  |
| Armazenamento — discos físicos | `Get-PhysicalDisk`                                                     | `Select-Object FriendlyName, MediaType, BusType, Size, SerialNumber, FirmwareVersion, HealthStatus`                                                                                                                                                                                                                 |                                                                                  |
| Armazenamento — discos lógicos | `Get-CimInstance Win32_DiskDrive`                                     | `Select-Object Model, InterfaceType, Size, SerialNumber, FirmwareRevision`                                                                                                                                                                                                                                          |                                                                                  |
| Partições e volumes            | `Get-Disk; Get-Partition; Get-Volume`                                  |                                                                                                                                                                                                                                                                                                                     |                                                                                  |
| Controladoras                  | `Get-CimInstance Win32_SCSIController, Win32_IDEController`          | `Select-Object Name, Manufacturer, PNPDeviceID`                                                                                                                                                                                                                                                                     |                                                                                  |
| Placas de rede ativas          | `Get-NetAdapter`                                                       | `Where-Object {$_.Status -eq 'Up'}`                                                                                                                                                                                                                                                                                  | `Select-Object Name, InterfaceDescription, LinkSpeed, MacAddress, DriverVersion` |
| Driver de rede assinado        | `Get-CimInstance Win32_PnPSignedDriver -Filter "ClassName='Net'"`     | `Select-Object DeviceName, DriverVersion, DriverDate, Manufacturer`                                                                                                                                                                                                                                                 |                                                                                  |
| Áudio                          | `Get-CimInstance Win32_SoundDevice`                                   | `Select-Object Name, Manufacturer, Status`                                                                                                                                                                                                                                                                          |                                                                                  |
| Monitor                        | `Get-CimInstance WmiMonitorID -Namespace root\wmi`                     | `ForEach-Object { [PSCustomObject]@{ Manufacturer=([System.Text.Encoding]::ASCII.GetString($_.ManufacturerName)) -replace '\0'; Product=([System.Text.Encoding]::ASCII.GetString($_.UserFriendlyName)) -replace '\0'; Serial=([System.Text.Encoding]::ASCII.GetString($_.SerialNumberID)) -replace '\0' } }` |                                                                                  |
| Sistema Operacional            | `Get-CimInstance Win32_OperatingSystem`                               | `Select-Object Caption, Version, BuildNumber, OSArchitecture, InstallDate, LastBootUpTime`                                                                                                                                                                                                                          |                                                                                  |
| Hotfixes/patches               | `Get-CimInstance Win32_QuickFixEngineering`                           | `Select-Object HotFixID, Description, InstalledOn`                                                                                                                                                                                                                                                                  |                                                                                  |
| BitLocker                      | `Get-BitLockerVolume`                                                  | `Select-Object MountPoint, VolumeType, ProtectionStatus, EncryptionMethod`                                                                                                                                                                                                                                          |                                                                                  |
| TPM                            | `Get-Tpm`                                                              |                                                                                                                                                                                                                                                                                                                     |                                                                                  |
| Bateria (se laptop)            | `Get-CimInstance Win32_Battery`                                       | `Select-Object Name, BatteryStatus, EstimatedChargeRemaining`                                                                                                                                                                                                                                                       |                                                                                  |
| Sensores térmicos*            | `Get-CimInstance MSAcpi_ThermalZoneTemperature -Namespace root\wmi`   | `Select-Object InstanceName, CurrentTemperature` *Observação: retorno costuma ser limitado e em décimos de Kelvin.                                                                                                                                                                                                  |                                                                                  |
| Periféricos USB                | `Get-PnpDevice -Class USB`                                             | `Select-Object FriendlyName, InstanceId, Status`                                                                                                                                                                                                                                                                    |                                                                                  |
| Dispositivos com erro          | `Get-PnpDevice`                                                        | `Where-Object Status -ne 'OK'`                                                                                                                                                                                                                                                                                        | `Select-Object Class, FriendlyName, Status, InstanceId`                          |
| Serviços                       | `Get-Service`                                                          | `Sort-Object Status, DisplayName`                                                                                                                                                                                                                                                                                     | `Select-Object Status, Name, DisplayName`                                        |
| Programas instalados           | `Get-Package`                                                          | `Select-Object Name, Version, ProviderName, Source`                                                                                                                                                                                                                                                                 |                                                                                  |

## Coleta completa em um único objeto

Cole tudo em um único objeto e exporte em JSON.

```powershell
$report = [PSCustomObject]@{
  ComputerSystem = Get-CimInstance Win32_ComputerSystem | Select-Object Manufacturer, Model, SystemType, TotalPhysicalMemory
  ComputerProduct = Get-CimInstance Win32_ComputerSystemProduct | Select-Object Vendor, Name, Version, UUID, IdentifyingNumber
  BaseBoard = Get-CimInstance Win32_BaseBoard | Select-Object Manufacturer, Product, Version, SerialNumber
  BIOS = Get-CimInstance Win32_BIOS | Select-Object SMBIOSBIOSVersion, Manufacturer, Version, ReleaseDate
  CPU = Get-CimInstance Win32_Processor | Select-Object Name, Manufacturer, NumberOfCores, NumberOfLogicalProcessors, MaxClockSpeed, SocketDesignation
  GPU = Get-CimInstance Win32_VideoController | Select-Object Name, AdapterCompatibility, AdapterRAM, DriverVersion, DriverDate
  DisplayDriver = Get-CimInstance Win32_PnPSignedDriver -Filter "ClassName='Display'" | Select-Object DeviceName, DriverVersion, DriverDate, Manufacturer
  RAMModules = Get-CimInstance Win32_PhysicalMemory | Select-Object BankLabel, Capacity, Manufacturer, PartNumber, Speed, ConfiguredClockSpeed, SerialNumber
  RAMArray = Get-CimInstance Win32_PhysicalMemoryArray | Select-Object MemoryDevices, MaxCapacity, MaxCapacityEx
  PhysicalDisks = Get-PhysicalDisk | Select-Object FriendlyName, MediaType, BusType, Size, SerialNumber, FirmwareVersion, HealthStatus
  DiskDrives = Get-CimInstance Win32_DiskDrive | Select-Object Model, InterfaceType, Size, SerialNumber, FirmwareRevision
  Partitions = Get-Partition | Select-Object DiskNumber, PartitionNumber, DriveLetter, Size, Type
  Volumes = Get-Volume | Select-Object DriveLetter, FileSystem, Size, SizeRemaining, HealthStatus
  Controllers = @{
    SCSI = Get-CimInstance Win32_SCSIController | Select-Object Name, Manufacturer, PNPDeviceID
    IDE  = Get-CimInstance Win32_IDEController | Select-Object Name, Manufacturer, PNPDeviceID
  }
  NetAdapters = Get-NetAdapter | Select-Object Name, InterfaceDescription, Status, LinkSpeed, MacAddress, DriverVersion
  NetDrivers = Get-CimInstance Win32_PnPSignedDriver -Filter "ClassName='Net'" | Select-Object DeviceName, DriverVersion, DriverDate, Manufacturer
  Sound = Get-CimInstance Win32_SoundDevice | Select-Object Name, Manufacturer, Status
  Monitors = Get-CimInstance WmiMonitorID -Namespace root\wmi | ForEach-Object {
    [PSCustomObject]@{
      Manufacturer = ([System.Text.Encoding]::ASCII.GetString($_.ManufacturerName)).Trim([char]0)
      Product      = ([System.Text.Encoding]::ASCII.GetString($_.UserFriendlyName)).Trim([char]0)
      Serial       = ([System.Text.Encoding]::ASCII.GetString($_.SerialNumberID)).Trim([char]0)
    }
  }
  OS = Get-CimInstance Win32_OperatingSystem | Select-Object Caption, Version, BuildNumber, OSArchitecture, InstallDate, LastBootUpTime
  Hotfixes = Get-CimInstance Win32_QuickFixEngineering | Select-Object HotFixID, Description, InstalledOn
  BitLocker = try { Get-BitLockerVolume | Select-Object MountPoint, VolumeType, ProtectionStatus, EncryptionMethod } catch { $null }
  TPM = try { Get-Tpm } catch { $null }
  Battery = Get-CimInstance Win32_Battery | Select-Object Name, BatteryStatus, EstimatedChargeRemaining
  USB = Get-PnpDevice -Class USB | Select-Object FriendlyName, InstanceId, Status
  DeviceIssues = Get-PnpDevice | Where-Object Status -ne 'OK' | Select-Object Class, FriendlyName, Status, InstanceId
  Services = Get-Service | Sort-Object Status, DisplayName | Select-Object Status, Name, DisplayName
  InstalledPackages = Get-Package | Select-Object Name, Version, ProviderName, Source
}

$path = "$env:PUBLIC\PC_Report_$(Get-Date -Format 'yyyyMMdd_HHmmss').json"
$report | ConvertTo-Json -Depth 6 | Out-File -FilePath $path -Encoding utf8
Write-Host "Relatório salvo em: $path"
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

## Observações

1. Alguns campos podem vir vazios dependendo do fabricante e drivers.
2. Em servidores, módulos como Storage Spaces Direct adicionam mais cmdlets.
3. Para sensores detalhados e SMART avançado, ferramentas de terceiros costumam ser necessárias.

Se quiser, monto uma versão que já exporta tudo em CSV e JSON para uma pasta padrão e assina a execução com política de scripts.
