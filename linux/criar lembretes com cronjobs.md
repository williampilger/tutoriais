# Guia: Lembretes Automáticos via Cronjob (Linux)

Este guia cobre a configuração de lembretes que rodam em dias úteis, de hora em hora (07h às 18h), utilizando três níveis de interatividade.

## 1. Como abrir o Crontab

O Cron é o agendador de tarefas padrão do Linux. Para editar suas tarefas, use o comando:

```bash
crontab -e

```

Se for a primeira vez, selecione o editor `nano` (geralmente a opção 1).

---

## 2. Entendendo a Sintaxe de Tempo

Cada linha no Crontab segue o padrão de 5 campos de tempo antes do comando:

`* * * * * [comando]`

1. **Minuto** (0-59)
2. **Hora** (0-23)
3. **Dia do mês** (1-31)
4. **Mês** (1-12)
5. **Dia da semana** (0-6, onde 1-5 é Seg-Sex)

Para o intervalo das **07:00 às 18:00 em dias úteis**, usamos: `0 7-18 * * 1-5`.

---

## 3. As Três Opções de Notificação

Para que o Cron consiga exibir janelas na sua interface gráfica, precisamos declarar as variáveis `DISPLAY` e `DBUS_SESSION_BUS_ADDRESS`.

### Opção A: Notificação Discreta (Padrão)

Usa o sistema de notificações nativo. Se o "Não Perturbe" estiver ativo, ela será silenciada e enviada para a central de mensagens.

```cron
0 7-18 * * 1-5 DISPLAY=:0 DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/$(id -u)/bus notify-send "Lembrete" "Hora de beber água."

```

### Opção B: Notificação Crítica (Fura o "Não Perturbe")

Adiciona o parâmetro `-u critical`. Na maioria das distros, isso faz a notificação ignorar o modo silencioso e permanecer na tela até ser fechada manualmente.

```cron
0 7-18 * * 1-5 DISPLAY=:0 DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/$(id -u)/bus notify-send -u critical "Lembrete" "Levante e se alongue agora!"

```

### Opção C: Janela Zenity (Invasiva/Impossível de ignorar)

O Zenity cria uma caixa de diálogo real no centro da tela que interrompe o fluxo de trabalho até que você clique em "OK".

```cron
0 7-18 * * 1-5 DISPLAY=:0 Zenity --info --title="Pausa Obrigatória" --text="Beba água e descanse os olhos." --width=300

```

---

## 4. Comparativo de Métodos

| Método | Comando | Comportamento | Uso Recomendado |
| --- | --- | --- | --- |
| **Discreto** | `notify-send` | Balão padrão, respeita DND | Lembretes leves (ex: ler e-mail) |
| **Crítico** | `notify-send -u critical` | Balão persistente, fura DND | Lembretes importantes (ex: remédios) |
| **Zenity** | `zenity --info` | Janela de diálogo centralizada | Bloqueio de foco (ex: postura e água) |

---

## Notas de Configuração

1. **Dependência do Zenity:** Caso escolha a Opção C e o comando não funcione, instale-o com `sudo apt install zenity`.
2. **Variável de Usuário:** O trecho `$(id -u)` identifica automaticamente o seu ID de usuário (geralmente 1000) para garantir que a notificação apareça na sessão correta.
3. **Salvando:** Após colar a linha escolhida no `crontab -e`, salve com `Ctrl+O`, `Enter` e saia com `Ctrl+X`.

---

# Sobre

By: *github.com/williampilger*

**2026-02-17 12:21**

*Reescrito e organizado por `Google Gemini PRO`.* 
