# Excluir um diretório, mesmo que esteja em uso e não seja de sua propriedade

Este scrip foi escrito pelo `ChatGPT 4o`, thanks.

```ps1
# Solicitar o nome do diretório a ser excluído
$directory = Read-Host "Digite o caminho completo do diretório que deseja excluir"

# Verificar se o diretório existe
if (Test-Path -Path $directory) {
    # Assumir a propriedade da pasta e todos os arquivos e subpastas
    takeown /F $directory /R /D Y

    # Conceder permissões de controle total ao grupo Administradores
    icacls $directory /grant Administrators:F /T

    # Fechar processos relacionados ao diretório
    $processes = Get-Process | Where-Object { $_.Path -like "$directory\*" }
    $processes | Stop-Process -Force

    # Excluir a pasta e todo o seu conteúdo
    Remove-Item -Path $directory -Recurse -Force

    Write-Host "O diretório foi excluído com sucesso."
} else {
    Write-Host "O diretório especificado não existe."
}
```
