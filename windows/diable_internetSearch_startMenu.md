# Desativando a pesquisa na Internet para no Menu Iniciar do Windows 11

Passo a passo completo pode ser visto no [PureInfoTech.com](https://pureinfotech.com/disable-search-web-results-windows-11/?utm_source=chatgpt.com), de onde tirei as informações para este procedimento.

Você pode executar o procedimento automaticamente usando o Terminal ou o Powershell.

*CMD -> Executado com priviégios de Administrador*
```bat
reg add "HKCU\Software\Policies\Microsoft\Windows\Explorer" /v DisableSearchBoxSuggestions /t REG_DWORD /d 1 /f
```

**OU**

*PowerShell*
```ps1
New-Item -Path "HKCU:\Software\Policies\Microsoft\Windows\Explorer" -Force
New-ItemProperty -Path "HKCU:\Software\Policies\Microsoft\Windows\Explorer" -Name "DisableSearchBoxSuggestions" -Value 1 -PropertyType DWORD -Force
```

**Reinicie o computador para aplicar as alterações**
