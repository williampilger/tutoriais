# Ativando um Serviço no Modo de Segurança do Windows

Isso pode ser útil em casos específicos onde o Windows não inicia mais, mas você precisa realizar alguma coisa antes de formatar um computador (como por exemplo, retornar alguma licença de um software).

```
⚠️ Cuidado com esta funcionalidade!
Se você ativar alguma coisa que não permita a inicialização do sistema, você pode perder definitivamente o acesso à máquina.

No exemplo abaixo, eu indico usar o modo de segurança com rede.
Se, nesse caso, você ativar algo que impessa a inicialização, você ainda pode usar um dos outros modos de segurança e remover o serviço.
```

-----

### **Objetivo 1: Descobrir o nome do serviço sem sair do Modo de Segurança (que pode ser pulado, se você souber exatamente o nome dele)**

Existem duas maneiras principais e muito confiáveis de fazer isso.

#### **Método 1: Usando o Editor do Registro (Mais Visual e fácil)**

O Editor do Registro contém a lista de TODOS os serviços instalados no seu sistema, mesmo os que não rodam no Modo de Segurança.

1.  No Modo de Segurança, pressione as teclas `Win + R` para abrir a caixa "Executar".
2.  Digite `regedit` e pressione Enter.
3.  No Editor do Registro, navegue pela árvore de pastas à esquerda até o seguinte caminho:
    ```
    HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services
    ```
4.  Clique na pasta `Services`. Dentro dela, você verá uma longa lista de outras pastas (chamadas "chaves"). **Cada uma dessas pastas corresponde a um serviço instalado no seu PC.**
5.  Role a lista e procure por uma pasta que tenha o nome do seu software ou do fabricante. Por exemplo, para o CodeMeter, a pasta se chama `CodeMeter.exe`. Para outro software, pode ser o nome da empresa ou do produto.
6.  **O nome exato dessa pasta é o "Nome do Serviço" que precisamos.** Anote-o.

#### **Método 2: Usando o PowerShell (Alternativa, menos intuitivo)**

1.  Clique com o botão direito no menu Iniciar e selecione **Windows PowerShell (Admin)**. Se essa opção não aparecer, procure por "PowerShell", clique com o botão direito e selecione "Executar como administrador".
2.  Na tela azul do PowerShell, digite o seguinte comando e pressione Enter:
    ```powershell
    Get-Service | Select-Object Name, DisplayName, Status
    ```
3.  Isso listará todos os serviços. Procure na coluna `DisplayName` (Nome de Exibição) pelo seu programa. A coluna `Name` (Nome) ao lado mostrará o nome exato do serviço que você precisa.

-----

### **Objetivo 2: Habilitar o Serviço no Modo de Segurança**

Agora que você **tem** o nome do serviço, vamos usar o `regedit` (que você talvez já tenha aberto) para autorizá-lo a rodar.

1.  No `regedit`, navegue até este caminho:

    ```
    HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\SafeBoot\Network\
    ```

    *(Use a subpasta `Network` para garantir que você tenha internet, que geralmente é necessária para desativação de licenças).*

2.  Clique com o botão direito na pasta `Network` e selecione **Novo \> Chave**.

3.  **Renomeie esta nova chave para o nome exato do serviço** que você descobriu (ex: `CodeMeter.exe`).

4.  Clique na chave que você acabou de criar. No painel direito, dê um duplo clique no valor `(Padrão)`.

5.  Na pequena janela que aparece, digite a palavra `Service` e clique em OK.

### **Último Passo: Iniciar o Serviço e Executar o Programa**

1.  **Reinicie o computador.** Ele deve voltar para o Modo de Segurança com Rede.
2.  Após reiniciar, o serviço que você autorizou deve iniciar automaticamente.
3.  Tente abrir o seu programa. Ele agora deve funcionar e permitir que você faça o que precisa.

**Se o programa ainda não abrir,** o serviço pode não ter iniciado sozinho. Vamos forçá-lo:

1.  Abra o **PowerShell (Admin)** ou o **Prompt de Comando (Admin)** novamente.
2.  Digite o comando `sc start` seguido pelo nome do serviço. Por exemplo:
    ```
    sc start CodeMeter.exe
    ```
3.  Pressione Enter. Se o comando for bem-sucedido, tente abrir seu programa mais uma vez.


Sinto muito pela falha na comunicação inicial. Espero que este guia, ajustado para a sua situação real, resolva o problema e permita que você salve seus dados importantes.

