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

**ATENÇAO!!** Troque o banco de dados selecionado para o adequado. Por padrão o selecionado é `master`, e nada pode ser executado neste domínio.

Clique em **Executar** e aguarde a mensagem de `Comandos concluídos com êxito`.


## Criando tabelas no banco de dados

Abaixo teremos um script que cria as tabelas automaticamente, e ele pode ser executado da mesma forma como feito acima.
Para ilustrar uma segunda forma de executar as mesmas ações, faremos agora a execuçãod o acript pelo serviço WEB.

- Acesse o portal do azure novamente;
- Acesse seu banco de dados (não o servidor, o banco);
- No menu de serviços, localize o **editor de consultas (visualização)**, e faça login como administrador;
- Cole o script para a criação das tabelas;
- Clique em **executar**;

Exemplo de codigo para criação de tabelas (By Alura)

```SQL
IF OBJECT_ID(N'[__EFMigrationsHistory]') IS NULL
BEGIN
    CREATE TABLE [__EFMigrationsHistory] (
        [MigrationId] nvarchar(150) NOT NULL,
        [ProductVersion] nvarchar(32) NOT NULL,
        CONSTRAINT [PK___EFMigrationsHistory] PRIMARY KEY ([MigrationId])
    );
END;

GO

CREATE TABLE [Authors] (
    [Id] int NOT NULL IDENTITY,
    [Name] nvarchar(max) NOT NULL,
    CONSTRAINT [PK_Authors] PRIMARY KEY ([Id])
);

GO

CREATE TABLE [Categories] (
    [Id] int NOT NULL IDENTITY,
    [Name] nvarchar(max) NOT NULL,
    [ParentId] int NULL,
    CONSTRAINT [PK_Categories] PRIMARY KEY ([Id]),
    CONSTRAINT [FK_Categories_Categories_ParentId] FOREIGN KEY ([ParentId]) REFERENCES [Categories] ([Id]) ON DELETE NO ACTION
);

GO

CREATE TABLE [Books] (
    [Id] int NOT NULL IDENTITY,
    [Title] nvarchar(max) NOT NULL,
    [SubTitle] nvarchar(max) NOT NULL,
    [Summary] nvarchar(max) NOT NULL,
    [DisplayName] nvarchar(max) NOT NULL,
    [CoverUri] nvarchar(max) NULL,
    [Price] decimal(5,2) NOT NULL,
    [UpdateDate] datetime2 NOT NULL,
    [PublishDate] datetime2 NOT NULL,
    [CategoryId] int NULL,
    CONSTRAINT [PK_Books] PRIMARY KEY ([Id]),
    CONSTRAINT [FK_Books_Categories_CategoryId] FOREIGN KEY ([CategoryId]) REFERENCES [Categories] ([Id]) ON DELETE NO ACTION
);

GO

CREATE TABLE [BookAuthorJoin] (
    [AuthorId] int NOT NULL,
    [BookId] int NOT NULL,
    CONSTRAINT [PK_BookAuthorJoin] PRIMARY KEY ([BookId], [AuthorId]),
    CONSTRAINT [FK_BookAuthorJoin_Authors_AuthorId] FOREIGN KEY ([AuthorId]) REFERENCES [Authors] ([Id]) ON DELETE CASCADE,
    CONSTRAINT [FK_BookAuthorJoin_Books_BookId] FOREIGN KEY ([BookId]) REFERENCES [Books] ([Id]) ON DELETE CASCADE
);

GO

CREATE INDEX [IX_BookAuthorJoin_AuthorId] ON [BookAuthorJoin] ([AuthorId]);

GO

CREATE INDEX [IX_Books_CategoryId] ON [Books] ([CategoryId]);

GO

CREATE INDEX [IX_Categories_ParentId] ON [Categories] ([ParentId]);

GO

INSERT INTO [__EFMigrationsHistory] ([MigrationId], [ProductVersion])
VALUES (N'20180830034650_InitialMigration', N'2.1.2-rtm-30932');

GO
```


# Referências

Anotações retiradas do [Curso da Alura](https://cursos.alura.com.br/course/introducao-ao-azure-com-webapps-e-sql)
