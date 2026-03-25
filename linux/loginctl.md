# Gerenciador de Login do Linux (`loginctl`)

**Importante:** Nos exemplos, estou usando um `Ubuntu 25.04`, em `Março de 2026`.

O `loginctl` faz parte do `systemd`, e serve para gerenciar as seções ativas dos usuários.

> **Atenção**: Ao listar os usuários/seções ativos, você verá seu próprio acesso também, mesmo que SSH, por exemplo.
> **Então, ao encerrar os acessos, tenha o cuidado de não encerrar sua própria seção sem querer.**

## Listar as seções ativas

```bash
loginctl list-sessions
```

Você verá algo como:
```txt
SESSION  UID USER   SEAT  LEADER CLASS         TTY                   IDLE SINCE    
      1  119 gdm    -     4230   manager-early -                     no   -        
     10 1000 wilger -     21042  user          -                     no   -        
      4 1000 wilger -     8095   manager       -                     no   -        
     c1  119 gdm    seat0 4192   greeter       tty1                  yes  26min ago
     c6 1000 wilger -     19607  user          chrome-remote-desktop no   -        
```

## Encerrar todas as seções de um usuário

```bash
sudo loginctl terminate-user wilger
```

## Encerrar todas as seções, de todos os usuários

```bash
sudo loginctl kill-user "*"
```


## Reiniciar o Display Manager SEM encerrar as seções

Este **não é um comando do `systemctl`**.
Isso serve pra fazer todas as seções gráficas voltarem para a tela de login.

```bash
# Ubuntu
sudo systemctl restart gdm
# Xubuntu ou Lubuntu
sudo systemctl restart lightdm
# Kubuntu
sudo systemctl restart gdm
```
