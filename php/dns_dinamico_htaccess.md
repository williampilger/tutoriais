# Configurar restrição por IP com DNS dinâmico

Como configurar restrição de acesso por IP para um DNS Dinâmico no Apache HTACCESS.

## Iniciando

Primeiro crie um host no seu provedor de DNS Dinâmico preferido, eu uso [No-IP](noip.com).

Para ver como instalar o DUC no seu PC linux, veja [esse tutorial](../ubuntu_server/configurew_no-ip.md).

Para instalar o DUC no windows, confira no site do No-IP as orientações, é bastante simples.

## Script para atualizar o endereço

A atualização do endereço de IP autorizado não é automática no servidor, portanto será necessário chamar um `script.php` para realizar a tarefa.
Isso poderá ser feito manualmente ou você pode configurar uma rotina de servidor para faze-lo.






## Sobre

by: will.i.am

**Agradecimentos**

Desenvolvido com base em [dyndns-htaccess](https://github.com/holodyn/dyndns-htaccess).
