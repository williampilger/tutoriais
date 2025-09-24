# Listar processos - Como o Linux top

Sem instalar nada, você pode ver os processos com um comando básico:

```ps1
While(1) {  $p = get-counter '\Process(*)\% Processor Time'; cls; $p.CounterSamples | sort -des CookedValue | select -f 15 | ft -a}
```


## Usando o NTop (github.com/gsass1/NTop)

O [repositório oficial](https://www.github.com/gsass1/NTop) contém orientações bem completas.
A aplicação pode ser instalada por lá, ou usando o winget:

```ps1
winget install gsass1.NTop
```

