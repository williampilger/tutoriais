# Acessar "localmente" um banco de dados hospedado com CloudQSL no Google Cloud Platform (GCP)

Neste exemplo, estou rodando um `Ubuntu 24.04 LTS`, com uma montanha de softwares instalados, logo é possível que vocẽ precise instalar mais bibliotecas e/ou ferramentas que eu.

## Ambiente

**Primeiramente**: [Instale o Google Cloud CLI](./install_cli.md), autentique sua conta, e garanta que tenha as permissões necessárias.

SE VOCÊ AINDA NÂO FEZ LOGIN E/OU SELECIONOU O PROJETO:
```sh
#Se você ainda não fez login:
gcloud auth login

# E selecionou o projeto:
gcloud config set project [PROJECT_ID]
```

-----------------

## Rodando o SQL Proxy na sua máquina

### 1. **Localize a Conexão do Banco de Dados**
No Google Cloud Console, encontre o **Instance Connection Name** do seu banco:

1. Vá para **Cloud SQL**.
2. Selecione a instância do banco de dados.
3. Copie o valor de **Connection Name** (algo como `my-project:region:instance-name`).


### 2. **Inicie o Proxy**
Execute o Cloud SQL Auth Proxy para criar o proxy local. Substitua `[INSTANCE_CONNECTION_NAME]` pelo valor copiado:

```bash
cloud_sql_proxy -instances=[INSTANCE_CONNECTION_NAME]=tcp:3306
```

Isso criará um proxy local na porta 3306, conectando ao seu banco de dados no Google Cloud.

