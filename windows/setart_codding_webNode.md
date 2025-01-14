# Começando a Programar no Windows

Este tutorial orienta o início básico para quem quer começar a trabalhar com **Programação WEB com Node e Typescript** no **Windows**.

*Quero deixar registrado também que esse tutorial foi criado para iniciantes, portanto, usa interfaces gráficas que futuramente poderão (e deverão) ser substituídas por ferramentas de terminal ou outras mais avançadas e completas.*

## Criando uma conta no Github

Se você ainda não possui, crie uma conta no [Github](https://github.com) (plataforma na qual você está vendo este tutorial).


---------------------------------------

## Instalação das Ferramentas Básicas

- **Visual Studio Code**
  - *Dica:* Instale a versão de sistema. A versão de usuário funciona, mas é limitada.
  - Você pode fazer o download do [Instalador x64 Sistema](https://code.visualstudio.com/docs/?dv=win64);
  - Ou, escolher a opção preferida no [site oficial](https://code.visualstudio.com);
  - *OPCIONAL* - Ao concluir a instalação do VSCode e abri-lo pela primeira vez, faça login na sua conta do github, para que seuas configurações sejam sincronizadas, e que não seja necessária uma nova configuração na proxima instalação.
    - Na parte inferior esquerda da tela, você verá um menu de `Contas`, clique sobre ele, e selecione `Ativas sincronização de configuração` e então, selecione o github, e confirme o login.
- **GitHub Desktop**
  - Faça o download na [página de download oficial](https://desktop.github.com/download/);
  - Basta executar o instalador, não requer permissão de administrador.
  - Confirme que deseja fazer login, e logue na sua conta do github.
- **NodeJS**
  - Faça o download do instalador no [site oficial](https://nodejs.org/pt), clicando em `Descarregar Node.JS (LTS)`;
  - Execute o instalador, e garanta que seja executado como administrador, e que o diretório de instalação seja algo parecido com `C:\Program Files\nodejs\`;
  - Na tela `Tools for Native Modules`, marque a opção `Automatically install the necessary tools. [...]`;
  - Você pode verificar se a instalação foi concluída com êxito abindo o CMD e digitando `node -v`, você deverá ver a versão do Node instalada. Se esta etapa falhar, você verá um aviso de que o comando não foi encontrado. Se isso acontecer, será necessário verificar se a instalação do Node foi adicionada ao Path do Windows.
- **Node Typescript**
  - Após a instalação do Node concluída e testada, você deve abrir um terminal e instalar o Typescript com o seguinte comando:
  - `npm install -g typescript`

---------------------------------------

## Abrindo meu primeiro repositório

No **Github Desktop** você pode criar e clonar repositórios. Após abri-los, você pode começar a explorar o código.

No passo-a-passo abaixo, você verá como CRIAR um projeto do zero.
No segundo item, explico um pouco sobre como executar a aplicação, ou abrir uma aplicação já existente.


### Estrutura Básica de um Projeto React com Typescript

Após instalar todas as ferramentas básicas, você pode criar um projeto React com Typescript usando o comando `npx create-react-app meu-projeto --template typescript`. Isso criará uma estrutura de diretórios semelhante a esta:

```
meu-projeto/
├── node_modules/
├── public/
│   ├── index.html
│   └── ...
├── src/
│   ├── App.css
│   ├── App.tsx
│   ├── index.css
│   ├── index.tsx
│   ├── react-app-env.d.ts
│   ├── reportWebVitals.ts
│   └── setupTests.ts
├── .gitignore
├── package.json
├── tsconfig.json
└── README.md
```

#### Descrição dos Arquivos e Diretórios

- **node_modules/**: Contém todas as dependências do projeto.
- **public/**: Contém arquivos públicos que não são processados pelo Webpack, como o `index.html`.
- **src/**: Contém o código-fonte do projeto.
  - **App.tsx**: Componente principal do aplicativo.
  - **index.tsx**: Ponto de entrada da aplicação.
  - **react-app-env.d.ts**: Arquivo de definição de tipos para o React.
  - **reportWebVitals.ts**: Arquivo para medir a performance do aplicativo.
  - **setupTests.ts**: Arquivo de configuração para testes.
- **.gitignore**: Arquivo que especifica quais arquivos e diretórios devem ser ignorados pelo Git.
- **package.json**: Contém informações sobre o projeto e suas dependências.
- **tsconfig.json**: Arquivo de configuração do Typescript.
- **README.md**: Arquivo de documentação do projeto.


### Executar um projeto depois de sua criação

Vamos para dois comandos básicos dentro do VSCode:

- `Ctrl` + `J` no teclado abrirão um terminal na parte inferior do VSCode;
- `cd caminho/` entra na pasta "caminho";
- `cd ..` volta um diretório;
- `ls` Comando para listar arquivos e pastas do diretório atual;

Então, abra o terminal e digite:
> cd react-project-name

Obviamente, substituindo o nome `react-project-name` pelo nome do projeto.
Isso, vale para estruturas de pasta no padrão que EU, WILLIAM PILGER, crio meus projetos.
Logo, isso pode ser diferente.

*Mas Will, como faço pra saber a pasta na qual devo entrar então??!*

Fácil, a pasta que contenha o arquivo `package.json` é a pasta na qual o projeto deve ser executado.
Então, no exemplo de criação de dei acima, a pasta correta é a `meu-projeto`.

Você pode conferir se está na pasta correta digitando no terminal:
> ls

Se você vir uma lista de arquivos incluindo o `package.json`, você está no lugar certo. Se não , continue explorando os diretório com o `cd`.

Agora, que já estamos na pasta certa, instale as dependências do seu projetos com:
> npm install

E, por fim, para executar seu projeto, use:
> npm start

*obs: O comando para executar o projeto pode variar, e você pode ter melhores orientações sobre como prosseguir lendo o arquivo Readme.md disponível dentro da mesma pasta.*