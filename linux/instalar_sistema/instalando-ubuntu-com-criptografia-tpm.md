# Instalando o Ubuntu com Secure Boot e criptografia de disco via TPM 2.0

Dar boot diretamente pelo pendrive, com uma assinatura válida no Secure boot é uma tarefa meio difícil, então, o caminho mais fácil é:

1. Dar boot com o TPM ativo, mas o Secure Boot DESATIVADO;
2. Instalar o Ubuntu com criptografia LUKS com senha, padrão;
3. Depois de instalado, ativar o SecureBoot, e adicionar a uma chave ao TPM para não precisar digitar a senha toda vez:
  - ```bash
    sudo systemd-cryptenroll --tpm2-device=auto --tpm2-pcrs=7 /dev/sdX
    ```
  - substitui `/dev/sdX` pelo teu disco — geralmente `/dev/sda` ou `/dev/nvme0n1`
4. Edita o `/etc/crypttab` e adiciona `tpm2-device=auto` nas opções do volume
5. Reinicia e testa se funcionou
6. **OPCIONAL**: Se quiser remover sua senha LUKS:
    - ```bash
      sudo systemd-cryptenroll --wipe-slot=password /dev/sdX
      ```
