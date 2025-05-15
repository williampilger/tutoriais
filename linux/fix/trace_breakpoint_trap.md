# Trace/breakpoint trap (imagem do núcleo gravada)

Exemplo do problema ocorrido:

```bash
wilger@MICRO-08:~$ authentypasswords
LaunchProcess: failed to execvp:
/opt/Authenty
Trace/breakpoint trap (imagem do núcleo gravada)
```


## Solução | <small>`✅ Testado`</small>

```
sudo sysctl -w kernel.apparmor_restrict_unprivileged_userns=0
kernel.apparmor_restrict_unprivileged_userns = 0
```

**Fonte:** [Drata Agent not Working in Ubuntu 24.04](https://github.com/drata/drata-agent/issues/20#issuecomment-2094848078);
