# Criando e lendo arquivos DXF

Este pequeno tutorial explica **uma pequena parte** dos codigos e a estrutura organizacional dos arquivos DXF.
Todo o conteúdo é baseado na documentação fornecida pela **AutoDesk**, referente ao **AutoCAD DXF Files**, e pode ser consultada na íntegra abaixo:

[AutoCAD 2012 DXF Reference.pdf](https://images.autodesk.com/adsk/files/autocad_2012_pdf_dxf-reference_enu.pdf)

## O formato DXF

Esta formatação de arquivo foi criada pela AutoDesk, com o intuito de salvar os dados de desenhos de modo que seja fácil interpretar e manipular seus arquivos fora do AutoCAD.

A estrutura dos dados é bastante simples: Uma linha sempre contem um código de identificação para o conteúdo da linha seguinte. E o arquivo é separado em seções, sendo elas:

- **HEADER** : Informações gerais sobre o desenho;
- **CLASSES** : Informações sobre a formação das classes BLOCKS, ENTITIES, e OBJECTS;
- **TABLES** : Definições sobre itens nomeados, como por exemplo:
  - Application ID (APPID) table;
  -   
- **BLOCKS**
- **ENTITIES**
- **OBJECTS**
- **THUMBNAILIMAGE**




## Outras referências
- [Wikipedia - AutoCAD DXF](https://en.wikipedia.org/wiki/AutoCAD_DXF)
- 
