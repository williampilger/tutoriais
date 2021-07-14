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
    primary key (id)
)default character set = utf8;

insert into alunos values
(DEFAULT, '1997-12-12', 'William'),
(DEFAULT, '1999-08-17', 'Tiago'),
(DEFAULT, '1965-07-17', 'Creusa'),
(DEFAULT, '1999-07-4', 'Maria'),
(DEFAULT, '1974-02-18', 'João');
```

```sql
use banco_de_dados;

create table cursos(
    id int not null auto_increment,
    datalancamento date,
    nome varchar(50),
    primary key (id)
)default character set = utf8;

insert into cursos values
(DEFAULT, '2020-12-12', 'Curso C++'),
(DEFAULT, '2021-08-17', 'Curso C#'),
(DEFAULT, '2020-01-10', 'Curso PHP'),
(DEFAULT, '2019-04-14', 'Curso Java');
```

## Criando tabela para relacionar os dados das tabelas acima

Veja abaixo uma forma de criar a tabela e alguns registros de alunos que assistiram um curso:

```sql
use banco_de_dados;

create table aluno_assiste_curso(
    id int not null auto_increment,
    dataexecucao date,
    idaluno int,
    idcurso int,
    primary key (id),
    foreign key (idaluno) references alunos(id),
    foreign key (idcurso) references cursos(id)
)default character set = utf8;

insert into aluno_assiste_curso values
(DEFAULT, '2021-07-14', '1', '2'),
(DEFAULT, '2021-07-14', '2', '1'),
(DEFAULT, '2021-07-14', '3', '3'),
(DEFAULT, '2021-07-14', '3', '3'),
(DEFAULT, '2021-07-14', '4', '2'),
(DEFAULT, '2021-07-14', '5', '1'),
(DEFAULT, '2021-07-14', '2', '4'),
(DEFAULT, '2021-07-14', '1', '2'),
(DEFAULT, '2021-07-14', '3', '1');
```

## Lendo dados cruzados

Para visualizar os dados dos cursos realizados pelos alunos de uma forma mais clara, podemos criar lógicas de substituição dos dados para impressão. Veja abaixo:

```sql
use banco_de_dados;

select A.nome, C.nome from alunos as A
join aluno_assiste_curso as AC
on A.id = AC.idaluno
join cursos as C
on C.id = AC.idcurso
order by A.nome;

```

Observações:
- Com o comando `alunos as A` apelidamos `alunos` de `A`, e sim, isso pode ser feito em qualquer parte do código, e vale inclusive para a chamada feita ANTES do comando;
- Com o comando `aluno_assiste_curso as AC`apelidamos `aluno_assiste_curso` de `AC`;
- Com o comando `curso as C`apelidamos `curso` de `C`;
- Com o comando `on` estabelecemos a conexão entre as chaves externas da tabela e a origem dela;
