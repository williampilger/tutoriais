# Criando primeira VM do Ubuntu Server no Multipass (windows)

## Instalando o Multipass

Faça o download do aplicativo no [site oficial](https://multipass.run/install), onde também poderá encontrar as instruções completas.


## Criando a VM

Depois da instalação e reinício do sistema, pode-se criar uma VM com:

> multipass launch --name foo

Onde `foo` é o novo nome da nova VM.

Os arquivos são salvos no diretório do Hyper-V (`C:\ProgramData\Microsoft\Windows\Hyper-V\Virtual Machines`).



## Definir/Alterar a senha de um usuário

Abra o terminal no **Hospedeiro** e execute:

> multipass exec <nome_da_instância> -- sudo passwd <nome_do_usuário>

O usuário padrão é `root` a senha eu desconheço, então defino ela nessa etapa.
