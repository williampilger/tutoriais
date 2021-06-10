# Criando e lendo arquivos DXF

Este pequeno tutorial explica **uma pequena parte** dos codigos e a estrutura organizacional dos arquivos DXF.
Todo o conteúdo é baseado na documentação fornecida pela **AutoDesk**, referente ao **AutoCAD DXF Files**, e pode ser consultada na íntegra abaixo:

[AutoCAD 2012 DXF Reference.pdf](https://images.autodesk.com/adsk/files/autocad_2012_pdf_dxf-reference_enu.pdf)

## O formato DXF

Esta formatação de arquivo foi criada pela AutoDesk, com o intuito de salvar os dados de desenhos de modo que seja fácil interpretar e manipular seus arquivos fora do AutoCAD.

A estrutura dos dados é bastante simples: Uma linha sempre contem um código de identificação para o conteúdo da linha seguinte. E o arquivo é separado em seções, sendo elas:

- **HEADER** : Informações gerais sobre o desenho
- **CLASSES** : Informações sobre a formação das classes BLOCKS, ENTITIES, e OBJECTS
- **TABLES** : Definições sobre itens nomeados, como por exemplo:
  - Application ID (APPID)
  - Configurações do registro de blocos/grupos (BLOCK_RECORD)
  - Estilos de cotas (DIMSTYLE)
  - Layers (LAYER)
  - Tipos de linha (LTYPE)
  - Estilo de texto (STYLE)
  - Sistema de coordenadas do usuário (UCS)
  - Visualização (VIEW)
  - Confirguação de Viewports (VPORT)
- **BLOCKS** : Contém o registro dos blocos, agrupamentos de entidades
- **ENTITIES** : Esta seção armazena os dados de todas as entidades (linhas, retangulos, circulos...)
- **OBJECTS** : Usado por aplicativos AutoLISP e ObjectARX, contendo dados de objetos não-gráficos
- **THUMBNAILIMAGE** : Contém uma prévia do arquivo DXF
- **END OF FILE** : Marcação do final do arquivo (opcional)

Os dados podem ser escritos em ordem completamente aleatória, então aconselho os desenvolvedores de ferramentas a não se basearem na sequência especificada pelo manual, pois ela pode (e vai) variar de acordo com os softwares utilizados na exportação.

Outra observação interessante, é criar lógicas para ignorar códicos de grupo desconhecidos até o momento, pois a cada lançamento da Autodesk são acrescentados novos códigos, para novas funções da aplicação em questão, mas a base, será sempre a mesma, e os dados dos codigos de grupo já existentes não irão mudar (ao menos de acordo com o política atual).

# Seção ENTITIES

Esta é a seção mais importante do arquivo, pois apenas com ela já é possível desenhar a figura completamente.
os codigos mais utilizados são:

**GERAIS**

| **Código** | **Função** |
| ---------- | ---------- |
| 0 | Tipo de entidade (LINE, ARC, CIRCLE, etc.)|
| 6 | Nome do tipo da linha (presente somente se não for *ByLayer*) |
| 8 | Nome da Layer |
| 10, 20 e 30 | Coordenadas X, Y e Z do primeiro ponto, respectivamente (Valor Float) |
| 11, 21 e 31 | Coordenadas X, Y e Z do segundo ponto, respectivamente (Valor Float) |
| 12, 22 e 32 | Coordenadas X, Y e Z do terceiro ponto, respectivamente (Valor Float) |
| 60 | Visibilidade da entidade: 0 - Visível / 1 - Invisível |
| 62 | Cor da linha: 0 indica ByBlock / 256 indica ByLayer / Negativo indica layer inativa |
| 67 | Espaço da entidade (opcional): Ausente ou zero indica em *Model* / 1 indica *In paper* |

**ARC** e **CIRCLE** - Arcos e Circulos

| **Código** | **Função** |
| ---------- | ---------- |
| 39 | Espessura da linha (opcional): Padrão = 0 |
| 100 | Marcador de subclasse (AcDbCircle) |
| 10, 20 e 30 | Coordenadas X, Y e Z do ponto central, respectivamente (Valor Float) |
| 40 | Raio do arco (Valor Float) |
| 100 | Marcador de subclasse (AcDbArc) - **Usado somente no ARCO**|
| 50 | Ângulo inicial (Float) |
| 51 | Ângulo final (Float) |

**ELLIPSE** - Elipse

| **Código** | **Função** |
| ---------- | ---------- |
| 100 | Marcador de subclasse (AcDbEllipse) |
| 10, 20 e 30 | Coordenadas X, Y e Z do ponto central, respectivamente (float) |
| 11, 21 e 31 | Coordenadas X, Y e Z do ponto final do maior ângulo, em relação ao centro (float) |
| 40 | Raio menor ângulo do arco (float) |
| 41 | Parâmetro inicial (0 para uma elipse completa) |
| 42 | Parâmetro final (2pi para uma elipse completa) |

**HATCH** - Hachurras

| **Código** | **Função** |
| ---------- | ---------- |
| 100 | Marcador de subclasse (AcDbHatch) |
| 2 | Nome do padrão de Hachurra |
| 10 e 30 | Coordenadas X e Y do ponto de início da hachurra, respectivamente (float) |
| 70 | Flag de preenchimento sólido: 1 - Preenchimento sólido / 0 - Preencher com padrão / ou Versão do polígono para preenchimento MPolygon |
| 63 | Para *MPolygon*, cor do preenchimento no padrão ACI |
| 71 | Flag de associatividade: 1 - associável / 2 - não-associável). Para *MPolygon* equivale a flag de preenchimento sólido |
| 91 | Número de caminhos de limite (loops aplicados sobre os parâmetros abaixo) |
| 75 | Estilo de hachurra: 0 - Normal / 1 - Hachurra apenas area externa / 2 - Hachurra área completa |
| 76 | Tipo de padrão de hachurra: 0 - Definido pelo usuário / 1 - Predefinido / 2 - Customizado |
| 52 | Ângulo do padrão de hachurra |
| 41 | Escala do padrão de hachurra |
| 77 | Flag padrão duplo de preenchimento: 0 - Simples / 1 - Duplo |
| 78 | Número de linhas do padrão de hachurra (Número de vezes que os padrões definidos abaixo serão repetidos)|
| 47 | Tamanho do pixel usado para determinar a densidade de hachuras criadas com o método Flood de hachura |
| 98 | Número de pontos de início de hachurra |
| 450 | Flag de preenchimento gradiente: 0 - Solido simples / 1 - Preenchimento gradiente |
| 453 | Número de cores: 0 - Solido simples / 1 - Preenchimento gradiente |
| 460 | Ângulo de rotação para o gradiente, em radianos |
| 461 | Grau de deslocamento do centro de gradiente. 0.0 significa que não será deslocado, enquanto que 1.0 significa que apenas o modo de deslocamento deve ser usado. |
| 462 | Valor de matiz de cor usado pelo código de diálogo (padrão = 0, 0; o intervalo é de 0,0 a 1,0) |
| 470 | String (padrão = LINEAR) |

**LINE** - Linhas

| **Código** | **Função** |
| ---------- | ---------- |
| 100 | Marcador de subclasse (AcDbLine) |
| 39 | Espessura da linha, opcional. Padrão = 0 |
| 10, 20 e 30 | Coordenadas X, Y e Z do ponto de início da linha, respectivamente (float) |
| 11, 21 e 31 | Coordenadas X, Y e Z do ponto de fim da linha, respectivamente (float) |



O fim de uma entidade é marcado pelo início da próxima. Estes dados todos podem aparecer em ordem aleatória.

## Gravando uma ENTIDADE no arquivo

Neste exemplo vou criar uma entidade de linha, ou seja, tipo *LINE*, pertencente a *Layer 1* que vai do ponto A(2,3) ao ponto B(14.65,36.54) usamos a seguinte lógica:
```
0
LINE
8
Layer 1
10
2.00
20
3.00
11
14.65
21
36.54
```
É bem fácil perceber como funciona a lógica de *Código de grupo / valor*. Temos o código de grupo, seguido da informação na linha seguinte.



## Outras referências
- [AutoCAD 2012 DXF Reference.pdf](https://images.autodesk.com/adsk/files/autocad_2012_pdf_dxf-reference_enu.pdf)
- [Wikipedia - AutoCAD DXF](https://en.wikipedia.org/wiki/AutoCAD_DXF)
- 
