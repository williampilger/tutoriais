# Warsaw não reconhecido no `Ubuntu 25.04`

DEPOIS DE TER JÁ ELE INSTALADO, E ELE AINDA NÃO FUNCIONAR:

Veja se o serviço está rodando:
```bash
systemctl list-units --type=service | grep -i warsaw
```

Edita o serviço
> sudo systemctl edit warsaw

Add o texto abaixo:
```ini
[Service]
Environment="GLIBC_TUNABLES=glibc.rtld.execstack=2"
```

E depois roda:
```bash
sudo systemctl daemon-reload
sudo systemctl restart warsaw
systemctl show warsaw -p Environment
```
