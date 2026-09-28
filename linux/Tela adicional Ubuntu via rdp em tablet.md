# Criar tela adicional em um Tablet - Nativamente no Ubuntu

> **Atenção**: *Eu, no meu caso de uso*, uso o acesso remoto do Ubuntu para acesso via RDP,
> e preciso, portanto, que este uso **não interfira no acesso remoto "padrão".**.
>
> No meu caso de uso:
>   - Porta 3389: RDP para acesso remoto com seção completamente remota
>   - Porta 3390: RDP (like VNC) que dá acesso à mesma seção do acesso físico à estação.
>
> Este tutorial **muda o comportamento do acesso à seção física do RDP**.


O `Ubuntu 25.04 LTS` tem "dois" acessos remotos nativos:
 - **Compartilhamento de área de trabalho** -> Porta `3390` -> Seção física.
   - é esse aqui que vamos alterar para `extend`
 - **Sessão remota** -> Porta `3389` -> RDP convencional, que possui uma sessão separada para o acesso remoto (melhor para trabalho remoto).
   - continua exatamente como está.


## Configurando

```bash
gsettings set org.gnome.desktop.remote-desktop.rdp screen-share-mode 'extend'
```

*Reverter para o default:*
```bash
gsettings set org.gnome.desktop.remote-desktop.rdp screen-share-mode 'mirror-primary'
```
