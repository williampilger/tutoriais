# Criar e configurar uma VPN com Wireguard

o *Wireguard* é uma tecnologia simples, leve, e bem segura. Usa criptografia de ponta.
Você pode (e deve) ler mais em [wireguard.com](https://www.wireguard.com/).

---

## Instalação

- **Windows**
  - Baixe o instalador e execute-o;
- **Linux**
  - ```sh
    sudo apt install -y wireguard
    ```


---


## Configuração 

No *Windows*, ou em dispositivos móveis, a configuração do *Wireguard* é um pouco mais gráfica e simples.
Os procedimentos são praticamente iguais, com a diferença que a interface gráfica vai gerar automaticamente as chaves privadas/públicas para o wireguard.

```
⚠️ Antes de Seguir: Tenha certeza que você tem uma porta pública aberta e direcionada para o seu servidor!!

Você deve precisar de acesso ao modem e roteador para realizar este direcionamento.
Não irei descrever este processo neste passo a passo.
Portanto, seu PC já precisa ter o acesso à porta de interesse aberta e direcionada.
```

**Microsoft Windows**
  - Clique em `Add empty tunnel...` para criar os Servidor e o Cliente;
  - Dê um nome a eles (não importa qual... mas costuma ser algo como `WG_Server` e `WG_Client`);
  - Você terá configurações parecidas com:
    - ```conf
      # WG_Server
      [Interface]
      PrivateKey = AP1sQhmULNSjxoT5gZgb6X6MRhuKXlespNLNyKcJRH8= # chave PRIVADA do SERVIDOR 
      ListenPort = 51820 # Porta pública (Necessariamente aberta no seu modem, acessível e direcionada para seu servidor)
      Address = 192.168.0.1/24 # IP do servidor dentro da rede LOCAL
      
      [Peer]
      PublicKey = 5OicFJjeN7rw0b+aLJTMfngDRqmEHpcK7heiDY4nfXY= # chave PUBLICA co CLIENTE 
      AllowedIPs = 192.168.0.30/32 # IP que o cliente pode obter na rede

      # Adicione mais Peers igual ao de cima...
      ```
    - ```conf
      # WG_Client
      [Interface]
      PrivateKey = EHMDxx1QVcV96diV/LTCNyAYRwiLOgmuKTGsfkCoGFo= # chave PRIVADA do CLIENTE 
      Address = 192.168.0.30/24 # IP que o cliente deve obter na rede
      DNS = 8.8.8.8, 1.1.1.1 # DNS de sua preferência
      
      [Peer]
      PublicKey = llu+PefVb52Oru2PWThEl7GrZDG8Uonb3AWq2+NkvFs= # chave PUBLICA co SERVIDOR 
      AllowedIPs = 0.0.0.0/0
      Endpoint = 128.201.149.82:51820 # IP público (web) do servidor, ou domínio, caso tenha um
      ```
  - Acesse as **Configurações do Adaptador** nas suas configurações de rede;
  - Abra as propriedades do seu adaptador e acesse a guia **Compartilhamento**;
  - Marque `Permitir que outros usuários da rede se conectem...`;
  - Selecione a rede `WG_Server` no seletor, e aceite o aviso (você não perderá o acesso à internet);
  - Agora deve ser possível conectar os clientes.
    - Exporte as configurações, e importe o cliente em outro dispositivo. Clique em `Iniciar` no server e no client, e tudo deve estar funcionando. 


---

## Sobre

By: **Will.i.am**

2025.03.18 | Bom Princípio - RS - Brasil
