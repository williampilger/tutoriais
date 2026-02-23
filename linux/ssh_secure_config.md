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
PermitRootLogin no
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

Do mesmo modo que o item 2, a melhor prática aqui é: **quanto mais fechado, melhor**!
Permita apenas o que for necessário.

Se você seguir a melhor prática, seu computador nem estará esposto diretamente à rede (portas fechadas no modem), mas, de todo modo, ainda assim o firewall fechado é uma boa prática.

*Ativar o Firewall, e permitir o acesso SSH:*
```bash
# Liberar para acesso local
sudo ufw allow from 192.168.0.0/24 to any port 22 proto tcp

# E/OU liberar acesso a algum IP público específico da internet (melhor pratica que abrir)
sudo ufw allow from 123.123.123.123 to any port 22 proto tcp

# Ativar o Firewall, se ainda não estiver ativo
sudo ufw enable
```

Ou, se você optar por permitir o acesso externo mesmo, de qualquer lugar do mundo:

```bash
# ⚠️ Perigoso
sudo ufw allow 22/tcp
```


---



# 4️⃣ Acesso SSH com Chave-Pública

Lembre-se de combinar esta etapa com o passo 2️⃣. **Não tem nenhuma serventia usar a chave-pública se você continuar permitindo login com senha!**

**Outra observação interessante: Usar uma chave Física é bem mais seguro que um pendrive com uma chave pública**, se era isso que você pretendia fazer.
Considere adquirir uma *YubiKey* ou similar (que suporte ao FIDO2).

Se a ideia é portar sua chave pública em um pendrive, **definitivamente você DEVE substituí-la com frequência**. Coloque lembretes para fazer isso.

### 1) No **computador que vai conectar** (cliente): gerar a chave

Recomendado: **ed25519**.

```bash
ssh-keygen -t ed25519 -a 64 -C "seu_nome@seu_pc"

# ou, para gerar um arquivo de nome conhecido:
ssh-keygen -t ed25519 -a 64 -f ./chave_nomeada -C "seu_nome@seu_pc"
```

* Quando perguntar o caminho, pode aceitar o padrão: `~/.ssh/id_ed25519`
* Digite uma **passphrase** razoável (não precisa ser algo impossível, mas não subestime. Você tem o tempo entre o momento que sua chave foi roubada de você até o momento da descoberta da senha para desativá-la no servidor).
* O parâmetro `-a 64` define a quantidade de rodadas do OpenSSL para criptografar a senha. Quanto maior, mais demora para quebrar sua senha.
* O parâmetro `-f ./chave_nomeada` define o nome de saída do seu arquivo. Por padrão (se você não informar) os arquivos são salvos como `~/.ssh/id_ed25519` e `~/.ssh/id_ed25519.pub`
* O parâmetro `-C "seu_nome@seu_pc"` é apenas um identificador/comentário. Identifique com clareza, para que saiba de onde é esta chave.

Verifica se criou:

```bash
ls -l ~/.ssh/id_ed25519*

# ou, se tiver usado -f, veja o caminho q vc informou
```

### 2) Copiar a **chave pública** para o Ubuntu (autorizar a nova chave no servidor)

Jeito mais fácil (via SSH, se você já tiver acesso):

```bash
ssh-copy-id -i ~/.ssh/id_ed25519.pub usuario@IP_DO_SERVIDOR

# Ou, se usar uma porta diferente:
ssh-copy-id -i ~/.ssh/id_ed25519.pub -p 2222 usuario@IP_DO_SERVIDOR
```

Teste login:

```bash
ssh usuario@IP_DO_SERVIDOR
```

### 3) Se não tiver `ssh-copy-id`, ou não tiver acesso SSH ao servidor, ou tiver acesso físico ao servidor, faça manual

No cliente, mostre a chave pública:

```bash
cat ~/.ssh/id_ed25519.pub
```

No servidor (Ubuntu), como o usuário que vai logar:

```bash
mkdir -p ~/.ssh
chmod 700 ~/.ssh
chmod 600 ~/.ssh/authorized_keys
nano ~/.ssh/authorized_keys
```

Cole **uma linha inteira** da chave pública dentro do `authorized_keys`, salve e saia.

**Para maior segurança:** Defina um período de validade, especialmente se tiver com a intenção de colocar esta chave privada em um pendrive, adicionando uma validade no início da linha (no `~/.ssh/authorized_keys`):

```txt
ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAI... pedro@notebook_valida-pra-sempre

expiry-time="20261231235959Z" ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAI... pedro@notebook_valida-até-20261231
```

> Importante: antes de desativar senha, mantenha **uma sessão SSH aberta** (uma aba logada) pra não se trancar caso algo dê errado.


### 4) Testar login forçando método (no cliente):

Se você salvou o arquivo de credencial no diretório padrão do Client:

```bash
# Padrão - normalmente funciona
ssh usuario@IP_DO_SERVIDOR

# Se por ventura ele tentar usar outras formas de autenticar primeiro, pode forçar com:
ssh -o PreferredAuthentications=publickey -o PubkeyAuthentication=yes usuario@IP_DO_SERVIDOR
```

Se você tem o arquivo da chave Privada no diretório atual (colocou em um pendrive, por exemplo):

```bash
ssh -i ./id_ed25519 usuario@IP_DO_SERVIDOR
# O comando acima, com o -i adiciona a chave atual às disponíveis pra essa conexão.
# Calma, não copia ela pra máquina, só deixa "disponível".
# Mas, isso não GARANTE que essa seja a chave que seja usada, se houverem mais disponíveis.

#Ou, para forçar que outras chaves não tentem ser usadas
ssh -o IdentitiesOnly=yes -i ./id_ed25519 usuario@IP_DO_SERVIDOR

#Ou, se quiser ser ainda mais rigoroso, e remover o agente de identidade da jogada, pode usar:
ssh -o IdentityAgent=none -o IdentitiesOnly=yes -i ./id_ed25519 usuario@IP_DO_SERVIDOR
```

> Lembre-se, que se você usa uma porta diferente, precisará do `-p 12345` no comando.


Não use a chave em máquinas não confiáveis! Diferente de uma chave física de autenticação, o "segredo" da chave é legível pelo sistema, e pode ser copiado.
E se o sistema for malipulado, poderá registrar seu PIN da chave, e a partir daí, conseguir acesso ao seu servidor.

### 5) Problemas comuns

Para identificar os motivos, use a flag `-v` (verbose) no mometno da conexão:
> ssh -v -i ./id_ed25519 usuario@IP_DO_SERVIDOR

#### a) Arquivo de credenciais com privilégios "muito abertos"

**Importante:** um arquivo de chave privada, precisa ter permissão `600` dentro de uma pasta com permissão `700`, o que **não é possível dentro de pendrives FAT32 nem NTFS montados tradicionalmente, por exemplo**.
Esteja com o arquivo em uma partição padrão do Linux (quando estiver acessando por um linux).

Veja as permissções que seu arquivo tem:
```bash
stat -c '%a %n' /media/user/pendrive/sua_chave
```
Tem q dar `600` (ou pelo menos não ser `644`/`666`).

**Alternativa 1**: Re-montar a unidade com técnicas para ajustar as pemissões, ou copiar o arquivo para outro sistema de arquivos (pode não ser seguro).

**Alternativa 2**: Criar uma cópia "segura"
```bash
# Copia para a RAM, ajusta a permissão (este diretório é temporário na RAM em qualquer distro linux)
cp ./sua_chave /dev/shm/key_tmp && chmod 600 /dev/shm/key_tmp

# Usa a chave salva na RAM
ssh -i /dev/shm/key_tmp usuario@IP_DO_SERVIDOR
```

#### b) Cliente ignorando a chave e tentando com senha

Sempre que a chave falhar, é bem provável que caia no fallback e peça a senha. Neste caso, veja o verbose e tente identificar o motivo.

**Tenha CERTEZA de que sua chave pública está MESMO autorizada.** Escrever os termos, como `expiry-time` de modo errado, ou informar uma validade incorreta fazem a chave ser ignorada!



---




# 5️⃣ Faça auditorias com certa frequência

Crie rotinas **automatizadas** para auditar os LOGs do SSH e/ou do Firewall.

Se achar que não vale a pena, ou estiver já usando restrições mais severas, crie lembretes semanais/mensais para dar uma "olhada rápida" nos LOGs de eventos do sistema e saber o que está acontecendo.


## LOG 1 - Tentativas de login SSH

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



##  LOG 2 - Firewall `ufw`

Veja uma explicação completa [neste outro tutorial](./firewall_ufw.md).

Veja os logs do UFW com:
```bash
sudo grep -i ufw /var/log/syslog
```

