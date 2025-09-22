# Erro `VERR_VMX_IN_VMX_ROOT_MODE` ao tentar iniciar uma VM no Virtualbox

*Este erro indica que o suporte a virtualização do processador já está em uso por outro programa.*

O mesmo erro no windows pode ser causado pelo `Hyper-V`.
Mas, neste caso estamos falando de um `Linux Ubuntu-based`.

Para saber se o sistema está em uso:
> lsmod

Procure por `kvm_intel` (para processadores Intel) ou `kvm_amd` (para processadores AMD). Se algum deles aparecer na lista, significa que o KVM está carregado e ativo.




## Solução (Temporária)

Para fazer com que o sistema descarregue a funcionalidade,liberado-a para o Virtualbox:

```bash
# Para processadores Intel
sudo modprobe -r kvm_intel

# Para processadores AMD
sudo modprobe -r kvm_amd
```

Se, porventura, for necessário desfazer:
```bash
sudo modprobe kvm_intel
```
