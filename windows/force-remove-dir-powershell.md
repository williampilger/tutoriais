# Excluir um diretório, mesmo que esteja em uso e não seja de sua propriedade

Este scrip foi escrito pelo `ChatGPT 4o`, thanks.
E está disponível em RAW [no repositório de utilidades](https://github.com/williampilger/utilidades_gerais/blob/master/WindowsScripts/force-remove-dir.ps1);

Assuma a propriedade da pasta
```ps1
takeown /F $directory /R /D Y
```

Conceder permissões de controle total ao grupo Administradores
```ps1
icacls $directory /grant Administrators:F /T
```

Fechar processos relacionados ao diretório
```ps1
$processes = Get-Process | Where-Object { $_.Path -like "$directory\*" }
$processes | Stop-Process -Force
```

Excluir a pasta e todo o seu conteúdo
```ps1
Remove-Item -Path $directory -Recurse -Force
```
