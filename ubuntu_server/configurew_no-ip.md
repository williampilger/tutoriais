# Configurando NO-IP no Ubuntu server para acesso externo

## Instalando o No-IP DUC

O guida de instalação completo pode ser encontrado no (site do NO-IP)[https://www.noip.com/support/knowledgebase/installing-the-linux-dynamic-update-client-on-ubuntu/].

> cd /usr/local/src/

> sudo wget http://www.noip.com/client/linux/noip-duc-linux.tar.gz

> sudo tar xf noip-duc-linux.tar.gz

> cd noip-2.1.9-1/

Obs.: Este diretório pode variar conforme a versão.

> sudo make install

Para configurar seu login use:

> sudo /usr/local/bin/noip2 -C

Para executar o serviço use:

> sudo /usr/local/bin/noip2

