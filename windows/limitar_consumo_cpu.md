# Limitar o consumo energético da CPU no Windows

Para definir em `90%`, por exemplo, use:

**Para ajustar o limite no modo AC (na Tomada)**:
> powercfg /setacvalueindex SCHEME_CURRENT SUB_PROCESSOR PROCTHROTTLEMAX 90

ou

**Para ajustar o limite no modo DC (na Bateria)**:
> powercfg /setdcvalueindex SCHEME_CURRENT SUB_PROCESSOR PROCTHROTTLEMAX 90

e **APLIQUE A CONFIGURAÇÂO USANDO:**
> powercfg /S SCHEME_CURRENT

