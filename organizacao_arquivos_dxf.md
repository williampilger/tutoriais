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
| **Código** | **Função** |
| ---------- | ---------- |
| 0 | Tipo de entidade |
| 10, 20 e 30 | Coordenadas X, Y e Z do primeiro ponto, respectivamente (Valor Float) |
| 11, 21 e 22 | Coordenadas X, Y e Z do segundo ponto, respectivamente (Valor Float) |
| 60 | Visibilidade da entidade: 0 - Visível / 1 - Invisível|
| 62 | Cor da linha: 0 indica ByBlock / 256 indica ByLayer / Negativo indica layer inativa |



## Outras referências
- [AutoCAD 2012 DXF Reference.pdf](https://images.autodesk.com/adsk/files/autocad_2012_pdf_dxf-reference_enu.pdf)
- [Wikipedia - AutoCAD DXF](https://en.wikipedia.org/wiki/AutoCAD_DXF)
- 
