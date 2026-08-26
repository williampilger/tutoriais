# Como instalar o VMware no Linux


### Download

Baixe o instalador [do site oficial](https://support.broadcom.com/group/ecx/downloads), buscando pelo `VMWare Workstation PRO` nos produtos gratuitos diponíveis.

*Sim, você precisa de uma conta.*


### Instalação

Execute o `.bundle` que tiver baixado:

```bash
cd ~/Downloads # se este for o diretório onde você salvou, obviamente
chmod +x ./VMware-Workstation-Full-26H1-25388281.x86_64.bundle 
sudo ./VMware-Workstation-Full-26H1-25388281.x86_64.bundle
```


### Desinstalação

```bash
sudo vmware-installer -u vmware-workstation
```
