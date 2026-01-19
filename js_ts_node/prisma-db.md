# Anotações sobre o Prisma

Nada melhor que ler [a documentação oficial](https://www.prisma.io/docs/).

O Prisma serve para trabalhar com bancos de dados diversos em Node.js (ou Typescript).

Como o prisma, você pode trocar de base de dados de forma relativamente simples.
Com "trocar", digo mudar de Banco de dados durante o desenvolvimento.
Trocar a engine em produção não é tão simples, mesmo com o Prisma.



## Começando

Instale a extensão `Prisma` no VSCode.

*Instalando o Prisma no Projeto e iniciando*
```bash
npm install prisma
npm install @prisma/client

# Inicializando o Prisma no projeto
npx prisma init

# Isso irá criar a pasta `prisma` com o arquivo `schema.prisma` e um arquivo `.env` para variáveis de ambiente.
```

*Veja um exemplo com três tabelas relacionadas entre sí e com índices de pesquisa*
```prisma
model User {
    id        Int      @id @default(autoincrement())
    email     String   @unique
    name      String?
    posts     Post[]
    Profile   Profile?
    createdAt DateTime @default(now())
}

model Post {
    id        Int      @id @default(autoincrement())
    title     String
    content   String?
    published Boolean  @default(false)
    authorId  Int
    Author    User     @relation(fields: [authorId], references: [id])
    createdAt DateTime @default(now())

    @@index([authorId])
}

model Profile {
    id     Int    @id @default(autoincrement())
    bio    String
    userId Int    @unique
    User   User   @relation(fields: [userId], references: [id])
}
```


## Comandos para gerar, implementar, deploy e outros

| Comando | Descrição |
| --- | --- |
| `npx prisma generate` | Gera o esquema (para você já poder usar no TS, por exemplo), mas não cria banco nem nada |
| `npx prisma migrate dev` | Cria e aplica uma nova migração no banco de dados durante o desenvolvimento |
| `npx prisma migrate deploy` | Aplica todas as migrações pendentes no ambiente de produção |
| `npx prisma studio` | Abre uma interface gráfica para visualizar e editar dados do banco |
| `npx prisma format` | Formata o arquivo `schema.prisma` (se você tiver a extensão configurada corretamente, isso será automático) |
| `npx prisma db pull` | Busca o esquema do banco de dados existente e atualiza o arquivo `schema.prisma` |
| `npx prisma db push` | Cria ou atualiza o esquema do banco de dados conforme o arquivo `schema.prisma` |

---

### `npx prisma migrate dev`

```
Esse comando deve ser usado durante o desenvolvimento, basicamente.

Na primeira vez que for usado:
    Gera o script para criação do banco inicial (ou faz a criação dele)

Nas execuções seguintes:
    Ele cria uma migration, ou seja, uma "alteração" no banco para um novo estado.
    Não aconselho ficar rodando migrations frequentemente.
    A ideia seria ter uma única migration para cada alteração considerável.
        Ex: O banco de produção precisa ser alterado: Migration!
    Para as alterações pequenas, durante os testes, eu pessoalmente não uso migrations.
```

### `npx prisma generate` + `npx prisma db push`
```
Usando o Generate, seguido do Push, você modifica o banco sem criar uma migration.
⚠️ ATENÇÃO: Isso pode dar muito errado se você fizer isso sem critério!

Eu, uso isso, por exemplo, enquanto estou criando o primeiro protótipo,
antes da primeira publicação da aplicação e ainda tenho bastante alterações para fazer no meu schema.

Essa também pode ser uma opção quando se precisa modificar algo em produção...
Eu já usei... MAAASSS, isso pode ser BEM perigoso!!

Para modificar algo que já está rodando SEMPRE siga:
    1 - Em um banco "clonado" rode o 'migrate dev'
    2 - Teste a aplicação, faça mais alterações...
    3 - Conecte ao banco de produção, e rode 'migrate deploy'
        Isso vai aplicar a migration já testada anteriormente!
```

### `npx prisma db pull`
```
⚠️ ATENÇÃO: Isso vai sobrescrever seu schema.prisma com um esquema deduzido do banco atualmente conectado!

Serve para você iniciar a modelagem no Prisma de um banco de dados que já existe fora dele.
```



### Comparação "Manual" do banco com o esquema

Você pode gerar um script com a diferença do esquema pro banco (script para executar e sincronizar manualmente):

```bash
# Gere o SQL de diferença
npx prisma migrate diff \
  --from-url "mysql://user:password@host:3306/database2" \
  --to-schema-datamodel prisma/schema.prisma \
  --script > sync.sql

# Revise o arquivo sync.sql e depois aplique manualmente no banco
```


### Criação de migration e aplicação falsa

Pode ser necessário criar uma migration sem aplicá-la:
```bash
npx prisma migrate dev --create-only
```

Se isso não funcionar, pois às vezes mesmo no `dev` ele exige a destruição do banco...
```bash
# Para  criar uma migration de init (não existe outra de base)
npx prisma migrate diff \
  --from-empty \
  --to-schema-datamodel prisma/schema.prisma \
  --script > prisma/migrations/0_init/migration.sql
# Marcar como aplicada
npx prisma migrate resolve --applied 0_init
```

**Lembre-se**: Estes métodos passam sobre as boas práticas. Não deve ser usado em um cenário razoável.
Preocupe-se se estiver usando isso em produção!
