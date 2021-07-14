# Inserindo e alterando dados nas Tabelas

Para ver sobre a criação e manipulação de bancos de dados e tabelas visite [este outro passo a passo](criando_banco_dados_e_dabelas.md)

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

## Modificando dados de linhas

Este processo é bastante perigoso, pois pode afetar inúmeras linhas simultaneamente.
(Hoje a maioria dos servidores possuem proteções para evitar alterações em grandes volumes de dados, mas cuidado)

Como exemplo tomarei a tabela preenchida acima. Para alterar a data de nascimento e peso de **William** posso usar:

```sql
update pessoas
set nascimento = '1997-11-15', peso = '71.5'
where nome = 'William';
```

**MAS ATENÇÂO!** Isso feito em tabelas maiores, afetará TODOS os registros onde o nome for "William".

Para limitar as alterações para que ocorram em apenas **um único registro** podemos usar o comando `limit`, veja:

```sql
update pessoas
set nascimento = '1997-11-15', peso = '71.5'
where nome = 'William'
limit 1;
```

## Eliminar um registro

Usamos o comando `delete` para isso, veja:

```sql
delete from pessoas
where nome = 'William';
```

**ATENÇÂO!!** Lembrando que é uma **Péssima ideia** eliminar um registro com base no nome. Pois novamente, isso afeta todos registros com esse nome.
Também é importante lembrar que **não pe nem um pouco aconselhavel modificar um banco de dados ativos**, sempre faça um backup.

## Eliminar todos os dados de uma tabela

Para limpar completamente uma tabela usamos:

```sql
truncate table sua_tabela
```
