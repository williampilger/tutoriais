# Instalando o Ubuntu com Secure Boot e criptografia de disco via TPM 2.0

Dar boot diretamente pelo pendrive, com uma assinatura válida no Secure boot é uma tarefa meio difícil, então, o caminho mais fácil é:

1. Dar boot com o TPM ativo, mas o Secure Boot DESATIVADO;
2. Instalar o Ubuntu com criptografia LUKS com senha, padrão;
3. Depois de instalado, ativar o SecureBoot (MicrosoftSigned Enable), e adicionar a uma chave ao TPM para não precisar digitar a senha toda vez:
    - ```bash
      sudo systemd-cryptenroll --tpm2-device=auto --tpm2-pcrs=7 /dev/sdX
      ```
    - substitui `/dev/sdX` pelo teu disco — geralmente `/dev/sda` ou `/dev/nvme0n1`
    - Pra saber quais tem:
        - ```bash
          lsblk -f
          ```
    - O que vai ver:
        - ```bash
          nvme0n1
          ├─nvme0n1p1   vfat    EFI
          ├─nvme0n1p2   ext4    /boot
          └─nvme0n1p3   crypto_LUKS    ← essa é a que você quer
          ```
4. Instalar dependências:
    - ```bash
      sudo apt install tpm2-tools cryptsetup-initramfs
      ``` 
5. Edita o `/etc/crypttab` e adiciona `tpm2-device=auto` nas opções do volume:
    - Vai ter algo como:
        - ```
          dm_crypt-0  UUID=xxxx-xxxx  none  luks
          ```
    - Insira a opção, ficando assim:
        - ```
          dm_crypt-0  UUID=xxxx-xxxx  none  luks,tpm2-device=auto
          ```
6. Regenere o initramfs (⚠️só inicie se for TERMINAR!!!)
    - ```bash
      sudo update-initramfs -u
      ```
    - ⚠️ **ATENÇÃO**: SE VOCÊ VIR AVISOS DE QUALQUER TIPO DE ERRO AQUI, PESQUISE O QUE É E RESOLVA, POIS QUE ESSE COMANDO RODADO COM ERROS DESTROI A INICIALIZAÇÃO DA SUA MÁQUINA!!! Se você rodou o comando, e deu algum erro, você PRECISA CORRIGIR O PROBLEMA ANTES DE REINICIAR!!!
7. Reinicia e testa se funcionou
8. **OPCIONAL**: Se quiser remover sua senha LUKS:
    - ```bash
      sudo systemd-cryptenroll --wipe-slot=password /dev/sdX
      ```
