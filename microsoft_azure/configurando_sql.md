# Configurando o banco de dados SQL no Azure

Para acessar o banco de dados SLQ, use o Microsoft SQL Server Manager, depois de logar com as credenciais do servidor, possivelmente o acesso será barrado pelo Firewall do servidor.
Para resolver este problema crie uma regra.

## Criar regra de acesso no Firewall do servidor SQL

- Acesse o [portal do azure](portal.azure.com), logue com suas credenciais, e acesse o banco de dados já criado.
- Na árvore de opções, procure por `Segurânça` -> `Firewall` e adicione seu endereço de IP como uma nova regra. (OBS: Seu IP aparece na própria página)

## Criando usuário para acesso ao banco de dados

Após logar no SQL Manager, clique em **Nova Consulta** e use o script abaixo:

```SQL
CREATE USER [SeuWebApp]
WITH PASSWORD = 'sua senha'
	, DEFAULT_SCHEMA = dbo;
GO

ALTER ROLE db_datareader ADD MEMBER [SeuWebApp];
ALTER ROLE db_datawriter ADD MEMBER [SeuWebApp];
GO
```

