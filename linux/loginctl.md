# Gerenciador de Login do Linux (`loginctl`)

**Importante:** Nos exemplos, estou usando um `Ubuntu 25.04`, em `Março de 2026`.

O `loginctl` faz parte do `systemd`, e serve para gerenciar as sessões ativas dos usuários. Muito útil para administrar máquinas remotamente via SSH.

> **Atenção:** Ao listar os usuários/sessões ativos, você verá seu próprio acesso também, mesmo que seja via SSH.
> **Então, ao encerrar os acessos, tenha o cuidado de não encerrar sua própria sessão sem querer.**

---

## Listar as sessões ativas

```bash
loginctl list-sessions
```

Você verá algo como:

```txt
SESSION  UID USER   SEAT  LEADER CLASS         TTY                   IDLE SINCE
      1  119 gdm    -     4230   manager-early -                     no   -
     10 1000 wilger -     21042  user          -                     no   -
      4 1000 wilger -     8095   manager       -                     no   -
     c1  119 gdm    seat0 4192   greeter       tty1                  yes  26min ago
     c6 1000 wilger -     19607  user          chrome-remote-desktop no   -
```

Colunas importantes:

| Coluna    | Descrição                                              |
|-----------|--------------------------------------------------------|
| `SESSION` | ID da sessão                                           |
| `UID`     | ID do usuário                                          |
| `USER`    | Nome do usuário                                        |
| `SEAT`    | Assento físico (`seat0` = monitor/teclado local)       |
| `CLASS`   | Tipo: `user` (sessão normal), `manager` (systemd user) |
| `TTY`     | Terminal associado (`tty2` = segundo terminal virtual) |

---

## Identificar a sessão gráfica local

A sessão gráfica local é aquela que possui um `SEAT` (geralmente `seat0`) e um `TTY` (como `tty1` ou `tty2`).

Para confirmar o tipo da sessão (X11 ou Wayland):

```bash
loginctl show-session <SESSION_ID> | grep Type
```

Exemplo:

```bash
loginctl show-session 2 | grep Type
# Type=wayland
```

Para ver todas as propriedades da sessão:

```bash
loginctl show-session <SESSION_ID>
```

---

## Verificar se a sessão está bloqueada

```bash
loginctl show-session <SESSION_ID> | grep -i lock
```

Saída esperada quando bloqueada:

```
CanLock=yes
LockedHint=yes
```

---

## Desbloquear uma sessão (via SSH)

Útil quando a tela está bloqueada e você precisa desbloqueá-la remotamente para permitir, por exemplo, acesso via RDP ou compartilhamento de tela:

```bash
loginctl unlock-session <SESSION_ID>
```

Exemplo:

```bash
loginctl unlock-session 2
```

> **Atenção:** isso desbloqueia a tela imediatamente, sem exigir senha na máquina local. Use com cautela em ambientes compartilhados.

Para desbloquear todas as sessões de uma vez:

```bash
loginctl unlock-sessions
```

---

## Encerrar sessões

Para terminar uma sessão específica de forma limpa:

```bash
loginctl terminate-session <SESSION_ID>
```

Para encerrar todas as sessões de um usuário:

```bash
sudo loginctl terminate-user wilger
```

Para encerrar todas as sessões de todos os usuários:

```bash
sudo loginctl kill-user "*"
```

> **Atenção:** isso fecha a sessão gráfica do usuário, encerrando todos os programas abertos.

---

## Reiniciar o Display Manager SEM encerrar as sessões

Este **não é um comando do `loginctl`**, mas complementa o uso dele.

Serve para fazer todas as sessões gráficas voltarem para a tela de login:

```bash
# Ubuntu
sudo systemctl restart gdm

# Xubuntu ou Lubuntu
sudo systemctl restart lightdm

# Kubuntu
sudo systemctl restart sddm
```

---

## Outros comandos úteis

| Comando                              | Descrição                                  |
|--------------------------------------|--------------------------------------------|
| `loginctl list-users`                | Lista usuários com sessão ativa            |
| `loginctl show-user <USERNAME>`      | Detalhes do usuário logado                 |
| `loginctl lock-session <SESSION_ID>` | Bloqueia a tela da sessão                  |
| `loginctl lock-sessions`             | Bloqueia todas as sessões ativas           |
| `loginctl kill-session <SESSION_ID>` | Mata forçadamente a sessão (sem cleanup)   |

---

## Fluxo típico de uso remoto (via SSH)

```bash
# 1. Listar sessões
loginctl list-sessions

# 2. Identificar a sessão gráfica local (tem SEAT e TTY)
loginctl show-session 2 | grep Type

# 3. Verificar se está bloqueada
loginctl show-session 2 | grep -i lock

# 4. Desbloquear se necessário
loginctl unlock-session 2

# 5. Encerrar a sessão quando necessário
loginctl terminate-session 2
```
