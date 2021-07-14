# Relacionando dados entre duas ou mais tabelas

Basicamente, uma tabela é relacionada com a outra atravéz pra `Primary Key`, que deve ser um dado que **não se repete em NENHUM outro registro da mesma tabela**.

Como exemplo: Supondo que eu queira relacionar uma lista de alunos com a lista de cursos, vou considerar o CPF como primary key do aluno, já que nunca um mesmo CPF pode ser usado por mais de um aluno.
É muito importante usar um dado realmente único pois caso contrario o banco de dados passa a retornar dados aleatórios e completamente inesperados.

## Preparando dados para teste

Vamos criar um banco de dados e duas tabelas para começar:

```sql
create database banco_de_dados;
```

```sql
use banco_de_dados;

create table alunos(
    id int not null auto_increment,
    nascimento date,
    nome varchar(30),
    primary key (id),
) default charset = utf8;

insert into alunos values
(DEFAULT, '1997-12-12', 'William'),
(DEFAULT, '1999-08-17', 'Tiago')
```

```sql
use banco_de_dados;

create table cursos(
    id int not null auto_increment,
    datalancamento date,
    nome varchar(50),
    primary key (id),
) default charset = utf8;

insert into cursos values
(DEFAULT, '2020-12-12', 'Curso C++'),
(DEFAULT, '2021-08-17', 'Curso C#')
```

## Criando tabela para relacionar os dados das tabelas acima

```qsl
use banco_de_dados;

create table aluno_assiste_curso(
    id int not null auto_increment,
    datarelacao date,
    idaluno int,
    idcurso,
    primary key (id),
    foreign key (idaluno) references alunos(id),
    foreign key (idcurso) references cursos(id),
) default charset = utf8;

insert into cursos values
(DEFAULT, '2020-12-12', 'Curso C++'),
(DEFAULT, '2021-08-17', 'Curso C#')
```
