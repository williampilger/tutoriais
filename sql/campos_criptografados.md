# Criando, gravando e lendo campos criptografados com AES_ENCRYPT() e AES_DECRYPT()

Funções nativas do MySQL

## Dimencionando campos criptogravados

Diferente dos demais campos, quando queremos armazenar dados criptografados precisamos armazena-los como dados binários, e para preencher estes campos usaremos, neste tutorial, (e em geral é assim que se trabalha com campos criptografados) a função `AES_ENCRYPT` que retorna **32 bytes** a cada **15 caracteres** de conteúdo. Logo, é importante que nossos campos sejam criados com tamanhos múltiplos de 32, podendo armazenar 15 caracteres em cada um desses blocos.
 
## Criando campos criptografados

Os campos com conteúdo criptografados devem ser do tipo `VARBINARY`.

Exemplo de tabela:
```sql

CREATE  TABLE `user` (
`id` BIGINT UNSIGNED NOT NULL AUTO_INCREMENT ,
`first_name` VARBINARY(100) NULL ,
`address` VARBINARY(200) NOT NULL ,
PRIMARY KEY (`id`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_general_ci;
```

## Escrevendo dados

Para ciptografar os dados usamos a função `AES_ENCRYPT('conteúdo','chave');`

Veja um exemplo:

```sql
INSERT into user (first_name, address) VALUES (AES_ENCRYPT('Obama', 'usa2010'),AES_ENCRYPT('Obama', 'usa2010'));
```

## Lendo dados criptografados

Para descriptografar os dados usamos em conjunto as funções `AES_DECRYPT()` e `CAST()`.

Veja abaixo:

```sql
SELECT *, 
       CAST(AES_DECRYPT(first_name, 'usa2010') AS CHAR(50)) first_name_decrypt 
FROM   user
```



## Referências

- [Como usar AES_ENCRYPT e AES_DECRYPT no mysql](https://www.ti-enxame.com/pt/mysql/como-usar-aes-encrypt-e-aes-decrypt-no-mysql/1073766743/);
