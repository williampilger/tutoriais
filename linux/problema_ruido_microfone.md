# Solucionar problema de ruido no microfone

Obtido de [diolinux](https://diolinux.com.br/sistemas-operacionais/remover-ruido-do-microfone-no-linux.html).

Veja também [este tutorial mais completo](https://diolinux.com.br/tutoriais/cancelamento-de-eco-e-ruido-no-linux.html).

## Procedimento

Abra o terminal, e:

> sudo nano /etc/pulse/default.pa

Vá até o final do arquivo e adicione os comandos abaixo:

Em **### loading modules and rerouting streams.**

```
load-module module-echo-cancel source_name=noiseless
```

e em **### Make some devices default**

```
set-default-source noiseless 
```

De modo que fique assim:

```
...
### Modules to allow autoloading of filters (such as echo cancellation)
### on demand. module-filter-heuristics tries to determine what filters
### make sense, and module-filter-apply does the heavy-lifting of
### loading modules and rerouting streams.
load-module module-filter-heuristics
load-module module-filter-apply
load-module module-echo-cancel source_name=noiseless

### Make some devices default
#set-default-sink output
#set-default-source input
set-default-source noiseless
```

Salve e feche o arquivo, e execute o comando abaixo:

> pulseaudio -k

Vá até a guia **Som** das **Configurações** da sua distro, e nos dispositivos de entrada verá um microfone com o filtro de ruido.

Obs.: Caso não estejam disponíveis os recursos de audio, inicie o pulseaudio digitando no terminal:

> pulseaudio

# Sobre

By: will.i.am | Bom Princípio - RS
