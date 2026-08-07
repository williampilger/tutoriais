# Ao abrir o VMWare após uma atualização, receber o erro `Unnable to install modules...`

> O erro geralmente aparece em um modal, indicando o caminho do log.
> E com `(Exit code 1)` no final.
>
> Feche o aviso, e cancele a "instalação".

"Force" a atualização dos pacotes, que tudo tende a funcionar novamente:

```bash
sudo apt update
sudo apt upgrade -y
```

> ⚠️ Se você tiver com o *SecureBoot* ativo, deve ser necessário reiniciar e assinar os módulos de kernel.

Se mesmo assim não funcionar, tente:

```bash
# instalar/reinstalar os headers (No ubuntu --->> ATENÇÃO, que no Fedora, por exemplo, o comando é bem difetrente, envolve o rpm e é o kernel-headers)
sudo apt install --reinstall linux-headers-$(uname -r) build-essential

# Rodar a compilação manualmente
sudo vmware-modconfig --console --install-all
```
