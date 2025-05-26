# Trace/breakpoint trap (imagem do núcleo gravada)

Exemplo do problema ocorrido:

```bash
wilger@MICRO-08:~$ authentypasswords
LaunchProcess: failed to execvp:
/opt/Authenty
Trace/breakpoint trap (imagem do núcleo gravada)
```

---



## Solução - Temporária (até o reinício)

<small style="font-size:8px;">`✅ Testado`</small>

```
sudo sysctl -w kernel.apparmor_restrict_unprivileged_userns=0
```

*Isso desativa a restrição de criação de namespaces do Linux. Pode representar riscos, mas em computadores pessoais, usados por alguém com certa experiência, é relativamente seguro. Não indicado para servidores e/ou máquinas com acesso SSH habilitado, por exemplo.*


## Solução Definitiva (aplicar ao sistema)

Edite o arquivo de configuração:

> sudo nano /etc/sysctl.d/99-userns.conf

e, adicione a linha abaixo:

```sh
kernel.apparmor_restrict_unprivileged_userns = 0
```

Para aplicar imediatamente (opcional, a menos que tenha preça e não tenha rodado a solução temporária)

> sudo sysctl --system



--- 


## Fontes

- [Drata Agent not Working in Ubuntu 24.04](https://github.com/drata/drata-agent/issues/20#issuecomment-2094848078);
- Casos em que isso é uma vulnerabilidade (exemplo):
  - [CVE-2021-3493](https://nvd.nist.gov/vuln/detail/CVE-2021-3493);
  - [CVE-2016-8655](https://nvd.nist.gov/vuln/detail/CVE-2016-8655);
