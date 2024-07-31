# Monitor completo para acesso WEB para qualquer máquina Linux

## Instalar e configurar

#### Install:

```sh
sudo apt update
sudo apt install -y netdata
sudo systemctl enable netdata
sudo systemctl start netdata
```

#### Configurando

Editar o arquivo de configurações:
```sh
sudo nano /etc/netdata/netdata.conf
```

E alterar o IP para `0.0.0.0`, para ter acesso de qualquer IP.
Caso não seja essa a ideia, mudar isso.

Reiniciar o serviço:
```sh
sudo systemctl restart netdata
```

Liberar firewall, se estiver ativo:
> sudo ufw allow 19999


## Acessando

Do mesmo, ou de outro PC, acesse: `http://SEU_IP_AQUI:19999`
