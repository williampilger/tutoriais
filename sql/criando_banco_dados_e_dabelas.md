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
