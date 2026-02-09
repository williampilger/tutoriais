# Ativando o acesso remoto via VNC no Ubuntu

Eu estou usando o `Xubuntu` no momento.

Instalando as dependẽncias

```bash
sudo apt update
sudo apt install x11vnc
```

Defina uma senha:

```bash
x11vnc -storepasswd
```

Se quiser TESTAR:
> x11vnc -display :0 -auth guess -forever -shared -rfbauth ~/.vnc/passwd

Crie o arquivo de configuração:

```bash
sudo nano /etc/systemd/system/x11vnc.service
```

E cole:
```config
[Unit]
Description=x11vnc (share desktop)
After=display-manager.service network.target

[Service]
Type=simple
ExecStart=/usr/bin/x11vnc -display :0 -auth guess -forever -shared -rfbauth /home/$USER/.vnc/passwd -rfbport 5900
Restart=on-failure
RestartSec=2

[Install]
WantedBy=multi-user.target
```

Agora, Habilite e teste:
```bash
sudo systemctl daemon-reload
sudo systemctl enable --now x11vnc

# Testando...
sudo systemctl status x11vnc --no-pager -l
```

Configurando o Firewall, se for o caso:
```bash
# Use os IPs corretos, obviamente.
sudo ufw allow from 192.168.0.0/16 to any port 5900 proto tcp
sudo ufw status
```
