# Redes no Docker

Os containers rodando no docker podem se comunicar entre sí, estando conectados na mesma rede.
E você pode listar as redes disponíveis usando:
> docker network ls

Assim como também pode conferir emq ual rede um containter está conectado com:
> docker inspect 3977e4012729 #definindo o ID adequado...

Se pode comunicar entre os containers usando hostnames, faça isso criando primeiro uma rede nova (bom para isolar os itens. Depois Execute o container na nova rede e definindo o hostname.

> docker network create --driver bridge minha-rede-exemplo

> docker run -d --name ubuntu-1 --network minha-rede-exemplo ubuntu

Agora, se você criar mais containers na mesma rede poderá acessá-los entre sí pelo hostname.
**OBS:** O hostname NÃO funciona nas interfaces de rede padrão do docker. Você precisará criar uma personalizada para isso.

As redes padrão do Docker tem as seguintes funcionalidades:

| NAME | Função |
| --- | --- |
| `bridge` (DEFAULT) | Coloca o container na mesma rede do host |
| `host` | O Container roda NO HOST. Ou seja a porta do container é a mesma porta do Host, e ele responde pelo mesmo IP do host |
| `none` | Container sem comunicação de rede |