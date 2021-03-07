# print
Funcionamento básico do comando **print**
Você pode encontrar a documentação completa (aqui)[https://docs.python.org/3/library/string.html#formatexamples].

## Print simples
Para realizar um print simples, com as variaveis separadas por espaços use

	nome = "William"
	idade = 23
	print("Eu sou", nome, "e tenho", idade, "anos")

A resposta será: **Eu sou William e tenho 23 anos**

## Alterando separador padrão do Print
Para alterar o separador padrão usamos o parâmetro **sep**:

	print("Eu sou", nome, "e tenho", idade, "anos", sep="_")
O Resultado será **Eu_sou_William_e tenho_23_anos**

	print("Eu sou", nome, "e tenho", idade, "anos", sep="")
O resultado será: **EusouWilliame tenho23anos**

## Usando a interpolação simples de string no Print

	dia = 2
	mes = 12
	ano = 1997
	print("Nasci no dia {}/{}/{}".format(dia, mes, ano))
O resultado será: **Nasci no dia 2/12/1997**

## Usando formatadores na interpolação de strings
Existem diversos formatadores utilizáveis, inclusive você pode alterar a ordem em que as variaveis são apresentadas no print.
Para isto basta colocar o índice entro das chaves:

	dia = 2
	mes = 12
	ano = 1997
	print("Nasci no dia {2}/{0}/{1}".format(mes, ano, dia))
O resultado será: **Nasci no dia 02/12/1997**
Para deixar o número de caracteres fixo, você pode utilizar o seguinte processo:

	dia = 2
	mes = 12
	ano = 1997
	print("Nasci no dia {:2d}/{:2d}/{:4d}".format(dia, mes, ano))
O resultado será: **Nasci no dia  2/12/1997**
Repare que apenas foi inserido um caractere a mais (um espaço a mais). Caso queira que o espaço seja preenchido com zeros, use:

	dia = 2
	mes = 12
	ano = 1997
	print("Nasci no dia {:02d}/{:02d}/{:04d}".format(dia, mes, ano))
O resultado será: **Nasci no dia 02/12/1997**

Para formatar valores float utilize o **:f**, como mostrado abaixo

	salario = 1256.36
	print("Meu salário é de {:f} reais")
O resultado será: **Meu salário é de 1256,36000 reais**

Para remover os zeros, use **.2** no formatador

	salario = 1256.36> print("Meu salário é de {:.2f} reais")
O resultado será: **Meu salário é de 1256,36 reais**

	
Para definir o número TOTAL de digitos (contando junto os após a vírgula), informe a quantidade antes do ponto:

	salario = 1256.36
	print("Meu salário é de {:7.2f} reais")
O resultado será: **Meu salário é de  1256,36 reais**
Observe o espaço a mais que ficou, pois o número tem apenas 6 dígitos.

Para substituir os espaços em branco por zeros, basta fazer isto:

	salario = 1256.36
	print("Meu salário é de {:07.2f} reais")
O resultado será: **Meu salário é de  01256,36 reais**


# random.random()
A função **random** faz parte da biblioteca random. Logo, para chama-la você precisa incluir ela. Vela a utilização abaixo:

    import random
    numero_aleatorio = random.random()
A função **random** sempre retorna um número entre 0.0 e 1.0


# random.randrange()
A função **randrange(de, ate)** serve para gerar números aleatórios inteiros em um intervalo específico.


# int()
A função **int()** retorna a parte inteira de um número.

# round()
A função **round()** arredonda um float para um valor inteiro.

# Formatadores/Funções de string

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
Material completo [aqui](https://docs.python.org/pt-br/3/tutorial/datastructures.html).
Para declarar uma lista use, por exemplo:

	lista = [] #lista vazia
	lista2 = [20, 5, "string"] #Lista já com componentes. OBS: podemos misturar os tipos de dados.

## len()
Retorna o tamanho da lista em questão
	
	>>> lista = [25,30,90]
	>>> len(lista)
	3

