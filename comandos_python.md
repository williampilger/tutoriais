# print
Funcionamento básico do comando **print**
Você pode encontrar a documentação completa [aqui](https://docs.python.org/3/library/string.html#formatexamples).

## Print simples
Para realizar um print simples, com as variaveis separadas por espaços use

	>>> nome = "William"
	>>> idade = 23
	>>> print("Eu sou", nome, "e tenho", idade, "anos")
	Eu sou William e tenho 23 anos

## Alterando separador padrão do Print
Para alterar o separador padrão usamos o parâmetro **sep**:

	>>> print("Eu sou", nome, "e tenho", idade, "anos", sep="_")
	Eu_sou_William_e tenho_23_anos

	>>> print("Eu sou", nome, "e tenho", idade, "anos", sep="")
	EusouWilliame tenho23anos

## Usando a interpolação simples de string no Print

	>>> dia = 2
	>>> mes = 12
	>>> ano = 1997
	>>> print("Nasci no dia {}/{}/{}".format(dia, mes, ano))
	Nasci no dia 2/12/1997

## Usando formatadores na interpolação de strings
Existem diversos formatadores utilizáveis, inclusive você pode alterar a ordem em que as variaveis são apresentadas no print.
Para isto basta colocar o índice entro das chaves:

	>>> dia = 2
	>>> mes = 12
	>>> ano = 1997
	>>> print("Nasci no dia {2}/{0}/{1}".format(mes, ano, dia))
	Nasci no dia 02/12/1997
Para deixar o número de caracteres fixo, você pode utilizar o seguinte processo:

	>>> dia = 2
	>>> mes = 12
	>>> ano = 1997
	>>> print("Nasci no dia {:2d}/{:2d}/{:4d}".format(dia, mes, ano))
	Nasci no dia  2/12/1997
Repare que apenas foi inserido um caractere a mais (um espaço a mais). Caso queira que o espaço seja preenchido com zeros, use:

	>>> dia = 2
	>>> mes = 12
	>>> ano = 1997
	>>> print("Nasci no dia {:02d}/{:02d}/{:04d}".format(dia, mes, ano))
	Nasci no dia 02/12/1997

Para formatar valores float utilize o **:f**, como mostrado abaixo

	>>> salario = 1256.36
	>>> print("Meu salário é de {:f} reais")
	Meu salário é de 1256,36000 reais

Para remover os zeros, use **.2** no formatador

	>>> salario = 1256.36> print("Meu salário é de {:.2f} reais")
	Meu salário é de 1256,36 reais

	
Para definir o número TOTAL de digitos (contando junto os após a vírgula), informe a quantidade antes do ponto:

	>>> salario = 1256.36
	>>> print("Meu salário é de {:7.2f} reais")
	Meu salário é de  1256,36 reais
Observe o espaço a mais que ficou, pois o número tem apenas 6 dígitos.

Para substituir os espaços em branco por zeros, basta fazer isto:

	>>> salario = 1256.36
	>>> print("Meu salário é de {:07.2f} reais")
	Meu salário é de  01256,36 reais


# random.random()
A função **random** faz parte da biblioteca random. Logo, para chama-la você precisa incluir ela. Vela a utilização abaixo:

    >>> import random
    >>> numero_aleatorio = random.random()
A função **random** sempre retorna um número entre 0.0 e 1.0


# random.randrange()
A função **randrange(de, ate)** serve para gerar números aleatórios inteiros em um intervalo específico.


# int()
A função **int()** retorna a parte inteira de um número.

# round()
A função **round()** arredonda um float para um valor inteiro.

# Formatadores/Funções de string
Documentação completa [aqui](https://docs.python.org/pt-br/3/library/stdtypes.html#text-sequence-type-str), e [aqui](https://docs.python.org/3.6/library/stdtypes.html#sequence-types-list-tuple-range).

## str.lower()
Retorna a string toda em letras minúscolas, ex:

	>>>palavra = "BaNana"
	>>>novapalavra = palavra.lower()
	>>>novapalavra
	'banana'

## str.upper()
Retorna a string toda em letras maiúsculas, ex:

	>>>palavra = "BaNana"
	>>>novapalavra = palavra.upper()
	>>>novapalavra
	'BANANA'

## str.strip()
Retorna a string sem espaços antes e depois, ex:

	>>>palavra = "   BaNana     "
	>>>novapalavra = palavra.strip()
	>>>novapalavra
	'BaNana'

## str.capitalize()
Retorna a string sem espaços antes e depois, ex:

	>>>palavra = "   banana     "
	>>>novapalavra = palavra.capitalize()
	>>>novapalavra
	'Banana'

# Manipulação/formatação de listas
Material completo [aqui](https://docs.python.org/pt-br/3/tutorial/datastructures.html), e [aqui](https://docs.python.org/3.6/library/stdtypes.html#sequence-types-list-tuple-range).
Para declarar uma lista use, por exemplo:

	lista = [] #lista vazia
	lista2 = [20, 5, "string"] #Lista já com componentes. OBS: podemos misturar os tipos de dados.

## len()
Retorna o tamanho da lista em questão
	
	>>> lista = [25,30,90]
	>>> len(lista)
	3

## list.count()
Retorna o número de ocorrencias de um valor dentro de uma lista, veja:

	>>> lista_teste = [0, 0, 5, 6, 0, 7, 9]
	>>> print(lista_teste.count(0))
	3

## list.index()
Retorna o índice do primeiro valor igual encontrado na lista, ex.:

	>>> frutas = ['Banana', 'Morango', 'Maçã', 'Uva', 'Maçã', 'Uva']
	>>> print(frutas.index('Uva'))
	3

# Simulando pressionamento de teclas
Veremos abaixo como dar entradas de teclado, tanto para Windows, MAC e Linux.
Utilizaremos a biblioteca [pyautogui](https://github.com/asweigart/pyautogui), que pode ser instalada utilizando o pip:

	pip install pyautogui
Para utilizar, alguns exemplos:

	>>> press('a')
	>>> typewrite('quick brown fox')
	>>> hotkey('ctrl', 'w')
Mais sobre o assunto [aqui](https://qastack.com.br/programming/13564851/how-to-generate-keyboard-events-in-python)
