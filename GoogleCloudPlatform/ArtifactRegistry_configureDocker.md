# Configurando o Docker para enviar imagens ao Google Artifact Registry do GCP

Com estes passos realizados, você poderá enviar umagens Docker para o Artifact Registry diretamente pelo terminal, usando a CLI do Google Cloud Platform.

---

### 1. Esteja Autenticado no CLI

> gcloud init

ou

> gcloud auth login

---

### 2. Configurando o Docekr

*Ps: Você obviamente já tem o Docker instalado e rodando na sua máquina, certo?!*

> gcloud auth configure-docker

Você deverá receber um JSON semelhante:
```json
{
  "credHelpers": {
    "asia.gcr.io": "gcloud",
    "eu.gcr.io": "gcloud",
    "gcr.io": "gcloud",
    "marketplace.gcr.io": "gcloud",
    "staging-k8s.gcr.io": "gcloud",
    "us.gcr.io": "gcloud"
  }
}
```

Adicionar a credencial para o servidor correto:
> gcloud auth configure-docker southamerica-east1-docker.pkg.dev

**IMPORTANTE!**

O arquivo de credenciais é no **Windows** o `%userprofile%\.docker\config.josn` e no **Linux** o `~/.docker/config.json`.
Este arquivo DEVE conter as credenciais acima.

As configurações completas serão algo assim (observe a credencial do novo repositório, adicionada manualmente):

```json
{
	"auths": {},
	"credsStore": "desktop",
	"credHelpers": {
		"asia.gcr.io": "gcloud",
		"eu.gcr.io": "gcloud",
		"gcr.io": "gcloud",
		"marketplace.gcr.io": "gcloud",
		"staging-k8s.gcr.io": "gcloud",
		"us.gcr.io": "gcloud",
		"southamerica-east1-docker.pkg.dev": "gcloud"
	},
	"currentContext": "default",
	"plugins": {
		"-x-cli-hints": {
			"enabled": "true"
		}
	}
}
```

---

### 3. Criar um Repositório no Artifact Registry

Crie um repositório de imagens no **Google Artifact Registry**:
> gcloud artifacts repositories create "sample-repos" --repository-format=docker --location="southamerica-east1" --description="Repositorio Exemplo"

Para listar seus repositórios:
> gcloud artifacts repositories list

---

### 4. Criando as imagens Docker da aplicação

Crie as imagens Docker da mesma forma que cria outra normal, por exemplo:

> docker build sample-local-image .

Marque a imagem como container para o Artifact Registry (*a Tag é opcional*):
```sh
REGION=southamerica-east1
docker tag sample-local-image:tag ${REGION}-docker.pkg.dev/PROJECT_ID/REPOSITORY_NAME/image-name:tag
```

---

### 5. Enviando para o Repositório do Artifact Registry

Fazer o push da imagem para o Artifact Registry:
```sh
REGION=southamerica-east1
docker push ${REGION}-docker.pkg.dev/PROJECT_ID/REPOSITORY_NAME/image-name:tag
```

### 🌟 Exemplo Completo

*Este exemplo é como EU faço meus scripts de automação dessas tarefas, o que não necessariamente seguem boas práticas!!*

```sh
PROJECT_ID="prod-sampleproject"
REGION="southamerica-east1"
REPOSITORY="sample-repos"
IMAGE_NAME="24001_sampleproject"

FULL_REPO_NAME=${REGION}-docker.pkg.dev/${PROJECT_ID}/${REPOSITORY}

docker tag ${IMAGE_NAME} ${FULL_REPO_NAME}/${IMAGE_NAME}
docker push ${FULL_REPO_NAME}/${IMAGE_NAME}
```
