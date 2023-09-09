# Windows 11: Usar menu de contexto padrão do windows 10

No explorador de arquivos, para abrir o menu completo, basta segurar a tecla `Shift` juntamente com o clique do mouse.

Se você quer que este seja o menu por padrão, execute o comando abaixo no **CMD**:

> reg add "HKCU\Software\Classes\CLSID\{86ca1aa0-34aa-4e8b-a509-50c905bae2a2}\InprocServer32" /f /ve

**Reinicie para fazer efeito!**


Para desfazer a ação:

> reg delete "HKCU\Software\Classes\CLSID\{86ca1aa0-34aa-4e8b-a509-50c905bae2a2}" /f
