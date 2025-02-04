# Criando uma conta de serviço no GCP

Aqui abordarei duas formas de criar a conta:
  - [Usando a Interface Gráfica do Cloud Plaftorm](#via-console);
  - [Usando o Google Cloud CLI](#via-cli);

**PS:** *Aqui foi criada a credencial para o SQL Proxy, mas você pode atribuir as permissões que forem necessárias pra você.*

---

## Via Console

Para criar uma credencial para o **SQL Proxy** do **Google Cloud Platform (GCP)** e obter o JSON, siga estes passos:

### 1️⃣ **Acesse o Google Cloud Console**
- Vá para [Google Cloud Console](https://console.cloud.google.com/)
- Certifique-se de que está no projeto correto.

### 2️⃣ **Crie um Serviço de Conta (Service Account)**
1. No menu lateral, vá até **IAM e Admin** > **Contas de serviço**.
2. Clique em **Criar conta de serviço**.
3. Preencha:
   - **Nome da conta de serviço** (ex: `sql-proxy`)
   - **ID da conta de serviço** (gerado automaticamente)
   - **Descrição** (opcional)
4. Clique em **Criar e continuar**.

### 3️⃣ **Conceda Permissões**
- Adicione o papel **"Cloud SQL Client"** (**roles/cloudsql.client**).
- Clique em **Concluir**.

### 4️⃣ **Gere a Chave JSON**
1. Na lista de contas de serviço, encontre a que você criou.
2. Clique no **menu de ações (⋮)** e selecione **Gerenciar chaves**.
3. Clique em **Adicionar chave** > **Criar nova chave**.
4. Escolha o formato **JSON** e clique em **Criar**.
5. O arquivo será baixado automaticamente para o seu computador.

---

## Via CLI

Você pode criar uma usando o **gcloud CLI** diretamente no terminal. Aqui está o passo a passo:

### 1️⃣ **Autentique-se no Google Cloud e escolha o projeto**
Se ainda não estiver autenticado no Google Cloud, execute:
```bash
# Para Login do zero
gcloud init

# OU - Use qualquer forma de autenticar que você já tenha usado antes
gcloud auth login
gcloud config set project [SEU_PROJETO]
```
Isso abrirá um navegador para você autenticar sua conta.


### 2️⃣ **Crie uma Conta de Serviço**
Execute o comando abaixo para criar uma **Service Account**:
```bash
gcloud iam service-accounts create sql-proxy \
  --description="Conta de serviço para SQL Proxy" \
  --display-name="SQL Proxy Service Account"
```
Isso criará uma conta chamada `sql-proxy`.


### 3️⃣ **Conceda Permissões**
Agora, conceda a permissão de **Cloud SQL Client** à conta:
```bash
gcloud projects add-iam-policy-binding [SEU_PROJETO] \
  --member="serviceAccount:sql-proxy@[SEU_PROJETO].iam.gserviceaccount.com" \
  --role="roles/cloudsql.client"
```
Substitua `[SEU_PROJETO]` pelo **ID do projeto**.


### 4️⃣ **Gerar a Chave JSON**
Agora, gere e salve a chave JSON:
```bash
gcloud iam service-accounts keys create ~/sql-proxy-key.json \
  --iam-account=sql-proxy@[SEU_PROJETO].iam.gserviceaccount.com
```
Isso salvará a credencial em `~/sql-proxy-key.json`.


### 🌟 Exemplo Completo

```sh
gcloud init #se ainda não tiver feito login e selecionado o projeto

PROJECT_ID="prod-sample"
NEW_CREDENTIAL_NAME="sqlproxy-sample"
NEW_CREDENTIAL_DESCRIPTION="Conta de serviço para conectar o app Sample ao SQL Proxy"
NEW_CREDENTIAL_DISPLAY="Sample - SQL Proxy Service Account"
NEW_CREDENTIAL_ROLE="roles/cloudsql.client"

gcloud iam service-accounts create ${NEW_CREDENTIAL_NAME} \
  --description="${NEW_CREDENTIAL_DESCRIPTION}" \
  --display-name="${NEW_CREDENTIAL_DISPLAY}"

gcloud projects add-iam-policy-binding ${PROJECT_ID} \
  --member="serviceAccount:${NEW_CREDENTIAL_NAME}@${PROJECT_ID}.iam.gserviceaccount.com" \
  --role="${NEW_CREDENTIAL_ROLE}"

# Gerar o JSON
gcloud iam service-accounts keys create ./${NEW_CREDENTIAL_NAME}-key.json \
  --iam-account=${NEW_CREDENTIAL_NAME}@${PROJECT_ID}.iam.gserviceaccount.com

# Garantir que só tenha acesso de leitura. Isso é opcional
chmod 600 ./${NEW_CREDENTIAL_NAME}-key.json
```
