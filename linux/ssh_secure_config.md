# Configuração segura de SSH para Linux

Se, por ventura, você resolver deixar um PC disponível para acesso externo via SSH, é bom tomar alguns cuidados.

```
⚠️ Saiba que EXISTE RISCO! Mesmo que você tome cuidado.
```

---

## Considerações Importantes

**Provavelmente**, você poderia resolver este problema usando *VPN*.
Se for o caso, faça, e pare de expor a porta publicamente.

Se, mesmo assim, **tiver certeza de que ista é a única saída**, tente:

- Tente usar uma porta diferente da `22`. Por dois motivos principais: ela é a porta padrão para SSH, então se ela estiver aberta, as pessoas sabem o que é (mas qualquer outra porta também é questão de minutos para algum servidor em torno do mundo ter te descoberto, literalmente);
- Restringir o acesso ao **seu IP exato**, ou uma região, se possível. Lembre-se: quanto menor a área de contato, melhor.
- Use SEMPRE senhas fortes, e troque as senhas com frequência!
- Inspecione o sistema frequentemente (crie lembretes/rotinas) para ver se não estão ocorrendo acessos indesejados;
- Quanto menos acesso interno/sensível sua máquina com SSH exposto tiver dentro da sua rede, melhor;
- Garanta que **apenas o(s) usuário(s) necessários** tenham acesso SSH habilitado. Não há necessidade de disponibilizar isso pra todos (muito menos o root).


# 1️⃣ Limite de tentativas - `fail2ban`

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


# 2️⃣ Faça auditorias de tentativas de login SSH com certa frequência

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

