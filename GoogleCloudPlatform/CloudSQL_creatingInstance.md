# Criando a Instância do CloudSQL -> Via console.cloud.google.com

1 - Com o seu projeto selecionado, acesse o [menu do CloudSQL](https://console.cloud.google.com/sql/instances);
2 - Clique em `+ Criar Instância`;
3 - Configure toda a máquina de acordo com suas necessidades:
    obs: Ativar o IP fixo não é mais reversível;
4 - Aguarde a criação concluir;



## Criando o Banco de dados e Usuário(s)

Conecte-se ao banco pelo terminal no **CloudShell**, ou usando o SQLProxy, com as credenciais do `Root` (usuário configurado na criação da instância do CloudSQL).
Execute a criação do(s) banco(s) e/ou usuário(s) com base nos comando abaixo:

```sql
CREATE DATABASE 'dev-workspace';

CREATE USER 'devuser'@'%' IDENTIFIED BY 'password';
GRANT SELECT, INSERT, UPDATE, DELETE ON 'dev-workspace'.* TO 'novo_usuario'@'%';

FLUSH PRIVILEGES;
```
