*Conteúdo reorganizado pelo Gemini*

---

# > React Hooks

## Para que criar um Hook?

Imagine que você tem a lógica de "verificar se o usuário está online" em três telas diferentes. Em vez de copiar e colar o `useEffect` e o `useState` em todo lugar, você cria um **Custom Hook**.

Os principais motivos são:

* **Reutilização:** Extrair lógica complexa para que possa ser usada em qualquer componente.
* **Limpeza (Clean Code):** O componente foca apenas na interface (o que mostrar), enquanto o Hook cuida do comportamento (como funciona).
* **Testabilidade:** É muito mais fácil testar uma função lógica isolada do que um componente visual inteiro.
* **Composição:** Você pode combinar vários Hooks básicos (como `useState` e `useEffect`) para criar uma funcionalidade nova e robusta.

---

## Como criar um Custom Hook

A regra de ouro é: **O nome deve começar com "use"** (ex: `useAuth`, `useFetch`). Isso avisa ao React que as regras dos Hooks se aplicam ali.

### Exemplo Prático: `useCounter`

Vamos criar um hook simples para gerenciar um contador com limites.

```javascript
import { useState } from 'react';

// 1. Defina a função começando com "use"
function useCounter(initialValue = 0, step = 1) {
  const [count, setCount] = useState(initialValue);

  const increment = () => setCount((prev) => prev + step);
  const decrement = () => setCount((prev) => prev - step);
  const reset = () => setCount(initialValue);

  // 2. Retorne o que o componente vai precisar
  return { count, increment, decrement, reset };
}

export default useCounter;
```

### Como usar no componente:

```javascript
import useCounter from './hooks/useCounter';

function ContadorDeCliques() {
  // Chamando nosso hook customizado
  const { count, increment, reset } = useCounter(10, 5);

  return (
    <div>
      <p>Valor atual: {count}</p>
      <button onClick={increment}>Aumentar</button>
      <button onClick={reset}>Resetar</button>
    </div>
  );
}
```

---

## Regras Importantes

Para que seus Hooks funcionem sem quebrar o React, siga estas diretrizes:

| Regra | Descrição |
| :--- | :--- |
| **Apenas no Topo** | Não chame Hooks dentro de loops, condições (`if`) ou funções aninhadas. |
| **Apenas em Funções** | Chame Hooks apenas em componentes funcionais ou em outros Custom Hooks. |
| **Nomeclatura "use"** | O prefixo `use` é obrigatório para que o linter do React identifique violações de regras. |

### Quando "extrair" um Hook?
Uma boa dica é: se o seu componente passou de 50 linhas de lógica de estado antes de chegar no `return`, provavelmente existe um Custom Hook pedindo para nascer ali.


------


# > React Context API

Se os Hooks servem para reutilizar **lógica**, o Context serve para compartilhar **dados** entre muitos componentes sem precisar passar "props" de pai para filho manualmente (o famoso *prop drilling*).

---

## Para que criar um Context?

O Context é ideal para dados que são "globais" no seu app, como:
* **Tema** (Dark/Light mode).
* **Autenticação** (Dados do usuário logado).
* **Carrinho de compras** em um e-commerce.
* **Preferências de idioma**.

---

## Como criar um Context (Passo a Passo)

Para criar um contexto, você geralmente segue três etapas: Criar, Prover e Consumir.

### 1. Criar o Contexto
Use a função `createContext`.

```javascript
import { createContext, useState } from 'react';

// Criamos o contexto propriamente dito
export const ThemeContext = createContext();

// Criamos um "Provider" para envolver a aplicação
export function ThemeProvider({ children }) {
  const [theme, setTheme] = useState('light');

  const toggleTheme = () => {
    setTheme((current) => (current === 'light' ? 'dark' : 'light'));
  };

  return (
    <ThemeContext.Provider value={{ theme, toggleTheme }}>
      {children}
    </ThemeContext.Provider>
  );
}
```

### 2. Prover o Contexto
No seu arquivo principal (como o `App.js`), você envolve os componentes que precisam dos dados.

```javascript
import { ThemeProvider } from './ThemeContext';
import Home from './Home';

function App() {
  return (
    <ThemeProvider>
      <Home />
    </ThemeProvider>
  );
}
```

### 3. Consumir o Contexto (Usando o Hook `useContext`)
Agora, qualquer componente dentro do `ThemeProvider` pode acessar os dados diretamente.

```javascript
import { useContext } from 'react';
import { ThemeContext } from './ThemeContext';

function BotaoTema() {
  const { theme, toggleTheme } = useContext(ThemeContext);

  return (
    <button onClick={toggleTheme}>
      Mudar para o modo {theme === 'light' ? 'Escuro' : 'Claro'}
    </button>
  );
}
```
