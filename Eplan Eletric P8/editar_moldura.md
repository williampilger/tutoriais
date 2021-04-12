# Editando Molduras no EPLAN Eletric P8

Geralmente os projetos utilizam mais de uma única moldura, pois para cada tipo de página outro modelo pode ser necessário.

*******
Neste tópico veremos:
 1. [Abrindo e editando uma moldura?](#editarmoldura)
 2. [Inserindo e editando textos dinâmicos](#textosdinamicos)
 3. [Alterando o tamanho e quantidade de linhas e colunas da página](#caminhos)
 4. [Configurando o tipo de numeração dos caminhos](#numeracaocaminhos)
 5. [Configurando tamanho e formado da página](#formatopagina)

*******

<div id='editarmoldura'/>  

## Abrindo, editando e salvando uma moldura

Para editar uma moldura, navegue até: `Utilitários -> Dados Mestre -> Moldura -> Abrir...`

Escolha a moldura que deseja editar. Caso queira criar uma nova, crie nesse momento uma cópia de um dos modelos disponíveis.

Obs.: O diretório padrão das molduras é `%eplan%\Data\%nome_empresa%\molduras`

Após aberta, você já pode alterar a moldura. Perceba que as linhas todas são desenhos soltos, e os desenhos e formas são facilmente alterados como se estivesse editando uma página normal de esquema.

Para que as alterações sejam aplicadas, é preciso **fechar** a moldura. Isso vale para todos os tipos de formulários do EPLAN. Para fecha-lo, clique com o botão direito do mouse sobre a moldura, no navegador de páginas, e em seguida em **fechar**.

Caso precise editar propriedades e dados específicos, veja os tópicos abaixo.


<div id='textosdinamicos'/> 

## Inserindo e editando textos dinâmicos

Ao abrir uma moldura, verá que ela contém campos de texto especiais, e dinâminos. Ou seja, textos que vão mudar de página para página, como por exemplo, o contador de páginas, a descrição, os números e letras das linhas e colunas, e muito mais.

Para **Inserir** uma nova propriedade ou texto dinâmido à moldura navegue até `Inserir -> Texto Especial` e escolha o tipo de texto que deseja inserir.

Para **Editar** as caixas de texto basta dar dois cliques sobre elas. Ao editar as propriedades dos textos especiais, poderá navegar por duas guias:
 - **Posicionamento**: Escolha a propriedade do projeto, página, linha ou coluna que deseja que seja exibida.
 - **Formato**: Personalizar a exibição do texto em sí. Funciona da mesma forma como as propriedades de um texto simples, onde você altera a centralização, espaçamento, quebras de linha, cor e tamanho.


<div id='caminhos'/> 

## Alterando o tamanho e quantidade de linhas e colunas da página

Primeiramente, para que possa ver onde estão os atuais caminhos da página, ative a exibição dos caminhos em `Visualização -> Caminhos`.
Se a moldura contiver as mascações e numerações de linhas e colunas na lateral, neste momento as marcações precisam estar coincidindo. Caso isso não esteja acontecendo, algo está errado.

o **Número de linhas e colunas, e suas medidas** devem ser preenchidas nas propriedades da moldura. Para edita-las, clique com o botão direito do mouse sobre a moldura, no navegador de páginas, e escolha **Propriedades**. As propriedades **Quantidade de linhas** e **Quantidade de colunas** devem estar visíveis e preenchidas, mas caso contrário, clique no botão **Novo** e busque pelas pripriedades. O mesmo vale para as propriedades de **Altura de linhas[X]** e **Altura de colunas[X]**.

Importante notar que ao preencher as medidas das primeiras e últimas linhas e colunas, deve-se levar em consideração o tamanho da márgem que foi deixada no desenho da moldura.
Para saber se a configuração está correta, basta ativar a visibilidade dos caminhos e ver se estão coincidindo com as marcações da moldura.


<div id='numeracaocaminhos'/> 

## Configurando o tipo de numeração dos caminhos

Nas pripriedades da moldura, encontre as propriedades:
- **Formato de numeração das colunas** e **Formato de numeração das linhas**, elas definem se a numeração deve ser numérica ou alfanumérica.
- **Numeração de colunas invertiva** e **Numeração de linhas invertida**, quando marcadas, invertem a numeração em questão.
- **quantidade de caracteres por coluna / linha** define quantos caracteres irão compor as numerações.

<div id='formatopagina'/> 

## Configurando tamanho e formado da página

Encontre as propriedades da moldura:
- **Alinhamento da página / Formato do papel**: Define formato retrato ou paisagem da exibição. (A impressão será baseada nisso)
- **Grid**: Por padrão, em *1mm*, e aconselho que permaneça assim.

