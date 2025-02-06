# Criando a Infraestrutura de Rede no GCP

Este tutorial **não está completo**. Estou anotando apenas o que estudei por necessidade.
No momento, estou aprendendo apenas o necessário.

---

## Conectores para a VPC

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
