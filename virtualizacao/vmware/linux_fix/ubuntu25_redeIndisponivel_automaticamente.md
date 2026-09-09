# No `Ubuntu 25.04 LTS`, as VMs ficam sem rede constantemente


> Este caso específico ocorreuquando o VMWare não criou o serviço de rede,
> e ao abrir o gerenciador de rede e iniciar ele manualmente tudo funciona.
>
> Este comando, então, vai criar isso automaticamente (como o instalador deveria ter feito)



Importante: Teste se realmente o serviço não existe
```bash
systemctl is-enabled vmware vmware-networks
# isso deve retornar "not-found" >>> Isso indica que o erro é o mesmo que estamos tentando sanar aqui!
```


```bash
sudo tee /etc/systemd/system/vmware.service > /dev/null <<'EOF'
[Unit]
Description=VMware Workstation services
After=network-online.target NetworkManager.service
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
