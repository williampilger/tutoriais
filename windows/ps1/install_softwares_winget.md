# 📦 Instalando Programas com `winget`

O `winget` é o **Gerenciador de Pacotes do Windows**. Ele funciona parecido com o `apt` (Linux) ou `brew` (macOS), permitindo instalar, atualizar e remover programas direto pelo terminal.

## 🔧 Estrutura básica do comando

```powershell
winget install <ID-ou-nome>
```

### Variações úteis:

| Comando                 | O que faz                                                       |
| ----------------------- | --------------------------------------------------------------- |
| `winget search <nome>`  | Procura o software no repositório.                              |
| `winget install <ID>`   | Instala o software pelo **ID único** (mais confiável que nome). |
| `winget install <nome>` | Instala pelo nome (pode haver mais de uma opção).               |
| `winget show <ID>`      | Mostra detalhes sobre o pacote (versão, instalador, fonte).     |
| `winget list`           | Lista programas já instalados via Windows.                      |
| `winget upgrade`        | Mostra programas que têm atualizações disponíveis.              |
| `winget upgrade <ID>`   | Atualiza um software específico.                                |
| `winget uninstall <ID>` | Remove um programa.                                             |

### Parâmetros importantes:

* `--id <ID>` → instala usando o identificador único.
* `--scope machine` → instala para **todos os usuários do PC**.
* `--scope user` → instala só para o usuário atual.
* `--silent` → instalação sem janelas ou prompts.
* `--accept-package-agreements` e `--accept-source-agreements` → pula confirmações.
* `--version <número>` → instala versão específica.

---

## 📋 Exemplos práticos

### 1. Procurar e instalar o **VLC Player**

```powershell
winget search VLC
winget install --id VideoLAN.VLC --scope machine
```

### 2. Instalar o **Python 3.12**

```powershell
winget install --id Python.Python.3.12 --scope machine
```

### 3. Instalar o **Google Chrome** em modo silencioso

```powershell
winget install --id Google.Chrome --scope machine --silent
```

### 4. Atualizar todos os programas

```powershell
winget upgrade --all --silent
```

---

## 📊 Tabela – Softwares populares no `winget`

| Software           | ID (recomendado)             | Observação                |
| ------------------ | ---------------------------- | ------------------------- |
| Google Chrome      | `Google.Chrome`              | Navegador                 |
| Mozilla Firefox    | `Mozilla.Firefox`            | Navegador                 |
| Microsoft Edge     | `Microsoft.Edge`             | Atualiza Edge manualmente |
| VLC Media Player   | `VideoLAN.VLC`               | Player multimídia         |
| 7-Zip              | `7zip.7zip`                  | Compactador               |
| WinRAR             | `RARLab.WinRAR`              | Compactador               |
| Git                | `Git.Git`                    | Controle de versão        |
| Node.js (LTS)      | `OpenJS.NodeJS.LTS`          | Desenvolvimento           |
| Python 3.12        | `Python.Python.3.12`         | Linguagem de programação  |
| Visual Studio Code | `Microsoft.VisualStudioCode` | Editor de código          |
| Notepad++          | `Notepad++.Notepad++`        | Editor de texto           |
| Steam              | `Valve.Steam`                | Plataforma de jogos       |
| Discord            | `Discord.Discord`            | Comunicação               |
| WhatsApp Desktop   | `9NKSQGP7F2NH` (ID da Store) | Versão oficial            |
| Spotify            | `Spotify.Spotify`            | Música                    |
| Zoom               | `Zoom.Zoom`                  | Videoconferência          |

*(IDs podem variar — use `winget search <nome>` se der conflito.)*

---

👉 Dica: sempre prefira **`--id`** ao invés de só o nome, porque nomes podem se repetir ou variar.

---

# Sobre

By: `ChatGPT 5` - 2025-08-26 09:44

