# Configuração avançada do VSFTPD (Linux FTP Server)


## Instalação

> sudo apt install -y vsftpd


## Criando usuários (Usuários padrão do Linux)

Para criar um usuário de nome `nome_do_usuario` use:

> sudo adduser nome_do_usuario

E para definir uma senha para ele:

> sudo passwd nome_do_usuario



## Definindo o diretório padrão do usuário

> usermod -d /var/www/html_sample nome_do_usuario



## Alterar a propriedade de uma pasta

Para garantir acesso total às pastas para seu respectivo usuário, podemos alterar o proprietário para o que queremos:

> chown -R nome_do_usuario /var/www/html_sample



## Reiniciando o serviço

> /etc/init.d/vsftpd restart


