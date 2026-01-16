# Exportar um Banco de Dados específico de dentro de uma instância

```
⚠️ Conteúdo gerado pelo Gemini PRO em  16/01/2026 às 16:10

Revisado por mim.
```

Para exportar apenas **um banco de dados específico** (e não todos os que estão na instância), siga estes passos:

### 1. Via Console do GCP (Foco em Banco Único)

1. No Console, vá em **SQL** > Selecione sua **Instância**.
2. Clique no botão **Exportar** no menu superior.
3. No campo **Formato**, certifique-se de que está em **SQL**.
4. **O ponto chave:** Na seção **Dados a serem exportados**, você verá uma opção chamada **Bancos de dados**. Selecione apenas o banco de dados que você deseja no menu suspenso.
5. Escolha o destino no Cloud Storage e clique em **Exportar**.

---

### 2. Via Linha de Comando (gcloud)

Se você quer garantir que apenas um banco seja exportado via terminal, use a flag `--database`. Isso evita que a instância inteira seja incluída no `.sql`.

```bash
gcloud sql export sql NOME_DA_INSTANCIA gs://SEU_BUCKET/backup_especifico.sql \
    --database=NOME_DO_SEU_BANCO \
    --offload

```

> **Atenção:** Se o seu banco de dados MySQL utiliza **Views**, a exportação via Console/gcloud pode falhar se o usuário que executa a exportação não tiver privilégios suficientes. Nesses casos, o `mysqldump` manual costuma ser mais resiliente.

---

### 3. Usando `mysqldump` (Apenas o Banco)

Se você precisa do arquivo direto na sua máquina (local) sem passar pelo Cloud Storage, use este comando via terminal (assumindo que você tem acesso à rede ou está usando o Proxy):

```bash
mysqldump -h [IP_OU_LOCAL] -u [USUARIO] -p \
    --single-transaction \
    --set-gtid-purged=OFF \
    NOME_DO_BANCO > backup_do_banco.sql

```

**Parâmetros importantes para MySQL no CloudSQL:**

* `--single-transaction`: Garante que o banco não seja "travado" durante a exportação (essencial para produção).
* `--set-gtid-purged=OFF`: Evita erros comuns ao tentar importar esse arquivo depois em outras instâncias MySQL que usam replicação GTID.

---

### Como baixar o arquivo após a exportação?

Como o GCP exporta para um Bucket por segurança, o arquivo não "cai" na sua pasta de Downloads automaticamente. Após o processo terminar, execute:

```bash
gcloud storage cp gs://SEU_BUCKET/backup_especifico.sql ./meu_arquivo_local.sql

```

**O banco de dados que você quer exportar é muito grande (acima de 10GB)?** Se sim, eu recomendo usar a flag `--offload` para não impactar a performance da sua aplicação enquanto o backup roda. Seria útil detalhar como configurar as permissões de Bucket caso ocorra erro de "Access Denied"?
