# Exemplo de funções pra log com cores no terminal (pra scripts)

```bash
# ---------------------------------------------------------------------------
# Utilidades
# ---------------------------------------------------------------------------

# Cores
RED=$'\e[31m'; GREEN=$'\e[32m'; YELLOW=$'\e[33m'; BLUE=$'\e[34m'; RESET=$'\e[0m'

# Funções prontas pra usar
log()  { printf '%s==>%s %s\n' "$BLUE" "$RESET" "$*"; }
ok()   { printf '%s ok%s %s\n' "$GREEN" "$RESET" "$*"; }
warn() { printf '%s !!%s %s\n' "$YELLOW" "$RESET" "$*"; }
die()  { printf '%serro%s %s\n' "$RED" "$RESET" "$*" >&2; exit 1; }

# Verificar se é root
[[ $EUID -eq 0 ]] || die "Rode com sudo."
```

Aí pra usar:
```bash

log "esse é um log"

ok "deu certo!"

die "programa encerrado por que vc não devia ter chegado aqui!"

```
