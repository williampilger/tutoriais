# Manipulando layers do EPLAN Eletric P8

As layers servem para diferenciar graficamente linhas, formas e símbolos.
Podemos configurar as layers de todos os gráficos no eplan, dentre elas, as formas, simbolos, textos, conexões, caixas de dispositivos e pontos de conexão.

Neste momento, estou utilizando a versão `2.9 SP1 Update 5` do Eplan, estas configurações podem variar para outras versões.

*******
Neste tópico veremos:
 1. [Abrindo configurações de layers](#ponto1)
 2. [Alterando as propriedades de uma layer específica](#ponto2)
 3. [Alguns exemplos de propriedades](#ponto3)

*******


<div id='ponto1'/>

## Abrindo configurações de layers

Navegue até `Dados do projeto -> Gerenciamento de Layers`, e então já poderá ver a tabela das configurações das layers na parte inferior da tela.

<div id='ponto2'/>

## Alterando as propriedades de uma layer específica

Caso você queira alterar as pripriedades de um layer específico, você pode abrir as propriedades da conexão/objeto/dispositivo que deseja atingir, e verificar em qual das layers ele está representado. Na maior parte dos casos, esta propriedade fica na guia **Exibição**, **Formato**, ou **Diagrama de conexão**.
Tendo o nome da layer, você já pode localiza-lá no gerenciador de layer.

Repare que as layer são organizadas em grupos:
- **Gráfico**: Que representa as formas gráficas, como linhas, retângulos, circulos, etc.
- **Gráfico de símbolos**: Formada pelas layers que são usadas no momento da criação de simbolos (inclusive os das bibliotecas padrões de simbolos);
- **Posicionamento de propriedades**: Compreende as layer responsáveis por representar os textos de propriedades que são exibidos ao lado ou dentro dos dispositivos, por exemplo;
- **Textos especiais**: Textos especiais, exibidos nos relatórios, molduras e formulários;
- **Gráfico 3D**: Utilizado em projetos do Pro Pannel;
- **Importar DXF / DWG**: Layers que serão aplicados aos gráficos importados de projetos CAD convencionais.

Como agora você já sabe o grupo, e o nome da layer do conjunto de objetos que você deseja alterar, busque pela layer, e faça as alterações desejadas. Basta clicar fora do gerenciador de layers, ou fecha-lo, para que as alterações passem a fazer efeito.

<div id='ponto3'/>

## Alguns exemplos de propriedades para alterar

- **Imprimir**: Caso queira que uma layer apareça durante a edição do esquema, mas não no momento da impressão, basta que se desmarque a coluna *Imprimir*;
- **Visível**: Caso a layer deva aparecer somente quando ativada a opção *exibir ocultos*, desmarque esta opção;
- **plano de fundo**: Quando marcado, torna a layer parte do plano de fundo da página, e ineditável;
- **Bloqueado**: Não será mais possível editar itens nessa layer;
- **Espeçura da linha**, **Cor**, **Tipo de linha** e **Tabanho da fonte**: Afetam todos os componentes na respectiva layer;
