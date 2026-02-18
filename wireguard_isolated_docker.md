# WireGuard em Docker com total isolamento

```
⚠️ IMPORTANTE!

É, obviamente, mais fácil configurar o Wireguard via interface gráfica,
especialmente se você quiser fazer testes rápidos!

Antes de configurar tudo manualmente, experimente a instalação e teste gráfico.
Acesse A página oficial de download.
```

```
⚠️ IMPORTANTE!

>> Este tutorial usa uma imagem Docker NÃO OFICIAL, mantida pela Linuxserver.io !!

>> Este procedimento não foi amplamente testado por mim ainda, e NÃO VERIFIQUEI A SEGURANÇA E ORIGEM DESTA IMAGEM‼️
```

Links Útei
- Página Oficial [wireguard.com](https://www.wireguard.com/install/);
- Youtube Tutorial [Configuração GRÁFICA no WIndows](https://www.youtube.com/watch?v=AR5IWUpZbsk&t=343s);

---

Criar uma VPN particular com WireGuard, rodando em Docker e totalmente isolado.

PS1: *Wireguard pode ser instalado em qualquer Ubuntu-based Linux com `sudo apt install wireguard`, não precisa ser em Docker.*

PS2: *O termo **Totalmente Isolado** usado no título é por conta de ser possível rodar ele, via docker, compartilhando o acesso aos módulos `lib/modules` do kernel hospedeiro, tornando assim o container mais leve. Mas neste caso a aplicação não é independende do hospedeiro, e não funciona em Windows.*

---

## Criando o Servidor

### Criar o diretório para persistir os dados
  - ```sh
    # Linux Bash
    mkdir -p ~/wireguard/config
    ```
  - ```ps1
    # Microsoft PowerShell
    mkdir C:\wireguard\config
    ```

### Criando o Container
  - ````bash
    # Linux Bash
    PUBLIC_SERVER_IP=65.48.63.89
    PUBLIC_SERVER_PORT=51820
    docker run -d \
      --name wireguard \
      --cap-add=NET_ADMIN \
      -e PUID=1000 \
      -e PGID=1000 \
      -e SERVERURL=$PUBLIC_SERVER_IP \
      -e SERVERPORT=51820 \
      -e PEERS=1 \
      -e PEERDNS=auto \
      -e ALLOWEDIPS=0.0.0.0/0 \ #Personalize os IPs permitidos aqui (⚠️ e remova este comentário!!! não funcionam comentários assim!)
      -v ~/wireguard/config:/config \
      -p $PUBLIC_SERVER_PORT:51820/udp \
      --restart unless-stopped \
      lscr.io/linuxserver/wireguard
    ```
  - ```ps1
    # Microsoft PowerShell
    $PUBLIC_SERVER_IP="65.48.63.89"
    $PUBLIC_SERVER_PORT="51820"
    docker run -d `
      --name wireguard `
      --cap-add=NET_ADMIN `
      -e PUID=1000 `
      -e PGID=1000 `
      -e SERVERURL=$PUBLIC_SERVER_IP `
      -e SERVERPORT=51820 `
      -e PEERS=1 `
      -e PEERDNS=auto `
      -e ALLOWEDIPS="0.0.0.0/0" `  # Personalize os IPs permitidos aqui
      -v "$HOME\wireguard\config:/config" `
      -p $PUBLIC_SERVER_PORT:51820/udp `
      --restart unless-stopped `
      lscr.io/linuxserver/wireguard
    ```

### Obter as configurações do Cliente
  - ```sh
    docker exec wireguard cat /config/peer1/peer1.conf
    ```

### Configurações do Roteador/Rede
  - Garanta que do seu IP público a porta `51820/UDP` está aberta e apontando para o IP do seu servidor.

---

## Configurando o acesso em seus dispositivos externos
  - Istale o WireGuard
    - **Windows**: Baixe o instalador e execute-o;
    - **Linux**
      - ```sh
        sudo apt install -y wireguard
        ```
  - Configurando:
    - **Windows**: Importe ou crie-os graficamente
    - **Linux**:
      - ```sh
        # COnsiderando que você deu o nome de `MG_Client` pro seu cliente
        # Copie o arquivo de configuração para a pasta do Wireguard
        sudo cp MG_Client.conf /etc/wireguard/MG_Client.conf
        # Dê as permissões
        sudo chmod 600 /etc/wireguard/MG_Client.conf
        # Ative a conexão
        sudo wg-quick up MG_Client

        # Para verificar se está OK
        wg

        # Para finalizar
        sudo wg-quick down MG_Client
        ``` 

Precisa configurar do zero? [O lugar é esse](./wireguard_vpn.md)

---

## Sobre

Tancks for *ChatGPT 4o* for the most information on this tutorial.

By: **Will.i.am**

2025.03.15 | Bom Princípio - RS - Brasil
