# llamafile portátil: LLM local para programação

> ⚠️ Tutorial gerado por Inteligência Artificial.
> 
> Testado conceitualmente com **llamafile v0.10.x** (2026). Flags mudam entre versões; na dúvida, rode `./llamafile --help`.

---

## 1. A ideia

O llamafile é **um único executável** que roda em Linux, macOS, Windows e BSD sem instalar nada.

Para máxima portabilidade, **não use o modelo "embutido"**. Use o binário puro + o arquivo `.gguf` separado:

- O Windows não executa arquivos acima de **4 GB**, e a maioria dos modelos bons de código passa disso.
- Você troca de modelo sem baixar o motor de novo.
- A pasta inteira cabe num pendrive/SSD externo e roda em qualquer máquina.

---

## 2. Estrutura da pasta

```
llm/
├── llamafile            # o binário (cópia: llamafile.exe para Windows)
├── llamafile.exe
├── models/
│   ├── qwen2.5-coder-7b-instruct-q4_k_m.gguf
│   └── ...
├── run.sh               # Linux / macOS
└── run.bat              # Windows
```

> Formate o pendrive em **exFAT** (lê/escreve nos três sistemas e aceita arquivos > 4 GB).

---

## 3. Montagem (uma vez só)

**3.1 Baixe o binário**

Em <https://github.com/mozilla-ai/llamafile/releases>, pegue o arquivo `llamafile-<versão>` da release mais recente (sem modelo, ~60 MB).

```bash
mv llamafile-* llamafile
chmod +x llamafile
cp llamafile llamafile.exe      # mesmo arquivo, só o nome muda
```

**3.2 Baixe um modelo** (ver tabela na seção 5)

```bash
mkdir -p models && cd models
curl -LO https://huggingface.co/<repo>/resolve/main/<arquivo>.gguf
```

Prefira a quantização **Q4_K_M** (melhor equilíbrio tamanho × qualidade). Se sobrar RAM, **Q5_K_M** ou **Q6_K**.

---

## 4. Rodar

**Linux / macOS — `run.sh`**

```bash
#!/bin/sh
cd "$(dirname "$0")"
MODEL="${1:-models/qwen2.5-coder-7b-instruct-q4_k_m.gguf}"
./llamafile -m "$MODEL" -c 16384 -ngl 999 --host 127.0.0.1 --port 8080
```

**Windows — `run.bat`**

```bat
@echo off
cd /d "%~dp0"
set MODEL=%1
if "%MODEL%"=="" set MODEL=models\qwen2.5-coder-7b-instruct-q4_k_m.gguf
llamafile.exe -m "%MODEL%" -c 16384 -ngl 999 --host 127.0.0.1 --port 8080
```

Depois abra **<http://localhost:8080>** (interface de chat no navegador).

| Flag | O que faz |
|---|---|
| `-m` | caminho do `.gguf` |
| `-c` | janela de contexto em tokens (mais = mais RAM) |
| `-ngl 999` | joga o máximo de camadas na GPU (ignorado se não houver) |
| `--host 0.0.0.0` | expõe na rede local (ex.: via Tailscale) |
| `--chat` | chat direto no terminal, sem navegador |

**Primeira execução — pegadinhas**

- **macOS:** se bloquear, `xattr -d com.apple.quarantine llamafile`.
- **Linux:** se der erro de formato, `sudo sh -c 'echo -1 > /proc/sys/fs/binfmt_misc/WSLInterop'` (conflito com WSL/binfmt) ou rode `sh ./llamafile ...`.
- **Windows:** antivírus às vezes reclama do binário "poliglota"; libere a pasta. Na v0.10.1 o Windows roda **só CPU**; GPU NVIDIA no Windows = via WSL2.
- **GPU:** Metal (Mac) é automático; CUDA/ROCm/Vulkan no Linux dependem do driver instalado na máquina.

---

## 5. Modelos recomendados (código: TS/React, SQL, etc.)

Tamanhos aproximados em **Q4_K_M**. RAM necessária ≈ tamanho do arquivo + 1–2 GB para contexto.

| Modelo | Arquivo | Pra quê | Repo no Hugging Face |
|---|---|---|---|
| **Qwen2.5-Coder 1.5B Instruct** | ~1 GB | Autocomplete (FIM) em máquina fraca | `Qwen/Qwen2.5-Coder-1.5B-Instruct-GGUF` |
| **Qwen2.5-Coder 3B Instruct** | ~2 GB | Notebook sem GPU, respostas rápidas | `Qwen/Qwen2.5-Coder-3B-Instruct-GGUF` |
| **Qwen3.5 4B** | ~3 GB | Generalista leve, bom em tool calling | `unsloth/Qwen3.5-4B-GGUF` |
| ⭐ **Qwen2.5-Coder 7B Instruct** | ~4,7 GB | **Padrão recomendado.** Ótimo em TS/SQL, contexto 128K, Apache 2.0 | `Qwen/Qwen2.5-Coder-7B-Instruct-GGUF` |
| **Qwen3.5 9B** | ~5,5 GB | Mais "raciocínio" e uso como agente | `unsloth/Qwen3.5-9B-GGUF` |
| **Qwen2.5-Coder 14B Instruct** | ~9 GB | Mais qualidade com 16 GB de RAM/VRAM | `Qwen/Qwen2.5-Coder-14B-Instruct-GGUF` |
| **Qwen3-Coder 30B-A3B** | ~18 GB | MoE: só 3B ativos → **roda bem até em CPU** com 32 GB RAM | `unsloth/Qwen3-Coder-30B-A3B-Instruct-GGUF` |

**Como escolher rápido**

- Até 8 GB RAM → **Coder 3B**
- 16 GB RAM / GPU 6–8 GB → **Coder 7B** ⭐
- GPU 12–16 GB → **Coder 14B** ou **Qwen3.5 9B**
- 32 GB RAM (mesmo sem GPU) → **Qwen3-Coder 30B-A3B**

> Para gerar SQL, cole o `CREATE TABLE` / schema do Prisma no prompt. Modelos pequenos acertam muito mais com o schema à vista.

---

## 6. Usar no editor / ferramentas

O llamafile expõe uma API **compatível com OpenAI**:

```
Base URL: http://localhost:8080/v1
API key:  qualquer coisa (ex.: "none")
Modelo:   qualquer nome
```

Funciona com **Continue.dev** (VS Code/JetBrains), **avante.nvim / CodeCompanion** (Neovim), Open WebUI, ou qualquer SDK OpenAI. A v0.10 também aceita a **API Messages da Anthropic**.

Teste rápido:

```bash
curl http://localhost:8080/v1/chat/completions \
  -H "Content-Type: application/json" \
  -d '{"messages":[{"role":"user","content":"Hook React em TS para debounce"}]}'
```

---

## 7. Checklist do pendrive

- [ ] Pendrive em exFAT
- [ ] `llamafile` + `llamafile.exe` na raiz
- [ ] Pelo menos um `.gguf` em `models/`
- [ ] `run.sh` (com `chmod +x`) e `run.bat`
- [ ] Testado em Linux e Windows antes de precisar
