# Configuração segura de SSH para Linux

Se, por ventura, você resolver deixar um PC disponível para acesso externo via SSH, é bom tomar alguns cuidados.

Estes 

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


# 2️⃣ Configurações do SSH

Você pode modificar as configurações do SSH da sua máquina para serem o mais restritas possível.
Veja como funciona:

Edite o arquivo de configurações (no meu caso, `Ubuntu 24.04 LTS`):
```bash
sudo nano /etc/ssh/sshd_config
```

E, se você estiver editando ainda o arquivo original, verá orientações sobre o uso nele, em forma de ocmentários.

*Lembrando que pode ser interessante fazer uma cópia do seu arquivo original.*

*Exemplo 1*
```ini
# Multiplas portas pro SSH (caso queira uma para acesso interno e outro externo, por exemplo)
Port 22
Port 2222

# Aqui, configurações GLOBAIS (valem sempre, sem condicional, a menos que sejam sobrescritas)
PubkeyAuthentication yes
PasswordAuthentication no
KbdInteractiveAuthentication no

# Configurações específicas para a porta 22 e IP especifico (sobrescrevem as globais)
Match LocalPort 22 Address 192.168.0.0/24
    PasswordAuthentication yes
    KbdInteractiveAuthentication yes

# Configurações específicas para os IPs específicos (sobrescrevem as globais)
#  > útil, por exemplo, se quiser aliviar as regras para a rede local, sem diferenciar portas
Match Address 192.168.0.0/24,10.0.0.0/8,172.16.0.0/12
    PasswordAuthentication yes
    KbdInteractiveAuthentication yes
```

Teste e recarregue:
```bash
sudo sshd -t
sudo systemctl reload ssh
```



---


# 3️⃣ Configurações do Firewall





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

