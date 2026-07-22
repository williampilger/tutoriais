# Erro ao iniciar relacionado ao 'vmmon'

Esse erro costuma acontecer se você tem Secure Boot ativo no Linux.

Esse erro acontece quando o Linux não consegue carregar o driver do VMware (`vmmon`). Ele costuma ocorrer por dois motivos: **os módulos do VMware não foram compilados após uma atualização do Kernel**, ou o **Secure Boot da BIOS está ativado** (impedindo que drivers de terceiros sejam carregados).

Aqui estão as etapas para resolver:

---

### Passo 1: Tentar recompilar os módulos do VMware

Abra o terminal e execute o comando abaixo para forçar a compilação dos módulos para a sua versão atual do Linux:

```bash
sudo vmware-modconfig --console --install-all

```

> **Se o comando rodar sem erros:** Feche e abra o VMware novamente. O problema deve estar resolvido.
> **Se o comando falhar ou indicar erro de chave/assinatura:** Siga para o **Passo 2**.

---

### Passo 2: Resolver o bloqueio do Secure Boot

Se o Secure Boot estiver ativado na sua placa-mãe, o Linux impede que o módulo `vmmon` rode porque ele não tem uma assinatura digital reconhecida.

Você tem duas opções para resolver isso:

#### Opção A (Mais rápida - MAS É UMA GAMBIARRA!)

1. Reinicie o computador e entre na **BIOS/UEFI** (geralmente apertando `F2`, `F12` ou `DEL` ao ligar).
2. Vá até a aba **Security** ou **Boot**.
3. Procure por **Secure Boot** e mude para **Disabled** (Desativado).
4. Salve e inicie o Linux normalmente.

---

#### Opção B (Manter o Secure Boot ativo e assinar os módulos)

Se você não quer ou não pode desativar o Secure Boot, crie uma chave de segurança para assinar os módulos do VMware manualmente:

1. Execute os comandos no terminal para gerar e assinar os módulos:
```bash
# 1. Gerar as chaves de assinatura
openssl req -new -x509 -newkey rsa:2048 -keyout MOK.priv -outform DER -out MOK.der -nodes -days 36500 -subj "/CN=VMware/"

# 2. Assinar os módulos do VMware
sudo /usr/src/linux-headers-$(uname -r)/scripts/sign-file sha256 ./MOK.priv ./MOK.der $(modinfo -n vmmon)
sudo /usr/src/linux-headers-$(uname -r)/scripts/sign-file sha256 ./MOK.priv ./MOK.der $(modinfo -n vmnet)

# 3. Importar a chave para o sistema
sudo mokutil --import MOK.der

```


2. O terminal pedirá para você **criar uma senha temporária** (anote ou lembre dela).
3. Reinicie o computador:
```bash
sudo reboot

```


4. Ao reiniciar, uma **tela azul (MOK Manager)** aparecerá antes do Linux carregar:
* Pressione qualquer tecla para entrar.
* Selecione **Enroll MOK** > **Continue** > **Yes**.
* Digite a **senha temporária** criada no passo anterior.
* Selecione **Reboot**.



Assim que o sistema reiniciar, o módulo `vmmon` estará assinado e o VMware abrirá normalmente.
