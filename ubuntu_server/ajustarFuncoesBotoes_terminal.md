# Configurar função dos botões e tampa no Linux via terminal

  Isso é válido também para o Ubuntu Server (22.04LTS, no meu caso).
  
### 1
Acesse o servidor/pc via ssh ou abra o terminal no próprio dispositivo

### 2
Abra para edição o arquivo `/etc/systemd/logind.conf` usando:

> sudo nano /etc/systemd/logind.conf

### 3
Defina o campo `HandleLidSwitch` como `ignore`, e lembre de descomentar a linha.

### 4
Se a propriedade `LidSwitchIgnoreInhibited` estiver sendo usada, seu valor deve ser `no`

### 5
Salve as alterações pressionando `Ctrl + X` e confirmando com `Y` seguido de `Enter`.

### 6
Reinicie o serviço com:

> sudo systemctl restart systemd-logind



# Sobre

Fontes:
  - [Como evitar que o Ubuntu entre em suspensão ao fechar o laptop](https://www.edivaldobrito.com.br/como-evitar-que-o-ubuntu-entre-em-suspensao-ao-fechar-o-laptop/);
  - [Como desativar o modo de suspensão e definir as configurações de energia da tampa para Ubuntu ou Red Hat Enterprise Linux 7](https://www.dell.com/support/kbdoc/pt-br/000179566/how-to-disable-sleep-and-configure-lid-power-settings-for-ubuntu-or-red-hat-enterprise-linux-7);

By: **will.i.am** | Bom Princípio - RS
