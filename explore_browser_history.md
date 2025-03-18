# Explorando manualmente o arquivo de Histórico de Navegação

Este método foi testado para explorar o histórico de navegação do Google Chrome, usando SQLiteDataBrowser.

---

### Download

Faça o download do [SQLiteDataBrowser](https://sqlitebrowser.org/).
Existem opções para todas as plataformas, e portáveis inclusive.

---

### Explorando o Histórico

Os dados de navegação costumam ficar em:

- `Google Chrome`
  - **Windows**: `C:\Users\<NomeDoUsuario>\AppData\Local\Google\Chrome\User Data\Default\History`
  - **Linux**: `~/.config/google-chrome/Default/History`
  - **macOS**: `~/Library/Application Support/Google/Chrome/Default/History`
- `Mozila Firefox`
  - **Windows**: `C:\Users\<NomeDoUsuario>\AppData\Roaming\Mozilla\Firefox\Profiles\<Perfil>\places.sqlite`
  - **Linux**: `~/.mozilla/firefox/<Perfil>/places.sqlite`
  - **macOS***: `~/Library/Application Support/Firefox/Profiles/<Perfil>/places.sqlite`
- `Microsoft Edge`
  - **Windows**: `C:\Users\<NomeDoUsuario>\AppData\Local\Microsoft\Edge\User Data\Default\History`
  - **Linux**: `~/.config/microsoft-edge/Default/History`
  - **macOS***: `~/Library/Application Support/Microsoft Edge/Default/History`
- `Safari`
  - **caminho comum**: `~/Library/Safari/History.db`
  - **Versões mais recentes**: `~/Library/Safari/CloudHistory/`
  - **Histórico de abas abertas***: `~/Library/Safari/LastSession.plist`
- `Opera`
  - **Windows**: `C:\Users\<NomeDoUsuario>\AppData\Roaming\Opera Software\Opera Stable\History`
  - **Linux**: `~/.config/opera/History`
  - **macOS***: `~/Library/Application Support/com.operasoftware.Opera/History`
- `Brave`
  - **Windows**: `C:\Users\<NomeDoUsuario>\AppData\Local\BraveSoftware\Brave-Browser\User Data\Default\History`
  - **Linux**: `~/.config/BraveSoftware/Brave-Browser/Default/History`
  - **macOS***: `~/Library/Application Support/BraveSoftware/Brave-Browser/Default/History`

```
⚠️ Os arquivos costumam ser protegicos para acesso.
Copie os arquivos para uma pasta separada antes de tentar abrir.
```

Abra o arquivo com o **SQLite Data Browser** clicando em `Importar Banco de Dados`.

Explore as telas, navegue pelos dados. É possível filtrar.

O Histórico fica na tabela `urls`.

#### Extra: Copiando o arquivo de histórico via SSH

