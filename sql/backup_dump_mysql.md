# Fazendo bakup (DUMP) do seu banco de dados

Existem dois possiveis caminhos, pela interface gráfica (quando possuir), ou no terminal.



## Através do PHP My Admin

Acesse seu painel de comando do PHP My Admin, selecione o banco de dados, e vá para a guia exportar.



## Linha de comando

Exportar (completo):
```bash
mysqldump -u usuario -p nome_do_banco > backup.sql
```

Exportar (somente dados, sem criação de tabelas):
```bash
mysqldump -u usuario -p --no-create-info nome_do_banco > backup.sql
```

Importar:
```bash
mysql -u usuario -p nome_do_banco < backup.sql
```


## Sobre

By: will.i.am | Balneário Camboriú - SC

2021.10.11
