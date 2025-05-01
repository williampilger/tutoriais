# Servidor FTP para acesso local

Este script coloca para rodar um servidor FTP acessível na rede local pelos usuários locais do PC em questão.

Casa usuário do computador, com seus próprios login e senha, podem acessar suas pastas-raiz pelo FTP.


*Thanks ChatGPT for the most part of this script*


## Script

```sh
#!/bin/bash

sudo apt update
sudo apt install -y vsftpd

# Fazendo backup da configuração original
sudo cp /etc/vsftpd.conf /etc/vsftpd.conf.bkp

sudo bash -c 'cat > /etc/vsftpd.conf <<EOF
listen=YES
listen_ipv6=NO
anonymous_enable=NO
local_enable=YES
write_enable=YES
local_umask=022
dirmessage_enable=YES
use_localtime=YES
xferlog_enable=YES
connect_from_port_20=YES
chroot_local_user=YES
allow_writeable_chroot=YES
secure_chroot_dir=/var/run/vsftpd/empty
pam_service_name=vsftpd
rsa_cert_file=/etc/ssl/certs/ssl-cert-snakeoil.pem
rsa_private_key_file=/etc/ssl/private/ssl-cert-snakeoil.key
EOF'

sudo systemctl restart vsftpd
sudo systemctl enable vsftpd

echo ""
echo "✅ FTP configurado com sucesso!"
echo "➡️  Os usuários do sistema podem agora acessar via FTP usando o IP:"
hostname -I | awk '{print $1}'
echo "ℹ️  Exemplo: ftp://$(hostname -I | awk '{print $1}')"

```
