# Acessar "localmente" um banco de dados hospedado com CloudQSL no Google Cloud Platform (GCP)

Neste exemplo, estou rodando um `Ubuntu 24.04 LTS`, com uma montanha de softwares instalados, logo é possível que vocẽ precise instalar mais bibliotecas e/ou ferramentas que eu.
Leia mais sobre o tema na [documentação do google](https://cloud.google.com/sql/docs/mysql/sql-proxy?hl=pt-br).

## Ambiente

**Primeiramente**: [Instale o Google Cloud CLI](./install_cli.md), autentique sua conta, e garanta que tenha as permissões necessárias.

SE VOCÊ AINDA NÂO FEZ LOGIN E/OU SELECIONOU O PROJETO:
```sh
#Se você ainda não fez login:
gcloud auth login

# E selecionou o projeto:
gcloud config set project [PROJECT_ID]
```

*Instale binário do CloudSQL Proxy e o torne executável*
```sh
sudo curl -o /usr/local/bin/cloud-sql-proxy https://storage.googleapis.com/cloud-sql-connectors/cloud-sql-proxy/v2.14.3/cloud-sql-proxy.linux.amd64
sudo chmod +x /usr/local/bin/cloud-sql-proxy
```

-----------------

## Rodando o SQL Proxy na sua máquina

### 1. **Localize a Conexão do Banco de Dados**
No Google Cloud Console, encontre o **Instance Connection Name** do seu banco:

1. Vá para **Cloud SQL**.
2. Selecione a instância do banco de dados.
3. Copie o valor de **Connection Name** (algo como `my-project:region:instance-name`).


### 2. Autenticando a Aplicação
As aplicações, como o `cloud-sql-proxy` usam credenciais diferentes da CLI, então, você precisa fazer login.

Em um ambiente de TESTES, é mais comum autenticar usando a própria conta do google:
```sh
gcloud auth application-default login
```

Em ambientes de Produção, **crie uma conta de serviço** com permissões para executar o SQLProxy,
e baixe o JSON da credencial.

Você **pode** definir o JSON baixado como a credencial padrão para todas aplicações:
```sh
export GOOGLE_APPLICATION_CREDENTIALS="/caminho/para/sua-chave.json"
```

---

### 3. **Inicie o Proxy**
Execute o Cloud SQL Auth Proxy para criar o proxy local. Substitua `[INSTANCE_CONNECTION_NAME]` pelo valor copiado:

```bash
# Se você definiu a credencial global (ou fez login com a conta)
cloud-sql-proxy --port=3306 [INSTANCE_CONNECTION_NAME]

# Se preferir passar a credencial no comando de executar
cloud-sql-proxy --credentials-file=/caminho/para/sua-chave.json --port=3306 [INSTANCE_CONNECTION_NAME]
```

Isso criará um proxy local na porta 3306, conectando ao seu banco de dados no Google Cloud.

### 3. Testar a conexão

Você deve conseguir acessar normalmente agora o banco com a sua aplicação.
No entanto, pode testar a conexão diretamente (se tiver o cliente mysql instalado, obviamente):

> mysql -u [USUÁRIO] -p -h 127.0.0.1 -P [PORTA] --database=[NOME-DO-BANCO]
