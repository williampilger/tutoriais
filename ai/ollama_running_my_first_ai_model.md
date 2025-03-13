# Ollama - Executando meu primeiro modelo de Inteligência artificial


Para rodar rapidamente, sem preparar muito nenhuma infraestrutura para executar um modelo de inteligência artificial, podemos usar o **Ollama**, que faz toda essa "mão" pra nós.

Desvantagem: Mais baixo controle sobre o que está acontecendo.

---

## Instalando o Ollama

Baixe o instalador do [site oficial - ollama.com](https://ollama.com/), e instale a versão adequada para o seu sistema.

Instale o software.

---

## Executando meu primeiro modelo

Depois de tudo instalado, abra o terminal, e digite:

```sh
ollama run nome-do-modelo
```

Se ele existir localmente, será executado, se não, será baixado (se encontrado) e executado.

Funciona exatamente igual o docker.

---

## Alguns modelos conhecidos, para você iniciar

*DeepSeek R1 com 1.5B de Parâmetros* - Extremamente leve, e bem alucinado
> ollama run deepseek-r1:1.5b

*DeepSeek R1 com 7B de Parâmetros* - Relativamente leve, e pouco preciso
> ollama run deepseek-r1:7b

*DeepSeek R1 com 8B de Parâmetros*
> ollama run deepseek-r1:8b

*DeepSeek R1 com 14B de Parâmetros* - Deve ser relativamente pesado
> ollama run deepseek-r1:14b

*DeepSeek R1 com 32B de Parâmetros*
> ollama run deepseek-r1:32b

*DeepSeek R1 com 70B de Parâmetros*
> ollama run deepseek-r1:70b

*DeepSeek R1 completo* - **Isso jamais vai rodar no seu PC, seu animal**
> ollama run deepseek-r1:671b
