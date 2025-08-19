# Configuração segura de SSH para Linux

Se, por ventura, você resolver deixar um PC disponível para acesso externo via SSH, é bom tomar alguns cuidados.

```
⚠️ Saiba que EXISTE RISCO! Mesmo que você tome cuidado.
```

---

# 1️⃣ Ajustes Indicados


### 1. Não use a porta padrão

Use uma porta (externa) diferente da padrão. A porta `22` é bem visada para estes ataques.



### 2. Configure um limite de tentativas com `fail2ban`

Instale:

```bash
sudo apt install fail2ban -y
```

Edite config local:

```bash
sudo nano /etc/fail2ban/jail.local
```

Adicione:

```
[sshd]
enabled = true
maxretry = 3
findtime = 600
bantime = 3600
```

* `maxretry = 3` → máximo 3 falhas
* `findtime = 600` → janela de 10 min
* `bantime = 3600` → bloqueia IP por 1 hora

Reinicie:

```bash
sudo systemctl restart fail2ban
```

Ver status:

```bash
sudo fail2ban-client status sshd
```




---


# 2️⃣ Auditoria de tentativas de login SSH

O SSH registra tudo no **journalctl** ou no `/var/log/auth.log`.

### Consultar log de falhas

```bash
sudo journalctl -u ssh
```

ou diretamente:

```bash
sudo grep "Failed password" /var/log/auth.log
```

### Ver usuários inválidos

```bash
sudo grep "Invalid user" /var/log/auth.log
```

### Ver IPs que tentaram login

```bash
sudo grep "Failed password" /var/log/auth.log | awk '{print $(NF-3)}' | sort | uniq -c | sort -nr | head
```

Isso mostra quantas tentativas cada IP fez.

