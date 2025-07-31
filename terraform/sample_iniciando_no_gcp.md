# Iniciando com o Terraform no Google Cloud Platform, com estrutura prévia já existente

Aqui está um guia passo a passo de como proceder, dividido em fases.

```
⚠️ Este é um exemplo gerado pelo Gemini e revisado por mim
```

-----

### Fase 1: Preparação do Ambiente

Antes de começar a escrever código, você precisa preparar seu ambiente local e o GCP.

1.  **Instale as Ferramentas:**

      * **Terraform:** Baixe e instale a CLI do Terraform a partir do [site oficial](https://www.terraform.io/downloads.html).
      * **Google Cloud SDK (`gcloud`):** Instale a CLI do GCP para facilitar a autenticação e a busca de informações dos seus recursos. Siga o [guia de instalação](https://cloud.google.com/sdk/docs/install).

2.  **Autenticação no GCP:**
    Autentique sua máquina local para que o Terraform tenha permissão para interagir com sua conta do GCP. O método mais simples para começar é:

    ```bash
    gcloud auth application-default login
    ```

    Este comando abrirá um navegador para você fazer login com sua Conta Google, que terá as permissões necessárias no projeto.

3.  **Crie um Backend Remoto para o Estado:**
    O Terraform mantém um arquivo de "estado" (`terraform.tfstate`) que mapeia seu código aos recursos reais na nuvem. **Nunca armazene este arquivo localmente em um projeto de equipe ou produção.** A melhor prática é usar um backend remoto. Para o GCP, o ideal é usar o Google Cloud Storage (GCS).

      * **Crie um bucket no GCS:** Este bucket armazenará seu arquivo de estado de forma segura e centralizada.
        ```bash
        # Lembre-se: os nomes do buckes devem ser EXCLUSIVOS (não pode existir outro igual, de nenhum outro usuário do GCP).
        # nomes como `sample.dominio.com` deverão ter o domínio `sample.com` verificado 
        gcloud storage buckets create gs://SEU_BUCKET_DE_ESTADO_SUPER_SEGURO --project=SEU_PROJETO_ID --location=sua-regiao --uniform-bucket-level-access
        ```
      * **Ative o versionamento no bucket (altamente recomendado):** Isso protege contra exclusões acidentais do arquivo de estado.
        ```bash
        gcloud storage buckets update gs://SEU_BUCKET_DE_ESTADO_SUPER_SEGURO --versioning
        ```

-----

### Fase 2: Estrutura do Projeto e Importação (O Processo Principal)

A estratégia é começar pequeno e importar recurso por recurso, ou grupo de recursos por vez. Não tente importar tudo de uma só vez.

**Estrutura de Arquivos Inicial:**

Crie um diretório para o seu projeto Terraform e adicione os seguintes arquivos:

```
/meu-projeto-gcp-terraform
  ├── main.tf         # Arquivo principal para os recursos
  ├── provider.tf     # Configuração do provedor GCP
  ├── backend.tf      # Configuração do backend remoto (GCS)
  └── variables.tf    # (Opcional, mas recomendado) Para variáveis
```

**Conteúdo dos Arquivos de Configuração:**

**`backend.tf`**:

```terraform
terraform {
  backend "gcs" {
    bucket  = "SEU_BUCKET_DE_ESTADO_SUPER_SEGURO"
    prefix  = "terraform/state" # Um "diretório" dentro do bucket
  }
}
```

**`provider.tf`**:

```terraform
terraform {
  required_providers {
    google = {
      source  = "hashicorp/google"
      version = "~> 5.0" # Use uma versão recente
    }
  }
}

provider "google" {
  project = "SEU_PROJETO_ID"
  region  = "sua-regiao-padrao" # ex: us-central1
  zone    = "sua-zona-padrao"   # ex: us-central1-a
}
```

**Inicialize o Terraform:**

No seu terminal, dentro do diretório do projeto, rode:

```bash
terraform init
```

Este comando irá baixar o provedor do Google e configurar seu backend no GCS.

### O Fluxo de Importação (Repita para cada recurso)

O processo para importar um recurso existente (ex: uma VPC, uma VM) segue 3 passos:

1.  **Escrever o Bloco de Recurso:** Escreva o código Terraform no seu arquivo `.tf` (ex: `main.tf`) que define o recurso que você quer importar. Você não precisa preencher todos os argumentos ainda, apenas o necessário para criar o bloco.
2.  **Encontrar o ID do Recurso no GCP:** Cada recurso no GCP tem um ID único que o Terraform usará para a importação.
3.  **Executar `terraform import`:** Use o comando de importação para vincular o código que você escreveu ao recurso real no GCP.
4.  **Sincronizar o Código:** Após a importação, o estado estará atualizado, mas seu código `.tf` ainda estará incompleto. Você precisa ajustar seu código para que ele corresponda exatamente à configuração do recurso importado.

-----

### Fase 3: Exemplo Prático - Importando a VPC e uma VM

Vamos supor que você tem uma VPC chamada `minha-vpc-principal` e uma VM chamada `vm-web-01`.

**1. Importando a VPC (`google_compute_network`)**

  * **Passo 1: Escrever o Código (em `main.tf`)**

    ```terraform
    resource "google_compute_network" "minha_vpc" {
      # Deixe os argumentos em branco por enquanto
      # ou apenas com o nome
      name = "minha-vpc-principal"
    }
    ```

  * **Passo 2: Encontrar o ID do Recurso**
    O ID de uma VPC no GCP é geralmente no formato `projects/SEU_PROJETO_ID/global/networks/NOME_DA_VPC`. Você pode encontrá-lo na URL do console do GCP ou usando `gcloud`:

    ```bash
    gcloud compute networks describe minha-vpc-principal --format='value(selfLink)'
    ```

  * **Passo 3: Executar a Importação**
    O comando de importação usa o `endereço do recurso no Terraform` e o `ID do recurso no GCP`.

    ```bash
    terraform import google_compute_network.minha_vpc projects/SEU_PROJETO_ID/global/networks/minha-vpc-principal
    ```

    Você verá uma mensagem de sucesso. Agora, `minha_vpc` está no seu arquivo de estado.

  * **Passo 4: Sincronizar o Código**
    Se você rodar `terraform plan` agora, o Terraform provavelmente dirá que quer deletar e recriar a VPC, pois seu código em `main.tf` está vazio e não corresponde à VPC real (que tem `auto_create_subnetworks`, `routing_mode`, etc.).

    Para corrigir isso:
    a. Rode `terraform show` para ver todos os atributos que o Terraform importou para o estado.
    b. Copie os atributos relevantes do output do `terraform show` para o seu bloco de recurso `google_compute_network.minha_vpc` em `main.tf`.

    Seu código final ficará parecido com isto:

    ```terraform
    resource "google_compute_network" "minha_vpc" {
      name                    = "minha-vpc-principal"
      auto_create_subnetworks = false # ou true, dependendo da sua config
      mtu                     = 1460
      project                 = "SEU_PROJETO_ID"
      routing_mode            = "REGIONAL" # ou GLOBAL
    }
    ```

    c. Rode `terraform plan` novamente. O objetivo é chegar à mensagem: **"No changes. Your infrastructure matches the configuration."** Isso significa que seu código e a realidade estão sincronizados\!

**2. Importando a VM (`google_compute_instance`)**

Repita o processo para a VM, depois para o Cloud SQL, e assim por diante.

  * **Código inicial em `main.tf`:**

    ```terraform
    resource "google_compute_instance" "vm_web" {
      name = "vm-web-01"
      # O resto será preenchido depois
    }
    ```

  * **ID do Recurso:** `projects/SEU_PROJETO_ID/zones/ZONA_DA_VM/instances/NOME_DA_VM`

  * **Comando de Importação:**

    ```bash
    terraform import google_compute_instance.vm_web projects/SEU_PROJETO_ID/zones/us-central1-a/instances/vm-web-01
    ```

  * **Sincronização:** Rode `terraform plan`, veja as diferenças, e preencha o bloco `google_compute_instance.vm_web` com os atributos corretos (tipo de máquina, disco de boot, interface de rede, etc.) até que `terraform plan` não mostre mais nenhuma alteração.

-----

### Fase 4: Boas Práticas e Próximos Passos

1.  **Organize seu Código:** À medida que crescer, não deixe tudo em `main.tf`. Crie arquivos por função: `vpc.tf`, `compute.tf`, `database.tf`, `cloudrun.tf`.
2.  **Use Variáveis:** Mova valores como `project_id`, `region`, nomes de recursos, etc., para um arquivo `variables.tf` e crie um `terraform.tfvars` para definir seus valores. Isso torna seu código reutilizável.
3.  **Controle de Versão:** **Use Git desde o início\!** Faça commit de seus arquivos `.tf` (e adicione `.terraform/` e `*.tfstate*` ao seu `.gitignore`).
4.  **Recursos Dependentes:** Para recursos como Cloud SQL ou Cloud Run que dependem da VPC, o processo de importação é o mesmo. Apenas certifique-se de que no código final você referencie a VPC importada.
    ```terraform
    // Exemplo para Cloud Run
    resource "google_cloud_run_v2_service" "meu_app" {
      name     = "meu-app-run"
      location = "sua-regiao"

      template {
        // ... outras configs
        vpc_access {
          // Referencia a VPC já importada
          connector = google_vpc_access_connector.meu_conector.id
          egress    = "all-traffic"
        }
      }
    }
    ```
5.  **Automatize com CI/CD:** Quando seu código estiver estável e representando sua infraestrutura, o próximo passo é automatizar a execução do Terraform usando ferramentas como Cloud Build, GitHub Actions ou Jenkins. Isso garante que as mudanças sejam aplicadas de forma controlada e auditável.

Comece com o recurso mais fundamental (a VPC), depois as sub-redes, regras de firewall, depois o Cloud SQL, e por fim as VMs e os serviços do Cloud Run. É um trabalho metódico, mas o investimento trará enormes benefícios de gerenciamento e segurança a longo prazo.