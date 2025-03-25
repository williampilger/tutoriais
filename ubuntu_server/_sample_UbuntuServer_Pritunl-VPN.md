# Exemplo de configuração: Criando uma VPN com o Pritunl

```
⚠️ Estou usando o Ubuntu Server, rodando no Microsoft Hyper-V, em um Windows 10 Pro.

⚠️ É óbvio que você precisará de um endereço público, e as portas abertas!!
   Então, tenha acesso ao modem e/ou roteador. Se seu provedor não lhe permite, vai precisar da ajuda deles.
```

---

## 1️⃣ Criação da VM, Configuração da rede, e Instalação do sistema

Não vou detalhar muito esta etapa, partindo do princípio que você já sabe o que faz.

### Criar um adaptador de rede Bridge

Para que a VM fique conectada à mesma rede que o servidor, vamos criar um adaptador de rede Bridge.

1. No seu servidor do Hyper-V, clique em `Gerenciador de Computador Virtual`;
2. Em `Novo computador de rede virtual`, crie um novo computador virtual `Externo`;
3. Dê um nome, como `Bridge Switch` (exemplo), à rede;
4. Em **Tipo de Conexão** selecione `Rede Externa`;
5. Selecione a placa de rede que deseja utilizar;
6. Marque a opção `Permitir que o sistema operacional de gerenciamento compartilhe este adaptador de rede`;
7. Salve, e **lembre de utilizar este adaptador de rede na sua VM**.

```
⚠️ No momento que você salvar estas alterações, é muito provável que a conexão do servidor caia por alguns instantes.
Então, se seu servidor estiver sendo usado para mais tarefas, garanta que é seguro.
⚠️ Se você estiver acessando o servidor por acesso remoto, é normal que você perca o acesso ao servidor por 10...15s.
```

### Criando a VM

Baixei a ISO do `Ubuntu Server 24.04.2 LTS`, e instalei a versão pequena do sistema.
Marquei a instalação do OpenSSH.

O Básico depois da primeira inicialização:

```bash
sudo apt update
sudo apt upgrade -y
sudo apt install -y net-tools
#sudo reboot
```

Eu, acesso a máquina via SSH... Só pra caso de dúvidas.
Isso permite copiar e colar no terminal, coisa que não é suportada pela janela do Hyper-V.

---

## 2️⃣ Instalar o Pritunl

Você pode [ver a documentação oficial para instalação aqui](https://docs.pritunl.com/docs/installation).

*Ubuntu 24.04*
```sh
# Origem: CÓPIA EXATA DO EXEMPLO DA DOCUMENTAÇÃO em 2025/03/20 12:14
sudo tee /etc/apt/sources.list.d/mongodb-org.list << EOF
deb [ signed-by=/usr/share/keyrings/mongodb-server-8.0.gpg ] https://repo.mongodb.org/apt/ubuntu noble/mongodb-org/8.0 multiverse
EOF

sudo tee /etc/apt/sources.list.d/openvpn.list << EOF
deb [ signed-by=/usr/share/keyrings/openvpn-repo.gpg ] https://build.openvpn.net/debian/openvpn/stable noble main
EOF

sudo tee /etc/apt/sources.list.d/pritunl.list << EOF
deb [ signed-by=/usr/share/keyrings/pritunl.gpg ] https://repo.pritunl.com/stable/apt noble main
EOF

sudo apt --assume-yes install gnupg

curl -fsSL https://www.mongodb.org/static/pgp/server-8.0.asc | sudo gpg -o /usr/share/keyrings/mongodb-server-8.0.gpg --dearmor --yes
curl -fsSL https://swupdate.openvpn.net/repos/repo-public.gpg | sudo gpg -o /usr/share/keyrings/openvpn-repo.gpg --dearmor --yes
curl -fsSL https://raw.githubusercontent.com/pritunl/pgp/master/pritunl_repo_pub.asc | sudo gpg -o /usr/share/keyrings/pritunl.gpg --dearmor --yes
sudo apt update
sudo apt --assume-yes install pritunl openvpn mongodb-org wireguard wireguard-tools

sudo ufw disable

sudo systemctl start pritunl mongod
sudo systemctl enable pritunl mongod
```

Pronto, ele já está acessível.

---

## 3️⃣ Acessar o Painel Web
Agora, acesse o Pritunl via navegador:
```
http://IP_DA_VM
```

```
⚠️ Aceite acessar a página mesmo não sendo segura, afinal, o servidor é seu...
```

Se estiver rodando diretamente na VM do Hyper-V, substitua `IP_DA_VM` por `localhost` no navegador.

---

## 4️⃣ Configuração Inicial

Siga as instruções no painel WEB.

Toda vez que ele pedir dados que você não sabe de onde vêm, ele vai dar um comando para você rodar no servidor para obter a informação.

---

## 5️⃣ Abrir portas no Firewall
Para permitir conexões VPN, libere as portas no Ubuntu:

```bash
sudo ufw allow 16575/udp   # OpenVPN (OU OUTRA PORTA!! Tem que ver a certa no seu servidor)
sudo ufw allow 51820/udp   # WireGuard
sudo ufw allow 443/tcp     # Painel Web SSL (se ativado)
sudo ufw allow 22/tcp      # Acesso SSH
sudo ufw enable
```

No **Hyper-V**, se necessário, abra as mesmas portas no **firewall do Windows**.
Isso se, e somente se, não estiver usando Bridge.

⚠️ **Lembre-se de que você precisa abrir as portas públicas para acesso ao servidor VPN de fora!**

---

## 6️⃣ Extra

#### Permitir MagickMackages (Wake-On-Lan) via VPN

Para permitir que os clientes acordem os PCs dentro do escritório, siga os passos:

1. Permitir IP Forwarding
   -  `sudo nano /etc/sysctl.conf`
   -  Adicione ou descomente `net.ipv4.ip_forward=1`
   -  Se precisar tornar isto válido agora (antes de reiniciar o servidor) rode:
      - ```bash
        echo 1 | sudo tee /proc/sys/net/ipv4/ip_forward
        sudo sysctl -w net.ipv4.ip_forward=1
        ``` 
2. Permitir Broadcast
   - ```bash
     sudo iptables -A INPUT -p udp -d 255.255.255.255 --dport 9 -j ACCEPT
     sudo iptables -A FORWARD -p udp -d 255.255.255.255 --dport 9 -j ACCEPT
     ```
3. Liberar Firewall (não sei se é realmente necessário, já que o pritunl usa iptables pra regrar isso)
   - ```bash
     sudo ufw allow 9/udp
     ```

---


## 📌 Conclusão

Agora seu servidor Pritunl está rodando no **Hyper-V com Ubuntu**!

- Lembre-se de colcoar a máquina para iniciar automaticamente junto com o windows.

- Lembre-se de fazer um backup da sua máquina configurada.

Alguns testes interessantes / curiosidades:

Acompanhar o fluxo de pacotes no servidor:
> sudo tcpdump -i any udp port 16575 -nn


---


## Sobre

By: **will.i.am** | github.com/williampilger

2025/03/20 15:05 | Bom Princípio - RS - Brasil
