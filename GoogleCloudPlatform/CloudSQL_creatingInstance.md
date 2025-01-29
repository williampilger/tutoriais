# Criando a Instância do CloudSQL -> Via console.cloud.google.com

- 1. Com o seu projeto selecionado, acesse o [menu do CloudSQL](https://console.cloud.google.com/sql/instances);
- 2. Clique em `+ Criar Instância`;
- 3. Configure toda a máquina de acordo com suas necessidades:
  - obs: Ativar o IP fixo não é mais reversível;
- 4. Aguarde a criação concluir;


## Criando o Banco de dados e Usuário(s)

Você pode criar os usuário **diretamente pelo painel, na guia Usuários**, ou **via SQL mesmo**.
Pelo painel **NÃO É POSSÍVEL ATRIBUIR PRIVILÉGIOS POR BANCO DE DADOS**.

Conecte-se ao banco pelo terminal no **CloudShell**, ou usando o SQLProxy, com as credenciais do `Root` (usuário configurado na criação da instância do CloudSQL). *NOTA: para usar o SQL via terminal no seu computador, será necessário ter o sql-client instalado, independente do seu sistema operacional.**

*Conectando usando o CLI (já autenticado)*
> gcloud sql connect nome-da-instancia --user=nome-de-usuario

*Execute a criação do(s) banco(s) e/ou usuário(s) com base nos comando abaixo:*
```sql
CREATE DATABASE 'database-name';

CREATE USER 'new_user'@'%' IDENTIFIED BY 'password';
GRANT SELECT, INSERT, UPDATE, DELETE ON 'database-name'.* TO 'new_user'@'%';

FLUSH PRIVILEGES;
```
