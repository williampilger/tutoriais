# Exemplo de configuração: Criando uma VPN com o Pritunl

```
ℹ️ Estou usando o Ubuntu Server, rodando no Microsoft Hyper-V, em um Windows 10 Pro.
```

## 1️⃣ Criação da VM e Instação do sistema

Não vou detalhar esta etapa.

Baixei a ISO do `Ubuntu Server 24.04.2 LTS`, e instalei a versão pequena do sistema.
Marquei a instalação do OpenSSH.

O Básico depois da primeira inicialização

```bash
sudo apt update
sudo apt upgrade -y
#sudo reboot
```

Eu, acesso a máquina via SSH... Só pra caso de dúvidas.
Isso permite copiar e colar no terminal, coisa que não é suportada pela janela do Hyper-V.



## **Instalar o MongoDB**
O **Pritunl** precisa do **MongoDB** para armazenar dados.

```bash
sudo apt install -y mongodb
sudo systemctl enable --now mongodb
```

Verifique se está rodando:
```bash
systemctl status mongodb
```

---

## **2️⃣ Instalar o Pritunl**
Adicione o repositório oficial:

```bash
echo "deb https://repo.pritunl.com/stable/apt jammy main" | sudo tee /etc/apt/sources.list.d/pritunl.list
```

Adicione a chave GPG:

```bash
sudo apt install -y gnupg curl
curl -fsSL https://repo.pritunl.com/stable/apt/gpg.key | sudo tee /etc/apt/trusted.gpg.d/pritunl.asc
```

Atualize os pacotes e instale o Pritunl:

```bash
sudo apt update
sudo apt install -y pritunl
```

Inicie o serviço:
```bash
sudo systemctl enable --now pritunl
```

Verifique se está rodando:
```bash
systemctl status pritunl
```

---

## **3️⃣ Acessar o Painel Web**
Agora, acesse o Pritunl via navegador:
```
http://IP_DA_VM
```

Se estiver rodando diretamente na VM do Hyper-V, substitua `IP_DA_VM` por `localhost` no navegador.

---

## **4️⃣ Configuração Inicial**
1. **Obter a chave de setup do Pritunl**  
   Rode o comando abaixo na VM:
   ```bash
   sudo pritunl setup-key
   ```
   Copie a chave gerada.

2. **Login inicial**  
   - Usuário: `pritunl`
   - Senha: Rode o comando abaixo na VM para obter a senha:
     ```bash
     sudo pritunl default-password
     ```

3. **Criar uma Organização e Usuário**  
   No painel, crie:
   - **Uma organização**
   - **Um usuário VPN**
   - **Um servidor VPN** com OpenVPN ou WireGuard.

4. **Gerar Configuração**  
   Baixe o arquivo de configuração no painel para conectar clientes.

---

## **5️⃣ Abrir portas no Firewall**
Para permitir conexões VPN, libere as portas no Ubuntu:

```bash
sudo ufw allow 1194/udp  # OpenVPN (se estiver usando)
sudo ufw allow 51820/udp # WireGuard
sudo ufw allow 443/tcp   # Painel Web SSL (se ativado)
sudo ufw enable
```

No **Hyper-V**, se necessário, abra as mesmas portas no **firewall do Windows**.

---

## **📌 Conclusão**
Agora seu servidor Pritunl está rodando no **Hyper-V com Ubuntu**! 🎉  

Você pode conectar clientes **Windows, Linux, Mac e Android** com os arquivos gerados no painel. Se precisar de desempenho máximo, **considere rodar o WireGuard nativamente no Linux**. 🚀
