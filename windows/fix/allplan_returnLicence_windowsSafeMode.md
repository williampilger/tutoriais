# Retornar a licença do Allplan em casos de perda de acesso ao Windows (Usando o modo de segurança)

```
⚠️ Para este procedimento, você ainda precisa ter acesso ao modo de segurança do Windows
```

Inicializando pelo modo de segurança **com Rede**, é possível retornar a licença.
No entanto, o *Allmenu* precisa do *Codemeter* para funcionar, serviço que não está disponível (por padrão) no modo de segurança.

---

## PASSO 1: Ativando o `Codemeter.exe` no modo de segurança

1. Inicialize o Windows no modo de segurança (qualquer dos modos);
2. Abra o Editor do Registro:
  3.1. Pressione `Windows` + `R`;
  3.2. Digite `regedit`;
  3.3. Pressione `Enter`, ou clique em `Executar`;
3. Navegue até `HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\SafeBoot\Network\`;
4. Clique com o botão direito na pasta `Network` e selecione **Novo** > **Chave**;
5. Renomeie esta nova pasta como `CodeMeter.exe`;
6. Clique na chave que você acabou de criar. No painel direito, dê um duplo clique no valor `(Padrão)`;
7. Na pequena janela que aparece, digite a palavra `Service` e clique em **OK**;


## PASSO 2: Reiniciar e retornar a licença

Agora, com o `CodeMeter` habilitado no `modo de segurança com rede`, basta reiniciar a máquina (obviamente neste modo), abrir o `Allmenu` e retornar a licença normalmente.

---

# About

By: **William Pilger**

2025-08-06 10:44 | Bom Princípio - RS
