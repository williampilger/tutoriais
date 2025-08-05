# Windows não inicia mais após alterar as configurações de Isolamento de Núcleo

Encontrei [este tópico no fórum da microsoft](https://learn.microsoft.com/pt-br/answers/questions/3170612/o-meu-computador-n-o-inicia-ap-s-ativar-a-op-o-de?forum=windows-all&referrer=answers) que cita algo parecido.
É possível alterar a configuração pelo terminal.

*Um dos comandos para voltar as configurações de isolamento de núcleo para o padrão é:*
> bcdedit /set hypervisorlaunchtype auto

Importante também, lembrar de ativar a opção `VT-x` ou `AMD-V` na BIOS.



```
⚠️ Avisos Interessantes

- Não é possível alterar as configurações de segurança do windows no modo de segurança (iniciando o windows no modo de segurança)
- No meu caso, o PC travava totalmente (nem invertia mais nunlock) já durante a inicialização, e às vezes atrasava um pouco, e durava até logar o usuário e começar a trabalhar.
```
