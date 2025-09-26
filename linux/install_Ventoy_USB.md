# Instalar Ventoy em um pendrive

Liste as unidades conectadas, e localise o nome da sua com:

> lsblk

Baixe o ventoy do [site oficial](https://www.ventoy.net/), e extraia o conteúdo do arquivo compactado. Navegue em seguida até o diretório dos scripts e:

> sudo chmod +x *.sh

> sudo ./Ventoy2Disk.sh -I /dev/sdc

Substituindo `sdc` pela sua unidade correta.

---

### Solução de Problemas

*Isso é com base nos problemas que EU tive.*

| Problema | Solução |
| --- | --- |
| Mesmo usando `sudo` não ter privilégios suficientes | Desconecte a unidade e contecte-a novamente. Não ejetar ela depois de conectar (parece anti-intuitivo, mas é isso) |
