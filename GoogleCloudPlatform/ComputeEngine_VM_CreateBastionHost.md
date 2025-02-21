# Criando um Bastion Host (vulgo ponto de acesso)

Em muitos casos, o acesso pelo CloudShell e o CLI não são o suficiente, e você precisa interagir diretamente com a sua rede VPC, via SSH, por exemplo.

Pra isso, usamos o chamado *Bastion Host*, que nada mais é que uma Virtual Machine à qual você tem acesso SSH, e que tem acesso à sua rede VPC do GCP.


## Antes de começar:

  Tenha certeza que você já possui uma subnet **PRIVADA** para colocar seu host, já que você não quer que ele seja acessível de fora, e que vai dar acesso total à sua rede para esta máquina.

  Lembre-se, obviamente, de ter criado esta subnet na mesma região onde deseja hospedar sua VM.


---

## Criando uma VM para uso interno (Bastion Host)

Neste exemplo, vou usar a máquina mais barata.

```sh
PROJECT_ID="sample-projectName"
REGION="us-west1"
ZONE="us-west1-a"
SUBNET_NAME="subnet-us-private"

gcloud compute instances create bastion-host \
    --zone=$ZONE \
    --machine-type=f1-micro \
    --image-family=debian-12 \
    --image-project=debian-cloud \
    --network-tier=STANDARD \
    --subnet=projects/$PROJECT_ID/regions/$REGION/subnetworks/$SUBNET_NAME \
    --no-address \
    --metadata=global-ssh=true
```
