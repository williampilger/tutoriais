# No `Ubuntu 25.04 LTS`, as VMs ficam sem rede constantemente


> Este caso específico ocorreuquando o VMWare não criou o serviço de rede,
> e ao abrir o gerenciador de rede e iniciar ele manualmente tudo funciona.
>
> Este comando, então, vai criar isso automaticamente (como o instalador deveria ter feito)

**Você pode "resolver" o problema executando o serviço:**
```bash
sudo vmware-networks --start

# ver se tá rodando
sudo vmware-networks --status

# Ver quais redes estão OK
ip -br a | grep vmnet
```

Importante 1: Se o comando acima não fizer diferença, **este tutorial não resolve seu problema!**
Se, depois disso, você iniciar o VMWare e a rede funcionar, então o que falta é realmente colocar o serviço pra rodar no boot. Siga este tutorial.

Importante 2: Teste se realmente o serviço não existe:
```bash
systemctl is-enabled vmware vmware-networks
# isso deve retornar "not-found" >>> Isso indica que o erro é o mesmo que estamos tentando sanar aqui!
```


```bash
sudo tee /etc/systemd/system/vmware.service > /dev/null <<'EOF'
[Unit]
Description=VMware virtual networks
After=vmware.service network-online.target NetworkManager.service
Requires=vmware.service
Wants=network-online.target

[Service]
Type=oneshot
RemainAfterExit=yes
ExecStart=/etc/init.d/vmware start
ExecStop=/etc/init.d/vmware stop

[Install]
WantedBy=multi-user.target
EOF

sudo systemctl daemon-reload
sudo systemctl enable --now vmware
systemctl is-enabled vmware
```
