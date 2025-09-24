# Listar processos - Como o Linux top

Sem instalar nada, você pode ver os processos com um comando básico:

```ps1
While(1) {  $p = get-counter '\Process(*)\% Processor Time'; cls; $p.CounterSamples | sort -des CookedValue | select -f 15 | ft -a}
```

