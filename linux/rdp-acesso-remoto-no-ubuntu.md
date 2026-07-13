# Configurando o RDP no `Ubuntu 25.04`

**Eu** neste momento estou usando o ubuntu mais recente, justamente pela consideravel melhoria no acesso remoto.

> Esta instalação básica, **em uma versão padrão do Ubuntu**, já vai sair funcionando para acesso remoto:
>
> - usando o **usuário e senha do usuário que se deseja acessar**;
> - mantendo a seção entre conexões do RDP;


```bash
sudo apt update
sudo apt install -y xrdp

# Adicionar xrdp ao grupo ssl-cert (obrigatório no Ubuntu moderno)
sudo adduser xrdp ssl-cert

sudo systemctl enable --now xrdp
sudo systemctl status xrdp
```

Obviamente, é necessário abrir o firewall, se o seu estiver fechado:

```bash
# Liberar apenas para rede local (recomendado)
sudo ufw allow from 192.168.0.0/16 to any port 3389 proto tcp

# Ou liberar geral (menos seguro)
# sudo ufw allow 3389/tcp

# Pra ver se está ativo e como estão as regras
sudo ufw status

# Reiniciar o serviço
sudo systemctl restart xrdp
```
