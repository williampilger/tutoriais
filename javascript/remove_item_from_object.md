# Removendo itens de Um ou vários objetos em Js/Ts

*Um único item*
```ts
const {removedField, ...filteredObject} = originalObject;
```

*Um array de objetos*
```ts
const cleanedResult = result.map(({ Status, ...rest }) => rest);
```
