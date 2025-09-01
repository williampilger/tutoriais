# Script de coleta completa de informações do sistema
# Para Download direto (pelo powershell):
#    Invoke-WebRequest -Uri "https://raw.githubusercontent.com/williampilger/tutoriais/refs/heads/master/windows/ps1/resources/technical-report.ps1" -OutFile "technical-report.ps1" -UseBasicParsing
# Para executar diretamente (pelo powershell):
#    Invoke-Expression (Invoke-WebRequest -Uri "https://raw.githubusercontent.com/williampilger/tutoriais/refs/heads/master/windows/ps1/resources/technical-report.ps1" -UseBasicParsing).Content

Write-Host "Coletando informações do sistema..." -ForegroundColor Green

$report = @{}

# Informações básicas do sistema
Write-Host "- Sistema e placa-mãe..." -ForegroundColor Yellow
$report.ComputerSystem = Get-CimInstance Win32_ComputerSystem | 
    Select-Object Manufacturer, Model, SystemType, TotalPhysicalMemory
$report.ComputerProduct = Get-CimInstance Win32_ComputerSystemProduct | 
    Select-Object Vendor, Name, Version, UUID, IdentifyingNumber
$report.BaseBoard = Get-CimInstance Win32_BaseBoard | 
    Select-Object Manufacturer, Product, Version, SerialNumber
$report.BIOS = Get-CimInstance Win32_BIOS | 
    Select-Object SMBIOSBIOSVersion, Manufacturer, Version, ReleaseDate

# Hardware principal
Write-Host "- CPU e GPU..." -ForegroundColor Yellow
$report.CPU = Get-CimInstance Win32_Processor | 
    Select-Object Name, Manufacturer, NumberOfCores, NumberOfLogicalProcessors, MaxClockSpeed, SocketDesignation
$report.GPU = Get-CimInstance Win32_VideoController | 
    Select-Object Name, AdapterCompatibility, AdapterRAM, DriverVersion, DriverDate
$report.DisplayDriver = Get-CimInstance Win32_PnPSignedDriver -Filter "ClassName='Display'" | 
    Select-Object DeviceName, DriverVersion, DriverDate, Manufacturer

# Memória
Write-Host "- Memória RAM..." -ForegroundColor Yellow
$report.RAMModules = Get-CimInstance Win32_PhysicalMemory | 
    Select-Object BankLabel, Capacity, Manufacturer, PartNumber, Speed, ConfiguredClockSpeed, SerialNumber
$report.RAMArray = Get-CimInstance Win32_PhysicalMemoryArray | 
    Select-Object MemoryDevices, MaxCapacity, MaxCapacityEx

# Armazenamento
Write-Host "- Discos e volumes..." -ForegroundColor Yellow
$report.PhysicalDisks = Get-PhysicalDisk | 
    Select-Object FriendlyName, MediaType, BusType, Size, SerialNumber, FirmwareVersion, HealthStatus
$report.DiskDrives = Get-CimInstance Win32_DiskDrive | 
    Select-Object Model, InterfaceType, Size, SerialNumber, FirmwareRevision
$report.Partitions = Get-Partition | 
    Select-Object DiskNumber, PartitionNumber, DriveLetter, Size, Type
$report.Volumes = Get-Volume | 
    Select-Object DriveLetter, FileSystem, Size, SizeRemaining, HealthStatus

# Controladoras
Write-Host "- Controladoras..." -ForegroundColor Yellow
$report.Controllers = @{
    SCSI = Get-CimInstance Win32_SCSIController | Select-Object Name, Manufacturer, PNPDeviceID
    IDE  = Get-CimInstance Win32_IDEController | Select-Object Name, Manufacturer, PNPDeviceID
}

# Rede e áudio
Write-Host "- Rede e áudio..." -ForegroundColor Yellow
$report.NetAdapters = Get-NetAdapter | 
    Select-Object Name, InterfaceDescription, Status, LinkSpeed, MacAddress, DriverVersion
$report.NetDrivers = Get-CimInstance Win32_PnPSignedDriver -Filter "ClassName='Net'" | 
    Select-Object DeviceName, DriverVersion, DriverDate, Manufacturer
$report.Sound = Get-CimInstance Win32_SoundDevice | 
    Select-Object Name, Manufacturer, Status

# Monitores
Write-Host "- Monitores..." -ForegroundColor Yellow
$report.Monitors = Get-CimInstance WmiMonitorID -Namespace root\wmi | ForEach-Object {
    [PSCustomObject]@{
        Manufacturer = ([System.Text.Encoding]::ASCII.GetString($_.ManufacturerName)).Trim([char]0)
        Product      = ([System.Text.Encoding]::ASCII.GetString($_.UserFriendlyName)).Trim([char]0)
        Serial       = ([System.Text.Encoding]::ASCII.GetString($_.SerialNumberID)).Trim([char]0)
    }
}

# Sistema operacional
Write-Host "- Sistema operacional..." -ForegroundColor Yellow
$report.OS = Get-CimInstance Win32_OperatingSystem | 
    Select-Object Caption, Version, BuildNumber, OSArchitecture, InstallDate, LastBootUpTime
$report.Hotfixes = Get-CimInstance Win32_QuickFixEngineering | 
    Select-Object HotFixID, Description, InstalledOn

# Segurança
Write-Host "- BitLocker e TPM..." -ForegroundColor Yellow
$report.BitLocker = try { 
    Get-BitLockerVolume | Select-Object MountPoint, VolumeType, ProtectionStatus, EncryptionMethod 
} catch { 
    "BitLocker não disponível ou erro ao acessar" 
}
$report.TPM = try { 
    Get-Tpm 
} catch { 
    "TPM não disponível ou erro ao acessar" 
}

# Dispositivos
Write-Host "- Dispositivos USB e problemas..." -ForegroundColor Yellow
$report.Battery = Get-CimInstance Win32_Battery | 
    Select-Object Name, BatteryStatus, EstimatedChargeRemaining
$report.USB = Get-PnpDevice -Class USB | 
    Select-Object FriendlyName, InstanceId, Status
$report.DeviceIssues = Get-PnpDevice | Where-Object Status -ne 'OK' | 
    Select-Object Class, FriendlyName, Status, InstanceId

# Serviços e software
Write-Host "- Serviços e programas..." -ForegroundColor Yellow
$report.Services = Get-Service | Sort-Object Status, DisplayName | 
    Select-Object Status, Name, DisplayName
$report.InstalledPackages = try {
    Get-Package | Select-Object Name, Version, ProviderName, Source
} catch {
    "Erro ao obter lista de pacotes instalados"
}

# Exportação
$timestamp = Get-Date -Format 'yyyyMMdd_HHmmss'
$path = "$env:PUBLIC\PC_Report_$timestamp.json"

Write-Host "Exportando relatório..." -ForegroundColor Green
$report | ConvertTo-Json -Depth 6 | Out-File -FilePath $path -Encoding utf8

Write-Host "`nRelatório salvo em: $path" -ForegroundColor Green
Write-Host "Tamanho do arquivo: $([math]::Round((Get-Item $path).Length / 1KB, 2)) KB" -ForegroundColor Cyan

# Também criar um resumo rápido
$summaryPath = "$env:PUBLIC\PC_Summary_$timestamp.txt"
@"
=== RESUMO DO SISTEMA - $(Get-Date) ===

SISTEMA: $($report.ComputerSystem.Manufacturer) $($report.ComputerSystem.Model)
CPU: $($report.CPU[0].Name)
RAM: $([math]::Round($report.ComputerSystem.TotalPhysicalMemory / 1GB, 2)) GB
OS: $($report.OS.Caption) $($report.OS.Version)

GPU Principal: $($report.GPU[0].Name)
Discos: $($report.PhysicalDisks.Count) disco(s) físico(s)
Problemas detectados: $($report.DeviceIssues.Count) dispositivo(s)

Relatório completo em: $path
"@ | Out-File -FilePath $summaryPath -Encoding utf8

Write-Host "Resumo salvo em: $summaryPath" -ForegroundColor Cyan