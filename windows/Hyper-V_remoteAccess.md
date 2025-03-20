# Hyper-V: Usando o Remote Manager

Isso serve para controlar o Hyper-V de um PC em outro, ambos com `Windows PRO`.

```
⚠️ Isso funciona só quando quer, pelo visto. Cada sistema é imprevisível.
Mas, você deve estar acostumado com isso, afinal, está usando Windows... :-/
```


### 1️⃣ Ativando o Hyper-V em ambos os PCs

1. Nos dois PCs, pesquise por "Recursos adicionais" no menu iniciar.
2. Marque a árvore completa do Hyper-V
3. Confirme a instalação de tudo
4. Reinicie o PC (isso será exigido para completar a instalação)


### 2️⃣ Permissões

Será necessário executar alguns ajustes no servidor e no client para permitir o acesso:

1. No Servidor
    1. Abra o PowerShell como administrador
        - ```ps1
          winrm quickconfig
          # Confirme com Y quando perguntar
          # Se receber um erro sobre o Firewall em redes públicas, isso não será problema, a menos que você esteja em uma rede pública.
          ```
        - ```ps1
          Enable-WSManCredSSP -Role "Server"
          ```
 2. No Cliente
     1. Abra o PowerShell como administrador
         - ```ps1
           Enable-WSManCredSSP -Role "Client" -DelegateComputer "NOME_DO_SERVIDOR"
           ```


### 2️⃣ Conectando o Cliente ao Servidor

1. Acesse o PC Cliente, e abra o Hyper-V;
2. Clique em "Conectar do Servidor";
3. Adicione o nome do PC e as credenciais
    1. Marque a opção "Informar usuário"
    2. o Usuário deve ser informado no formato `NOME_DO_SERVIDOR@Usuario`
4. Pronto