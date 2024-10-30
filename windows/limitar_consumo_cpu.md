# Limitar o consumo energético da CPU no Windows

## Via Interface Gráfica

- Acesse `Configurações`>`Sistema` > `Energia e Suspensão` > `Configurações adicionais de energia`;
- Clique em `Alterar configurações do plano` para o plano ativo e, em seguida, em `Alterar configurações avançadas de energia`;
- Expanda a opção `Gerenciamento de energia do processador` e ajuste o `Estado máximo do processador` para um valor abaixo de 100%. Isso limita a velocidade da CPU, reduzindo o consumo.


## Via Linha de Comando

Para definir em `90%`, por exemplo, use:

**Para ajustar o limite no modo AC (na Tomada)**:
```ps1
powercfg /setacvalueindex SCHEME_CURRENT SUB_PROCESSOR PROCTHROTTLEMAX 90
powercfg /S SCHEME_CURRENT
```

ou

**Para ajustar o limite no modo DC (na Bateria)**:
```ps1
powercfg /setdcvalueindex SCHEME_CURRENT SUB_PROCESSOR PROCTHROTTLEMAX 90
powercfg /S SCHEME_CURRENT
```
