# Limitar o consumo energético da CPU no Windows

Para definir em `90%`, por exemplo, use:

**Para ajustar o limite no modo AC (na Tomada)**:
```p1
powercfg /setacvalueindex SCHEME_CURRENT SUB_PROCESSOR PROCTHROTTLEMAX 90
powercfg /S SCHEME_CURRENT
```

ou

**Para ajustar o limite no modo DC (na Bateria)**:
```p1
powercfg /setdcvalueindex SCHEME_CURRENT SUB_PROCESSOR PROCTHROTTLEMAX 90
powercfg /S SCHEME_CURRENT
```

