# Inserindo e alterando dados nas Tabelas

Para ver sobre a criação e manipulação de bancos de dados e tabelas visite [este outro passo a passo](/criando_banco_dados_e_dabelas.md)

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
