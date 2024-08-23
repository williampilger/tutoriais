# Alterar estado inicial do NumLock na tela de bloqueio (após reinício)

1. Pressione `Win + R`, digite `regedit` e pressione `Enter` para abrir o Editor de Registro.
2. Navegue até a seguinte chave:
   ```
   HKEY_USERS\.DEFAULT\Control Panel\Keyboard
   ```
3. Dê um duplo clique em `InitialKeyboardIndicators`.
4. Altere o valor para `2147483650` para ativar o NumLock por padrão (o valor original pode ser `2147483648`, que desativa o NumLock).
5. Clique em `OK` e feche o Editor de Registro.
6. Reinicie o computador para verificar se o NumLock permanece ativado.
