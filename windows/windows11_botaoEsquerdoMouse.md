# Windows 11: Usar menu de contexto padrão do windows 10



## Método 1: Funciona nas versões mais recentes do windows

Salve o arquivo abaixo:

*WindowsOldContextMenu.reg*
```reg
Windows Registry Editor Version 5.00

[HKEY_CURRENT_USER\Software\Classes\CLSID\{86ca1aa0-34aa-4e8b-a509-50c905bae2a2}]

[HKEY_CURRENT_USER\Software\Classes\CLSID\{86ca1aa0-34aa-4e8b-a509-50c905bae2a2}\InprocServer32]
@=""
```

Dê dois cloques no arquivo, e pronto.

ou, cole os comandos diretamente no CMD:

```bat
reg add "HKEY_CURRENT_USER\Software\Classes\CLSID\{86ca1aa0-34aa-4e8b-a509-50c905bae2a2}" /f
reg add "HKEY_CURRENT_USER\Software\Classes\CLSID\{86ca1aa0-34aa-4e8b-a509-50c905bae2a2}\InprocServer32" /f
reg add "HKEY_CURRENT_USER\Software\Classes\CLSID\{86ca1aa0-34aa-4e8b-a509-50c905bae2a2}\InprocServer32" /ve /t REG_SZ /d "" /f
```

e Reinicie o explorador de arquivos:

> taskkill /f /im explorer.exe && start explorer.exe

### Desfazer

Caso precise desfazer isso, podes usar o comando abaixo, colado no CMD:

```bat
reg delete "HKEY_CURRENT_USER\Software\Classes\CLSID\{86ca1aa0-34aa-4e8b-a509-50c905bae2a2}" /f
```

Lembrando que o explorador de arquivos precisa ser reiniciado para fazer efeito.


--------------------------------------------------------------------------------------------------------------------------------

## Método 2: Funcionava nas primeiras versões do windows 11

No explorador de arquivos, para abrir o menu completo, basta segurar a tecla `Shift` juntamente com o clique do mouse.

Se você quer que este seja o menu por padrão, execute o comando abaixo no **CMD**:

> reg add "HKCU\Software\Classes\CLSID\{86ca1aa0-34aa-4e8b-a509-50c905bae2a2}\InprocServer32" /f /ve

**Reinicie para fazer efeito!**


Para desfazer a ação:

> reg delete "HKCU\Software\Classes\CLSID\{86ca1aa0-34aa-4e8b-a509-50c905bae2a2}" /f
