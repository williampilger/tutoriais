# Instalando o Python usando o Powershell

No Windows 10/11 você consegue instalar o **Python a nível de sistema (para todos os usuários)** usando o **winget** (gerenciador de pacotes que já vem embutido no Windows 11 e pode ser instalado no 10).

### Instalar Python para todos os usuários

Abra o **PowerShell como Administrador** e rode:

```powershell
winget install --id Python.Python.3.12 --scope machine --source winget --silent --accept-package-agreements --accept-source-agreements
```

🔎 Explicando:

* `--id Python.Python.3.12` → instala a versão 3.12 (pode trocar por `3.11` ou só `Python.Python.3` para a mais recente estável).
* `--scope machine` → instala para **todos os usuários do sistema**.
* `--silent` → não abre janela interativa.
* `--accept-package-agreements --accept-source-agreements` → evita prompts de confirmação.

### Verificar instalação

Depois de instalar, feche e abra de novo o PowerShell e teste:

```powershell
python --version
py --version
```

### Observações

* Isso coloca o Python no **`C:\Program Files\Python312\`** (ou equivalente).
* Ele adiciona o Python no PATH do sistema, então qualquer usuário pode rodar `python` ou `py`.
* Instala também o **pip**, que você pode usar para instalar pacotes globais.
