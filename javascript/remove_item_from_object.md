# Removendo itens de Um ou vários objetos em Js/Ts

*Um único item*
```ts
result = {
  field1: 'valie1',
  field2: 'valie2',
  remove: 'value to be removed',
  field3: 'valie3',
  field4: 'valie4'
};
const {removedField, ...cleanedResult} = result;
console.log(cleanedResult);
```

*Um array de objetos*
```ts
result = [
  {field1: 'valie1',field2: 'valie2',remove: 'value to be removed',field3: 'valie3',field4: 'valie4'},
  {field1: 'valie1',field2: 'valie2',remove: 'value to be removed',field3: 'valie3',field4: 'valie4'},
  {field1: 'valie1',field2: 'valie2',remove: 'value to be removed',field3: 'valie3',field4: 'valie4'}
];
const cleanedResult = result.map(({ removedField, ...rest }) => rest);
console.log(cleanedResult);
```
