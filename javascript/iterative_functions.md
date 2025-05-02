## 📌 **Síncronos vs Assíncronos**

Diferenças entre os laços de repetição:

* `for`
* `while`
* `forEach`
* `for (const item of array)`
* `map`


---


### ✅ Quando **`await` funciona** corretamente:

```ts
for (const item of array) {
  await asyncFunc(item); // funciona
}

for (let i = 0; i < array.length; i++) {
  await asyncFunc(array[i]); // funciona
}

while (condição) {
  await algumaCoisa(); // funciona
}
```

---

### ❌ Quando `await` **NÃO FUNCIONA** corretamente:

```ts
array.forEach(async item => {
  await asyncFunc(item); // NÃO ESPERA — executa tudo "ao mesmo tempo"
});

array.map(async item => {
  await asyncFunc(item); // também NÃO espera — cria um array de Promises
});
```

---

## ⚙️ Diferenças COMPUTACIONAIS

| Método           | Controle de fluxo? | Performance | Paralelismo           | Pode usar `await`?  |
| ---------------- | ------------------ | ----------- | --------------------- | ------------------- |
| `for` / `while`  | Máximo             | Mais rápido | Sequencial            | ✅ Sim               |
| `for (const of)` | Boa                | Razoável    | Sequencial            | ✅ Sim               |
| `forEach`        | Menor controle     | Mais lento  | Paralelo (em `async`) | ❌ Não               |
| `map`            | Gera array         | Rápido      | Paralelo (em `async`) | ❌ Não (sem `await`) |

---

## 🔍 Considerações práticas:

* Use `for`, `while`, ou `for..of` **quando precisa de `await` com controle sequencial**.
* Use `Promise.all(array.map(...))` **quando quer paralelismo com `async`**.
* Evite `forEach(async)` se precisa que algo espere de fato — ele **ignora o `await`** internamente.

---


## Sobre

Conteúdo sintetizado pelo *ChatGPT 4o* em *2025-05-02*.

- 1. MDN Web Docs – `for await...of`
  > “A declaração `for await...of` cria um loop iterando sobre objetos iteráveis assíncronos, bem como iteráveis síncronos.”  
  🔗 [https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Statements/for-await...of](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Statements/for-await...of)
- 2. Stack Overflow – Uso de `async/await` com `forEach`
  > “A principal questão é que `forEach` não espera por promessas. Isso significa que o loop não aguardará a conclusão das operações assíncronas.”  
  🔗 [https://stackoverflow.com/questions/37576685/using-async-await-with-a-foreach-loop](https://stackoverflow.com/questions/37576685/using-async-await-with-a-foreach-loop)
- 3. Medium – Diferença entre `for` e `forEach` com `async/await`
  > “Usar `async/await` com um loop `for` permite que cada iteração aguarde a resolução da operação assíncrona anterior antes de prosseguir para a próxima.”  
  🔗 [https://medium.com/@potatoscript/exploring-the-difference-between-using-async-await-in-a-for-loop-and-foreach-739c9ebeb64a](https://medium.com/@potatoscript/exploring-the-difference-between-using-async-await-in-a-for-loop-and-foreach-739c9ebeb64a)
- 4. freeCodeCamp – `async/await` em Loops
  > “Se você usar `await` em um `map`, ele sempre retornará um array de promessas. Para obter os resultados, você precisa usar `await Promise.all(...)`.”  
  🔗 [https://www.freecodecamp.org/news/javascript-async-and-await-in-loops-30ecc5fb3939/](https://www.freecodecamp.org/news/javascript-async-and-await-in-loops-30ecc5fb3939/)
- 5. GeeksforGeeks – `async/await` com `forEach`
  > “Usar `async/await` com `forEach` pode ser complicado, pois `forEach` não suporta operações assíncronas de forma nativa.”  
  🔗 [https://www.geeksforgeeks.org/how-to-use-async-await-with-foreach-loop-in-javascript/](https://www.geeksforgeeks.org/how-to-use-async-await-with-foreach-loop-in-javascript/)
