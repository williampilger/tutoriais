# Exemplos de configuração do Cloud SQL em apps do CLoud Run com Prisma

Neste arquivo, apresentarei alguns exemplos **testado por mim**, e que **pra mim** funcionam.

Estou usando exemplos com o *GCP CLI*. Ou seja, via terminal, como acontece em projetos reais da **minha** produção. 

⚠️ Importante notar que: **O Cloud Run costuma não se dar muito bem com as revisões muito diferentes de uma mesma aplicação**
(ao menos até o momento em que vos escrevo).
Então, se desconfiar que uma alteração não está causando o efeito esperado, exclua o serviço e recrie-o do zero.

Para evitar problemas, os serviços ativos no seu projeto devem ser, no mínimo:

```bash
gcloud services enable run.googleapis.com \
    secretmanager.googleapis.com \
    sqladmin.googleapis.com \
    iam.googleapis.com \
    cloudresourcemanager.googleapis.com \
    artifactregistry.googleapis.com \
    vpcaccess.googleapis.com \
    networkmanagement.googleapis.com
```


---


## 1️⃣ Usando Conexão Direta com socket padrão e SSL Manual

```
* Com SSL (usando certificados SSL e conexão seguros)
    * Gerando Certificados e Credenciais manualmente
* Com exposição pública do Banco de dados (IP público)
* Sem proxy
* Sem NAT
* Sem VPC Connector
```

- `.ENV`
  - ```sh
    PORT=5001
    DATABASE_URL="mysql://user:password@34.151.203.258:3306/your-database?connect_timeout=5000&sslaccept=accept_invalid_certs&sslca=/secrets/server-ca/server-ca.pem&sslcert=/secrets/client-cert/client-cert.pem&sslkey=/secrets/client-key/client-key.pem"
    PROJECT_ID="project-id"
    SERVICE_NAME="your-service-name"
    REGION="southamerica-east1"
    CLOUDSQL_INSTANCE_NAME="database-instance-name"
    GCP_CREDENTIAL_NAME="credential-name"
    MY_ENV_VAR_SAMPLE="sample"
    ```
- *EXEMPLO de Dockerfile*
    - ```Dockerfile
        FROM node:18
        WORKDIR /app
        ENV PORT 5001

        COPY . .
        RUN npm install
        RUN npx prisma generate
        RUN npm run build
        RUN mv entrypoint.sh /usr/local/bin/entrypoint.sh
        RUN chmod +x /usr/local/bin/entrypoint.sh

        # Remove credenciais, se por ventura estavam dando sopa, e move os certificados para o diretório adequado
        RUN rm .env
        RUN rm -rf ./secrets

        # Instalação de pacotes necessários
        RUN apt update && apt install -y wget ca-certificates --no-install-recommends
        RUN apt-get clean && rm -rf /var/lib/apt/lists/*


        EXPOSE ${PORT}
        CMD ["node", "./dist/server.js"]
      ```
- Permissões da Service Account
    - ```bash
        gcloud init #se ainda não tiver feito login e selecionado o projeto

        # USE SUAS CONSTANTES

        gcloud iam service-accounts create ${NEW_CREDENTIAL_NAME} \
            --description="${NEW_CREDENTIAL_DESCRIPTION}" \
            --display-name="${NEW_CREDENTIAL_DISPLAY}"

        gcloud projects add-iam-policy-binding $PROJECT_ID \
            --member="serviceAccount:${GCP_SERVICE_ACCOUNT}" \
            --role=roles/run.invoker
        gcloud projects add-iam-policy-binding $PROJECT_ID \
            --member="serviceAccount:${GCP_SERVICE_ACCOUNT}" \
            --role=roles/secretmanager.secretAccessor
        gcloud projects add-iam-policy-binding $PROJECT_ID \
            --member="serviceAccount:${GCP_SERVICE_ACCOUNT}" \
            --role=roles/vpcaccess.user
      ```
- Deploy command
    - ```bash
        gcloud run deploy $SERVICE_NAME \
            --image $FULL_IMAGE_NAME \
            --platform managed \
            --region $REGION \
            --allow-unauthenticated \
            --port $PORT \
            --ingress all \
            --service-account $GCP_SERVICE_ACCOUNT \
            --min-instances 1 \
            --max-instances 10 \
            --concurrency 100 \
            --execution-environment gen2 \
            --cpu-throttling \
            --set-env-vars=CLOUDSQL_CONNECTION_NAME=${CLOUDSQL_CONNECTION_NAME} \
            --set-env-vars=DATABASE_URL=${DATABASE_URL} \
            --set-env-vars=MY_ENV_VAR_SAMPLE=${MY_ENV_VAR_SAMPLE} \
            --update-secrets=/secrets/server-ca/server-ca.pem="${SECRET_PREFIX}_SERVER_CA:latest" \
            --update-secrets=/secrets/client-key/client-key.pem="${SECRET_PREFIX}_CLIENT_KEY:latest" \
            --update-secrets=/secrets/client-cert/client-cert.pem="${SECRET_PREFIX}_CLIENT_CERT:latest" \
            --verbosity=debug 
      ```


⚠️ Note que

  - Não se usa o conector `--add-cloudsql-instances=INSTANCE_CONNECTION_NAME`;
  - **Não se instala** o client do SQL Proxy;
  - Foi necessário [criar o certificado SSL](/SecretsManager_CloudSQL-SSL-cert.md);
  - Foi usando `--ingress all` e `--allow-unauthenticated` para conectar a instância à rede aberta e permitir acesso externo;
  - É necessário **obrigatoriamente liberar o IP público do app CloudRun para acesso ao IP público do CloudSQL**; 
  - **A URL de conexão ao banco**
    - Não se deve informar o `socketPath` na URL de conexão, uma vez que se usa o padrão neste caso.
    - Informar os certificados `sslca`, `sslcert` e `sslkey`;
      - 🔴 Precisam, **OBRIGATORIAMENTE** estar em diretórios individuais! Levar isso em conta ao montar as secrets.
    - Informar `sslaccept=accept_invalid_certs` se o servidor e o cliente forem de confiança;
    - Pode ser necessário aumentar o `connect_timeout`;
    - Usar o **IP Público** da sua instância de banco de dados;
    - É necessário definir a variável de ambiente `CLOUDSQL_CONNECTION_NAME`



## 2️⃣ Usando Conexão gerenciada com SQL Proxy

```
* Com SSL gerenciado
* Com proxy automático (mais seguro)
* Sem exposição pública ao servidor CloudSQL
* Sem NAT nem VPC Connector
```

- `.ENV`
  - ```sh
    PORT=5001
    DATABASE_URL="mysql://user:password@34.151.203.258:3306/your-database?socket=/cloudsql/project-id:southamerica-east1:cloudsql-instance-name&connect_timeout=5000"
    PROJECT_ID="project-id"
    SERVICE_NAME="your-service-name"
    REGION="southamerica-east1"
    CLOUDSQL_INSTANCE_NAME="database-instance-name"
    GCP_CREDENTIAL_NAME="credential-name"
    MY_ENV_VAR_SAMPLE="sample"
    ```
- *EXEMPLO de Dockerfile*
    - ```Dockerfile
        FROM node:18
        WORKDIR /app
        ENV PORT 5001

        COPY . .
        RUN npm install
        RUN npx prisma generate
        RUN npm run build
        RUN mv entrypoint.sh /usr/local/bin/entrypoint.sh
        RUN chmod +x /usr/local/bin/entrypoint.sh

        # Remove credenciais, se por ventura estavam dando sopa, e move os certificados para o diretório adequado
        RUN rm .env
        RUN rm -rf ./secrets

        # Instalação de pacotes necessários
        RUN apt update && apt install -y wget ca-certificates --no-install-recommends
        RUN apt-get clean && rm -rf /var/lib/apt/lists/*


        EXPOSE ${PORT}
        CMD ["node", "./dist/server.js"]
      ```
- Permissões da Service Account
    - ```bash
        gcloud init #se ainda não tiver feito login e selecionado o projeto

        # USE SUAS CONSTANTES

        gcloud iam service-accounts create ${NEW_CREDENTIAL_NAME} \
            --description="${NEW_CREDENTIAL_DESCRIPTION}" \
            --display-name="${NEW_CREDENTIAL_DISPLAY}"

        gcloud projects add-iam-policy-binding $PROJECT_ID \
            --member="serviceAccount:${GCP_SERVICE_ACCOUNT}" \
            --role=roles/cloudsql.client
        gcloud projects add-iam-policy-binding $PROJECT_ID \
            --member="serviceAccount:${GCP_SERVICE_ACCOUNT}" \
            --role=roles/run.invoker
        gcloud projects add-iam-policy-binding $PROJECT_ID \
            --member="serviceAccount:${GCP_SERVICE_ACCOUNT}" \
            --role=roles/vpcaccess.user
      ```
- Deploy command
    - ```bash
        gcloud run deploy $SERVICE_NAME \
            --image $FULL_IMAGE_NAME \
            --platform managed \
            --region $REGION \
            --allow-unauthenticated \
            --port $PORT \
            --ingress all \
            --service-account $GCP_SERVICE_ACCOUNT \
            --min-instances 1 \
            --max-instances 10 \
            --concurrency 100 \
            --execution-environment gen2 \
            --cpu-throttling \
            --add-cloudsql-instances=${CLOUDSQL_CONNECTION_NAME} \
            --set-env-vars=DATABASE_URL=${DATABASE_URL} \
            --set-env-vars=SUPPRESS_RESPONSE_ERROR_MESSAGES=${SUPPRESS_RESPONSE_ERROR_MESSAGES} \
            --set-env-vars=SERVER_UNDER_MAINTENANCE=${SERVER_UNDER_MAINTENANCE} \
            --set-env-vars=ALOW_USER_HARD_DELETE=${ALOW_USER_HARD_DELETE} \
            --set-env-vars=PASSWORD_SALT=${PASSWORD_SALT} \
            --set-env-vars=LOG_API_URL=${LOG_API_URL} \
            --set-env-vars=APP_ID=${APP_ID} \
            --verbosity=debug 
      ```


⚠️ Note que

  - Usa o conector `--add-cloudsql-instances=INSTANCE_CONNECTION_NAME`;
  - **Não se instala** o client do SQL Proxy;
  - Foi usando `--ingress all` e `--allow-unauthenticated` para conectar a instância à rede aberta e permitir acesso externo;
  - É necessário **obrigatoriamente liberar o IP público do app CloudRun para acesso ao IP público do CloudSQL**; 
  - **A URL de conexão ao banco**
    - Deve-se informar o `socketPath` na URL de conexão, para que o socket injetado pelo GCP seja usado
    - **Pode** ser necessário aumentar o `connect_timeout`;
    - Usar o **IP Público** da sua instância de banco de dados;
    - 🔴 Você **não deve** definir manualmente a variável de ambiente `CLOUDSQL_CONNECTION_NAME` dentro do container

