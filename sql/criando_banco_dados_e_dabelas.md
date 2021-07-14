# Criar e configurar Bancos de dados e Tabelas em um servidor SQL

Estes passos foram feitos seguindo o tutorial []().

## Criar Tabela

Abaixo está um exemplo de uma tabela `pessoas` onde o ID é a chave primária (ou seja, não se repete. Impede que a mesma pessoa seja cadastrada duas vezes).

```sql
create table pessoas(
    id int not null auto_increment,
    nome varchar(20) not null,
    nascimento date,
    sexo enum('M','F'),
    peso decimal(5,2),
    altura decimal(3,2),
    nacionalidade varchar(15) default 'Brasil',
    primary key(id)
)default character set utf8;
```

Podemos observar também que o padrão de caracteres foi definido em `UTF-8`, e que alguns campos estão marcados como obrigatórios com a constante `not null`.

O formato de dados `decimal` permite que criemos campos "float" com o número exato de caracteres. Onde o primeiro número é a quantidade total de dígitos disponíveis e o segundo é a quantidade que ficará depois da vírgula.

## Inserir dados na tabela

Exemplos de código:

```sql
insert into pessoas
(id, nome, nascimento, sexo, peso, altura, nacionalidade)
values
('1', 'William', '1997-12-12', 'M', '65.6', '1.92', 'Brasileiro');
```

```sql
insert into pessoas
(nome, nascimento, sexo, peso, altura)
values
('Mariano', '1997-1-12', 'M', '65.6', '1.92');
```

```sql
insert into pessoas values
(DEFAULT, 'Mariano', '1997-1-12', 'M', '65.6', '1.92', DEFAULT);
```

## Alterar a estrutura da tabela

Lembrando que para ver a atual estrutura da sua tablema você pode usar os dois comandos abaixo:

> describe nome_da_sua_tabela

> desc nome_da_sua_tabela

**Adicionar uma Coluna**

Para adicionar uma coluna (um campo) ao final da sua estrutura de dados, use o exemplo abaixo:

```sql
alter table pessoas
add column profissao varchar(10);
```

Neste caso, foi adicionada a coluna "profissao" à tabela "pessoas" que criamos no passo anterior.

Para adicionar a coluna em uma posição específica, use o comando `after`. Para coloca-la após o nome, por exemplo, use:

```sql
alter table pessoas
add column profissao varchar(10) after nome;
```

**Remover uma Coluna**

Para remover a mesma coluna, usamos:

```sql
alter table pessoas
add column profissao varchar(10);
```



