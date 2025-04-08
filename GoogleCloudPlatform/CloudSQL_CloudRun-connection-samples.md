# Exemplos de configuração do Cloud SQL em apps do CLoud Run com Prisma

Neste arquivo, apresentarei alguns exemplos **testado por mim**, e que **pra mim** funcionam.

Estou usando exemplos com o *GCP CLI*. Ou seja, via terminal, como acontece em projetos reais da **minha** produção. 

⚠️ Importante notar que: **O Cloud Run costuma não se dar muito bem com as revisões muito diferentes de uma mesma aplicação**
(ao menos até o momento em que vos escrevo).
Então, se desconfiar que uma alteração não está causando o efeito esperado, exclua o serviço e recrie-o do zero.


---


## 1️⃣ Usando Conexão Direta

```
* Com SSL (usando certificados SSL e conexão seguros)
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