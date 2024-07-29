# Reiniciando Máquina Remota Ubuntu para Iniciar no Windows em Dual Boot

Este tutorial orienta sobre como reiniciar uma máquina remota que está rodando Ubuntu e iniciar no Windows, em um sistema de dual boot onde o Ubuntu é o sistema operacional padrão.


## Passos para Reiniciar e Iniciar no Windows via SSH

### 1. Acesse a Máquina Remotamente

Use SSH para acessar a máquina remota que está rodando Ubuntu.

```bash
ssh username@remote_IP_address
```

### 2. Instale o `grub-reboot` (se não estiver instalado)

O `grub-reboot` é um comando que permite definir uma entrada de inicialização única no GRUB para o próximo boot. Geralmente, ele já vem instalado com o GRUB, mas é bom verificar.

```bash
sudo apt update
sudo apt install grub-common
```

### 3. Verifique as Entradas do GRUB

Verifique as entradas do GRUB para identificar qual entrada corresponde ao Windows.

```bash
grep -E "^menuentry " /boot/grub/grub.cfg
```

Isso listará todas as entradas do GRUB. Anote o nome ou a posição da entrada que corresponde ao Windows.

### 4. Configure o Próximo Boot para Windows

Use o `grub-reboot` para definir o Windows como o sistema operacional para o próximo boot. Supondo que o Windows está na posição 1 (as posições começam a contar de 0):

```bash
sudo grub-reboot "Windows Boot Manager (on /dev/sdXY)"
```

Ou, se você usar a posição:

```bash
sudo grub-reboot 1
```

### 5. Reinicie a Máquina

Finalmente, reinicie a máquina para que ela inicie no Windows na próxima vez:

```bash
sudo reboot
```

## Exemplo Completo

1. Acesse a máquina via SSH:

   ```bash
   ssh username@remote_IP_address
   ```

2. Verifique as entradas do GRUB:

   ```bash
   grep -E "^menuentry " /boot/grub/grub.cfg
   ```

   Saída possível:

   ```
   menuentry 'Ubuntu' --class ubuntu --class gnu-linux --class gnu --class os ...
   menuentry 'Advanced options for Ubuntu' --class ubuntu --class gnu-linux --class gnu --class os ...
   menuentry 'Windows Boot Manager (on /dev/sda1)' --class windows --class os ...
   ```

3. Configure o próximo boot para Windows:

   ```bash
   sudo grub-reboot "Windows Boot Manager (on /dev/sda1)"
   ```

4. Reinicie a máquina:

   ```bash
   sudo reboot
   ```

# About

100% By ChatGPT
