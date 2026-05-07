# Como aumentar o tamanho do disco de uma máquina virtual no VMware

Se você precisa aumentar o tamanho do disco de uma máquina virtual no VMware, lembre-se de que não se trata somente de expandir o disco virtual,
mas também é necessário redimensionar a partição dentro do sistema.

> Em alguns casos (como no `Microsoft Windows`), a partição do sistema não é a última partição do disco,
> o que pode complicar o processo.
>
> No caso do Windows em específico, você **pode** excluir a partição de recuperação (que normalmente ocupa menos de 1GB) sem uma perda de funcionalidade significativa.
> Obviamente, **só é recomendado fazer isso se você não tiver nada altamente importante nessa VM**, pois a partição de recuperação pode ser útil em caso de falhas graves do sistema.
>
> Caso opte por manter a partição, ela precisará ser movida.

---

## Passo 1: Aumentar o tamanho do disco virtual
1. Abra o VMware e selecione a máquina virtual que deseja aumentar o disco.
2. Clique com o botão direito na máquina virtual e selecione "Configurações" ou "Settings".
3. Na janela de configurações, vá para a seção "Hardware" e selecione o disco rígido que deseja aumentar.
4. Clique em "Expandir" ou "Expand" e insira o novo tamanho desejado para o disco.
5. Confirme as alterações e feche a janela de configurações.

---

## Passo 2: Redimensionar a partição

Embora existam formas de fazer isso pelo próprio sistema (se você tiver em um sistema Linux, faça diretamente por ele),
mas aqui vou indicar o uso do `GParted Live`, que é uma ferramenta de particionamento de disco, e pode ser baixada [no site oficial](https://gparted.org/download.php).

1. Baixe a imagem ISO do GParted Live e monte-a na máquina virtual.
2. Adicione a imagem ISO do *GParted Live* como um CD/DVD na máquina virtual. 
3. Inicie a máquina virtual a partir da imagem ISO do GParted Live.
   1. Durante a inicialização, selecione a opção "GParted Live (Default settings)" ou similar.
   2. OU, se você estiver no `Windows` com o `Secure Boot` habilitado, reinicie a VM segurando o `Shift` pressionado para inicializar com o menu de inicialização, e selecione a opção de inicializar a partir do CD/DVD (onde o GParted Live está montado).
4. Na interface do GParted, selecione a opção `Don't touch keymap` ao iniciar.
5. Selecione seu idioma e as configurações iniciais.
6. Na janela principal do GParted, localize o disco que você expandiu
7. Mova a partição de recuperação (se houver) para o final do disco:
   1. Identifique a partição que precisa ser movida, selecione ela, e clique em `Redimensionar/Mover` ou `Resize/Move`.
   2. Na parte superior da janela, arraste a partição para o final do disco;
   3. Clique em `Redimensionar/Mover` ou `Resize/Move` para confirmar a mudança.
      1. Caso neste momento lhe mostre um aviso, basta confirmar/ignorar.
8. Expanda a partição de interesse
   1. Selecione a partição que deseja expandir, e clique em `Redimensionar/Mover` ou `Resize/Move`.
   2. Na parte superior da janela, arraste a borda da partição para ocupar o espaço não alocado.
   3. Clique em `Redimensionar/Mover` ou `Resize/Move` para confirmar a mudança.
9. Após realizar as mudanças, clique no botão `Aplicar` ou `Apply` para aplicar as alterações.
10. Aguarde o processo ser concluído e, em seguida, reinicie a máquina virtual normalmente.
    1.  Lembre-se de remover a imagem ISO do GParted Live para que a máquina virtual inicie a partir do disco rígido.