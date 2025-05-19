# Alterando configurações da Dock do Gnome pelo terminal


### Comando para inverter o estado do "auto-ocultar" dock

```sh
gsettings set org.gnome.shell.extensions.dash-to-dock dock-fixed "$([ "$(gsettings get org.gnome.shell.extensions.dash-to-dock dock-fixed)" = "true" ] && echo false || echo true)"
```

*Você pode criar um script com este conteúdo, e executar o comando em um atalho de teclado, se for conveniente.* 
