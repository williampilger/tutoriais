# Problema ao montar partição NTFS com flag de proteção do Windows

O Windows pode travar uma partição para montagem, gerando o erro abaixo quando tentamos montar ela no linux:

> Error mounting /dev/nvmeOn1p3 as /media/user/OS: wrong fs type, bad option, bas superblock on /dev/nvmeOn1p3, missing codepage or helper program, or other error

PS.: Obviamente, o nome da uidade e o caminho da montagem serão diferentes no seu caso.

---

*A solução:*
```bash
# Verifica o estado da partição
sudo ntfsfix /dev/nvme0n1p3

# Se confirmar dirty bit, força limpeza:
sudo ntfsfix -d /dev/nvme0n1p3
```
