# Criando a Infraestrutura de Rede no GCP

Este tutorial **não está completo**. Estou anotando apenas o que estudei por necessidade.
No momento, estou aprendendo apenas o necessário.

---

### Criando uma subrede Privada

Diferentemente de uma rede doméstica convencional, as VPCs do Google Cloud não fazem NAT automaticamente.
Então, uma VM sem um IP público não pode acessar a internet, a menos que você configure uma NAT explicitamente.

*Se ainda não tem, crie uma rede VPC com uma subrede privada:*
```sh
gcloud compute networks create minha-rede \
    --subnet-mode=custom
gcloud compute networks subnets create minha-subrede \
    --network=minha-rede \
    --range=192.168.1.0/24 \
    --region=$REGION
```

*Sequiser acesso à internet -> Crie um Cloud Router e o Cloud NAT:*
```sh
# O Cloud Router é necessário para o NAT funcionar:
gcloud compute routers create meu-router \
    --network=minha-rede \
    --region=$REGION
gcloud compute routers nats create meu-nat \
    --router=meu-router \
    --region=$REGION \
    --nat-all-subnet-ip-ranges \
    --auto-allocate-nat-external-ips
```

Agora, teoricamente, sua rede PRIVADA, tem acesso à internet. Talvez seja necessário ajustar as regras de Firewall para tal.

**⚠️ Acredito que este método não é muito indicado por questões de segurança!!**

---

### Conectores para a VPC

Os conectores servem para conectar aplicações serverless (containers do CloudRUN ou semelhantes), à sua VPC.

*Listar os conectores do seu projeto*
> cloud compute networks vpc-access connectors list

Para criar um novo:
```sh
CONNECTOR="meu-vpc-connector"
VPC_NAME="default"
REGION="southamerica-east1"
gcloud compute networks vpc-access connectors create ${CONNECTOR} \
  --network=$VPC_NAME \
  --region=$REGION \
  --range=10.8.0.0/28
```

Para usa-lo no deploy das suas aplicações, adicione ao comando do `gcloud run deploy` o seguinte: 
> --vpc-connector $VPC_CONNECTOR
