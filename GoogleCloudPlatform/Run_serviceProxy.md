# Proxy de Instância do CloudRun

Esta função traz para a máquina local (seu PC) o tráfego de rede do Serviço do Cloud Run.

```sh
REGION=southamerica-east1
PROJECT=dev-authentyglobalservices
SERVICE=logging-system-24001

gcloud beta run services proxy --region $REGION --project $PROJECT $SERVICE
```

