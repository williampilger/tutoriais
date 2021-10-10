# Desativando o Windows update no Windows 10 definitivamente

Descreverei abaixo dois métodos, retirados do [forum da microsoft](https://answers.microsoft.com/pt-br/windows/forum/all/quero-desativar-de-vez-atualizacoes-do-windows/28ddc447-c170-4d14-b110-dbcc62663de5?auth=1).

## Método 1

1 - Abra o terminal como administrador, uma forma de fazer isso é pressionando **windows** + **X** e clicando em **Prompt de comando (admin)**.

2 - Digite `net stop wuauserv` para desativar, e `net start wuauserv` para reativar.

Este método pode não funcionar sempre.

## Método 2

Este método é bem mais complexo, e exige um pouco mais de atenção.

**Primeiro passo**

  1 - Baixe [este arquivo de registro.reg](aux/WindowsUpdateDisable.reg) (após abrir, clique em **RAW** e pressione **Ctrl** + **S** para salvá-lo)
  
  2 - Execute o arquivo de registro, e clique em `Sim` para confirmar a alteração do registro.

  3 - Reinicie o computador (obrigatoriamente)
  
**Segundo passo**

  1 - Pressione **Windows** + **R**, ou procure por **executar** no menu iniciar;
  
  2 - Digite `Services.MSC` e pressione **Enter**;
  
  3 - Na janela **Serviços** localize o `Windows Update`;
  
  4 - Altere o **Tipo de inicialização** para **desativado**;
  
  5 - Pare o serviço, aplique e salve.
## Sobre

By: will.i.am
Harmonia - RS
