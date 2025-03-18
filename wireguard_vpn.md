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

### Microsoft Windows

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

### Linux

1. Habilitar o encaminhamento de pacotes no servidor
   1. Abra o arquivo de configuração do sysctl:
      - ```bash
        sudo nano /etc/sysctl.conf
        ```
   2. Procure (ou adicione) a linha referente ao `net.ipv4.ip_forward` e certifique-se de que ela esteja assim:
      - ```
        net.ipv4.ip_forward=1
        ```
   3. Salve o arquivo e rode o comando para aplicar as alterações:
      - ```bash
        sudo sysctl -p
        ```
2. Gerar chaves (no servidor e no cliente)
   1. No **servidor**, gere a chave privada e pública:
      - ```bash
        cd ~
        umask 077  # Para garantir permissões seguras
        wg genkey | tee server_private.key | wg pubkey > server_public.key
        ```
      - `server_private.key`: chave privada do servidor.
      - `server_public.key`: chave pública do servidor.
   2. No **cliente**, faça o mesmo processo (em outra máquina ou contêiner, por exemplo):
      - ```bash
        cd ~
        umask 077
        wg genkey | tee client_private.key | wg pubkey > client_public.key
        ```
      - `client_private.key`: chave privada do cliente.
      - `client_public.key`: chave pública do cliente.
3. Configuração no servidor
   1. Criar arquivo de configuração `/etc/wireguard/wg0.conf`
      - ```bash
         sudo nano /etc/wireguard/wg0.conf
         ```
      - ```conf
        [Interface]
        # Copie o conteúdo da chave privada
        PrivateKey = <CONTEÚDO_DO_ARQUIVO_server_private.key>
        # Endereço IP interno do WireGuard (será a "sub-rede" do túnel)
        Address = 10.8.0.1/24
        # Porta que o WireGuard vai "escutar"
        ListenPort = 51820
        
        # Comandos executados ao "subir" a interface (iptables para NAT, se desejar)
        #PostUp = iptables -t nat -A POSTROUTING -o <interface_de_rede_externa> -j MASQUERADE
        #PostDown = iptables -t nat -D POSTROUTING -o <interface_de_rede_externa> -j MASQUERADE

        # Configuração do peer (cliente)
        [Peer]
        # PublicKey do cliente
        PublicKey = <CONTEÚDO_DO_ARQUIVO_client_public.key>
        # Faixa de IP permitida para o cliente
        AllowedIPs = 10.8.0.2/32
        ```
      - **Observações:**
        - Substitua `<CONTEÚDO_DO_ARQUIVO_server_private.key>` pelo que está dentro de `server_private.key`. Você pode fazer isso manualmente ou usar `cat server_private.key` e copiar-colar.
        - Em `PostUp` e `PostDown`, ajuste a interface de rede externa. Por exemplo, se for `eth0`, troque `<interface_de_rede_externa>` por `eth0`.
        - Caso não queira fazer NAT, você pode remover essas linhas de `PostUp` e `PostDown`, mas então precisará de roteamento adequado para sua rede.
        - Se quiser permitir que o cliente roteie todo o tráfego pela VPN, você precisará ajustar as rotas (por exemplo `AllowedIPs = 0.0.0.0/0, ::/0`) no **cliente**.
      - Salve e feche o arquivo.
    2. Ajustar permissões do arquivo de configuração
      - ```bash
        sudo chmod 600 /etc/wireguard/wg0.conf
        ```
    3. Subir a interface WireGuard
      - ```bash
        sudo wg-quick up wg0
        ```
      - Se não houver erros, a interface `wg0` estará ativa.
      - Para verificar o status, use:
         - ```bash
           sudo wg show
           ```
    4. Habilitar para iniciar junto com o sistema
      - ```bash
        sudo systemctl enable wg-quick@wg0
        ```
4. Configuração no cliente
   1. Abra (ou crie) o arquivo de configuração:
      - ```bash
        sudo nano /etc/wireguard/wg0.conf
        ```
      - ```
        [Interface]
        # Endereço IP interno do lado do cliente (o mesmo AllowedIPs que colocamos lá no servidor)
        Address = 10.8.0.2/24
        
        # Chave privada do cliente
        PrivateKey = <CONTEÚDO_DO_ARQUIVO_client_private.key>
        
        # (opcional) DNS = 1.1.1.1
        # Se quiser que o tráfego DNS passe pela VPN, também inclua algo como
        # DNS = 8.8.8.8
        
        [Peer]
        # Chave pública do servidor
        PublicKey = <CONTEÚDO_DO_ARQUIVO_server_public.key>
        
        # IP ou domínio do servidor + porta
        Endpoint = <IP_ou_Domínio_do_Servidor>:51820
        
        # Rotas permitidas. Para passar todo tráfego, use 0.0.0.0/0
        AllowedIPs = 0.0.0.0/0, ::/0
  
        # Para manter o túnel sempre ativo
        PersistentKeepalive = 25
        ```
      - Salve o Arquivo
   2. Ajuste permissões (igual no servidor):
      - ```bash
        sudo chmod 600 /etc/wireguard/wg0.conf
        ```
   3. Suba a interface:
      - ```bash
        sudo wg-quick up wg0
        ```
   4. Verifique se tudo está funcionando:
      - ```bash
        sudo wg show
        ```
   5.  Se quiser ativar a interface automaticamente na inicialização do sistema:
      - ```bash
        sudo systemctl enable wg-quick@wg0
        ```
5. Passos gerais de resolução de problemas (troubleshooting)
   1. **Verifique logs**: 
      - `sudo journalctl -u wg-quick@wg0` no servidor e no cliente para ver se houve erros ao subir a interface.
   2. **Confirme que as chaves estão corretas**:
      - O campo `PublicKey` no servidor deve ser a chave pública do cliente, e vice-versa.
   3. **Cheque porta/iptables/firewall**:
      - Confirme que a porta UDP (padrão 51820) está aberta no firewall do servidor (por exemplo, `ufw allow 51820/udp` no Ubuntu).
   4. **IP forwarding**:
      - Certifique-se de ter habilitado `net.ipv4.ip_forward=1` no servidor e, se necessário, no cliente.
   5.  **Rotas**:
      - Se estiver roteando todo o tráfego do cliente pelo servidor, use `AllowedIPs = 0.0.0.0/0, ::/0`. Se quiser apenas acesso à rede local do servidor, ajuste o `AllowedIPs` para a sub-rede adequada.



---

## Sobre

Tancks for *ChatGPT 4o* for the most information on the linux tutorial.

By: **Will.i.am**

2025.03.18 | Bom Princípio - RS - Brasil
