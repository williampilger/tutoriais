# Comandos C++

## Opções de compilação

Conteúdo completo [aqui](https://man7.org/linux/man-pages/man1/g++.1.html) ou [aqui](https://linux.die.net/man/1/g++).

O **minGW**, ou GCC do linux possui vários parâmetros, estarão descritos alguns aqui:
- **-l** - informa bibliotecas que serão vinculadas imediatamente no momento da compilação. Geralmente arquivos `liblibrary.a` ou `liblibrary.so`.


## Comandos C++
```
Printf:
	Usa-se para imprimir coisas na tela.
	
	EX:
	printf("\nSua mensagem");
	OBS: exibe a mensagem "Sua mensagem" em uma NOAVA LINHA, por causa do "\n" que esta no inicio da mensagem, caso nao seja incluido, o a mensagem será exibida na mesma linha onde o cursor esta.

criando variaveis:
	float - cria uma variavel Real
	int   - Cria uma variavel inteira
	char  - Cria uma variavel caracter
	...
	EX:
	Char E, T, Y;
	obs: criu trez variaveis char.

Atribuindo valores às variaveis:
	Para dizer que uma variavel será igual a alguma coisa, utiliza-se o "=".
	EX's:
	scanf:
		comando serve para ESCANear... ele captura o que voce digita. Para atribuir o valor digitado a uma variavel, deve-se digitar o valor, e teclar enter.
		EX:
		scanf("%f", &prova1);
		neste exemplo, a variavel "prova1" recebe o valor que é digitado em um formato de variaveis "Float", por isso o "%f". A variavel precisa receber o "&" na frente.
	getch:
		Comando para tribuir valores as variaveis CHAR, e somente CHAR. Lembrando que, quando se digita uma tecla, ela armazena (sem precionar enter) o valor do caracter na tebela ASCII.
		EX:
		char E;
		E=gethc();
		OBS: neste codigo, primeiro criamos a varioavel char, e depois, atribuimos o valor nela, neste caso, o programa espera alguma tecla ser digitada.
		OBS2: Quando se digita "1", ela armazena 49, e assim segue... 

ezibindo variaveis:
	usa-se:
		"%f" - Para exibir o valor de uma variavel em formato float.
		"%i" - exibir o valor em formato inteiro.
		"%c" - exibir o valor da variavel em formato caracter.
		...
	exemplo:
		printf("%F", VARIAVEL);
		OBS: no lugar de "VARIAVEL" deve-se colocar uma variavel que tenha algum valor, e o valor desta será exibido em formato float.

Simbolos de ciomparação:
	"==" - igual
	">"  - maior
	"<"  - menor
	">=" - maior ou igual
	"<=" - menor ou iguar
	"=!" - Diferente
	EX:
	if (1>=K) compara o valor de "k" com "1".

if:
	serve para criar condições.
	EX:
	if(F>3) printf("O valor é maior que 3");
	OBS: Neste comando, ele compara o valor da variavel "F" (que vede ter cido criada, e ter um valor) com o valor inteiro "3", e caso seja maior, esidirá a mensagem "O valor é maior que 3".










Laços de repetição:

	while:
		usa-asem para criar loops, para fazer com que alguma coisa seja repetida emquanto a condição for verdadeira, quando ela for falça, sai do loop.
		EX's:
		1)
			while(condicão) comando;
			OBS: neste caso, pode-se repetiro somente UM comando.
		2)
			while(condição)
			{
			Comando1;
			comando2;
			...
			}

	Do-while:
		Usa-se para utilizar a condição no final.
		EX:
			do
			{
				comando1;
				comando2;
				...
			} while(condição);

	for:
		Utiliza-se para condições e comandos em uma linha.
		EX:
			for(X=1;X!=100;X++) printf("%d", X);
			OBSERVAÇÕES:
				* PRECISA ter dois ";" dentro dos parenteses. ex: (;;).
				* Neste codigo, "X" inicia com o valor de "1" (X=1), e a cada vez, é encrementado (X++), até que seja igual a "100" (X!=100).
			sintaxe:
				O comando é baseado em: "for(VALOR_INICIAL_DA_VARIAVEL;CONDIÇÃO;INCREMENTO/DECREMENTO)"
	Break:
		Quando é encontrado no programa, força o final de um laço (de um loop, ou repetição) independente de qualquer condição.
Exit:
	Força o ABORTO de um programa.
	sintaxe:
		void exit(Codigo_de_erro);
		ou
		exit();
		OBS: onde o "Codigo_de_erro" for iual a "0", significa o termino correto do programa, outro valor, é enviado ao sistema operacional, e ...


OPERADORES LOGICOS:
	"!"- NEGADO - Obs:" o NEGADo significa o contrario do que é, ou seja, se vc tiver um valor logico '1', ele sera '0', e se for '0' sera '1'."
	"="- ATRIBUIÇÃO - Obs: "Atribuir, é dizer que uma variavel agora É um valor"
	"=="- COMPARAÇÃO_IGUAL - Obs: "ele COMPARA dois valores: como por exemplo: 'if (5==b) COMANDO;'. ali ele compara se o 'b' é ou n igual a '5'."
	"!="- COMPARAÇÃO_DIFERENTE - Obs: "É o oposto do IGUAL."
	"++"- IMPLEMENTO - Obs: "Ele implementa uma variavel, ex: 'A++', ai ele diz que agora 'A' vale 'A+1'"
	"--"- DECREMENTO - Obs: "Decrementa a variavel, ou o contrario do INCREMENTO"

Operador Condicional:
	Sua estrutura e da seguinte forma:
	Deve ter uma Condição, um comando para ser executado caso verdadeiro, e um caso falso, veja:

	CONDIÇÃO?CASO_VERADEIRO:CASO_FALSO;
	Onde o "?" o ":" são obrigatorios, são eles que fazem a divisão dos comandos.



CRIANDO CONSTANTES:
	comando: "#define nome valor"
		onde, no "nome" fica o nome da constante, e no lugar de "valor" coloca-se o valor dela

	OBS: o priograma, na hora de compilar, irá substituir o 'nome' pelo conteudo da constante, em todo o programa.

CRIANDO MACROS:
	COMANDO: "#define NOME(VALORES) (O QUE FAZER COM OS VALORES)"
		ex: "#define SOMA(X,Y) (X+Y)"
			ai, toda a vez que o programa estiveer escrito "SOMA(3,4)" ele substituirá por "3+4".

	assim, depois dom nome da macro, entre perenteses, irão constar os valores, NA ORDEM DECLARADA, e em seguida, o calculo a ser feito com as variaveis.

	PROGRAMA EXEMPLO:
		#define MEDIA(a, b, c) ((a+b+c)/3) //aqui, ele cria um macro, que ira calcular a media de tres notas digitadas
		int a, b, c, me;                   // criando as variaveis.
		printf("Digite a primeira nota");
		scanf("%d", &a);
		printf("Digite a segunda nota");
		scanf("%d", &b);
		printf("Digite a terceira nota");
		scanf("%d", &c);
		me=MEDIA(a, b, c);                 //usando a macro.
		printf("%d é a media das notas");

IMPRIMINDO O ENDEREÇO DA VARIAVEL
	Para que por exemplo, no "printf", exibir o ENDEREÇO de memoria onde esta armazenada o valor da variavel, coloca-se o "&" antes da variavel, exemplo:
		printf("%d", &D)
			onde "D" é a variavel utiliada

CRIANDO vetores (CONJUNTOS)
	ela funciona como uma matriz, ou seja, ela será uma variavel com um nome qualquer, e logo após ela, DEVE-se informar a sua referência.
	E como se fosse um conjunto de variaveis.
	por exemplo:
		char a[50];
			OBS: foi criado um V vetor (é como um conjunto de variaveis) do tipo "char", com o nome de "a", com "50" indices;
	para escrever ou ler um vetor, SEMPRE se informa o indice.
	por exemplo:
		char a[3];
		scanf("%c", a[1]);  //aqui ele escreve no INDICE 1.
		printf("%c", a[1]); // lê o mesmo.
	IMPORTANTE: o primeiro 'lugar', ou o primeiro INEDICE, é SEMPRE o 0(ZERO), ou seja, se eu criar um vetor com 3 indices, eles serão: 0, 1, e 2.
	PARA CRIAR UM VETOR, E JA NA CRIAÇÃO ESCREVE-LO ( PARA FAZER UMA TABELA VERDADE, POR EXEMPLO) USA-SE, POR EXEMPLO:
		CHAR A[5]={5, 6, 7, 10, 450}; //CRIOU OS TODOS OS ENDEEÇOS OBS: NAO ESQUECE O PONTO E VIRGULA

			OU

		char a[5]=
			{
			5,	\\indice: a[0]  \\NAO ESQUECER A VIRGULA!!!!!!!
			6,	\\indice: a[1]
			7,	\\indice: a[2]
			10,	\\indice: a[3]
			450,	\\indice: a[4]
			};      \\NAO ESQUECER ESTE PONTO E VÍRGULA
CRIANDO MATRIZES (CONJUNTOS COM DOIS INDICES COMO REFEÊNCIA)
	uma matriz, funciona como um vetor, só que agora, deve-se utilizar DOIS indices para chamar uma das variaveis, ou algum endereço.
	assim, ela dá a ideia de uma coluna, com muitas linhas, e o primeiro indice a ser informado, é a linha, depois, a coluna, veja:
		char a[10][10];  //cria-se uma matriz com 10 linhas e 10 colunas. OBS: seria a mesma coisa que criar um vetor de 100 posições, só que agora, com dois indices como referência
		scanf("%c", a[0][0]);  // escreve no primeiro indice da matriz.
	CRIAR E AO MESMO TEMPO ESCREVER:
		int a[2][3]={0, 1, 2, 3, 4, 5};    //aqui estão todos escritos na mesma linha pois a memoria é linear, a diferença é SOMENTE NA HORA DE LER E ESCREVER DEPOIS DA CRIAÇÂO.

			ou (para quem quer organizar melhor, pode dar espaços de enter, como no vetor.

		int a[2][3]=	{0, 1,
				 2, 3,  //NAO ESQUECER AS VIRGULAS
				 4, 5}; // lembrando que isso afeta somente A ESTETICA  \\ NAO ESQUEVE A MERAD DO PONTO E VIRGULA

		AGORA, PARA LER E ESCREVER EM UMA MATRIZ:
			scanf("%d", a[0][0]); // sobrescreve o valor no posição [0][0] da matriz. que é o "0".
			printf("%d", a[2][1]);  // le o valor da posição [2][1], que é o "5".


MATRIZES TRIDIMENCIONAIS:
	cria-se uma matris, assim como se cria uma variavel, como uma matriz simples, ou como um vetor, soó que agora com mais um valor.
	veja:
		int a[3][2][5];	\\criou-se uma matris que pode ser representada graficamente por um CUBO: onde, a ultima "coordenada" é a linha, a penúltima "coordenada" é a coluna, e a primeira, é a "camada" onde ela estara.
			OBS: seria como criar 3 matrizes de duas linhas e três colunas. só que agora, em um so. seria como se as três estivessem "empilhadas" e o primeiro indice (neste caso, o 3) fosse a camada, ou indicasse quais das três matrizes é a que queremos utilizar.
	para escrever, por exemplo:
		scanf("%d", a[1][1][4]); \\escreve na SEGUNDA matris, na sua SEGUNDA linha e QUINTA coluna! ATENSAOOOOOOO, as linhas, colunas, e matrises de indice 0(ZERO) são contadas.
OBS SOBRE VETORES E MATRIZES:
		quando se cria um vetor ou uma matriz, se informa a QUANTIDADE de linhas colunas e etc... mas depois, o ZERO CONTA, ou seja, que eu criar um vetor: "int a[5];" ele terá CINCO indices, mas eles vão de ZERO à QUATRO.

FUNÇÂO kbhit:
	Esta função, serve para verificar se o bufer do teclado tem algum caracter... assim ele vai retornar "1" se alguma tecla foi precionada, e "0" se nao.
	associada ao "getch()" pode evitar que o programa pare, para ver se algumna tecla seja precionada, e assim irá ler somente quando for, podendo-se executar mais do que uma coisa ao mesmo tempo.
		exemplo:
			int a;
			while(1){
			if(kbhit()){
				a=getch();
				printf("Você precionou %c", a);
				}
				}

UTILIZANDO TECLAS DE DOIS BITS(COMO "ESC", "F1...", "Delete", etc)
	quando precionamos teclas como "F1, F2,..." o bufer, armazena DOIS byts, o primeiro, é CEMPRE ZERO (no caso dos F1, F2, Fn) e o segundo, varia(Para ver isso, pode-se pegar, e mandar um programa, ler e escrever duas vezes o que tenha no teclado.
	no caso das setas(Up, Down, ...) o caracter que é salvo no primeiro byte, é sempre "224"e o outro varia.
		Exemplo de programa para ver quel das teclas é precionada:
			
REPRESENTANDO UMA STRING EM C. (UMA VARIAVEL QUE ARMAZENA TEXTOS, MAIORES QUE UM CARACTER)
	#include <string.h>
	uma String, nada mais é, que um VETOR do tipo CHAR, só que com algumas diferênças:
		para atribuir o valor NULO à ela, utiliza-se o "\0", isso, é como setar uma variavel normal em zero.
		UMA STRING, COM UM VALOR QUALQUER, POR EXEMPLO "João", SEMPRE, TERÁ UM CARACTER PARA "MARCAR" O SEU "FIM", E ESSE CARACTER É O "\0", ENTÃO, FICA ASSIM: "J o ã o \0" (separados por espaços cada caracter, só para EXEMPLO)
		Na hora de criar uma string, pode-se atribuir o valor desta forma:
			char nome[7]=João; //a styring foi criada, com o nome "nome", e o seu conteúdo é "João\0", por que o "\0" SEMPRE vai estar no final.
			...
			nome[]={J, o, ã, o, \0}; // atribuindo valores DEPOIS DA CRIAÇÂO.
			nome[0]=J; //agora, atrigundo valores em um caracter por linha.
			nome[1]=o; //E assim segue.

		NOTE QUE: para atribuir todo o nome, de uma vez, deichamos o indice vazio ("nome[]"), e aí atribuimos o valor, com cada caracter separado por virgula e espaço, e SEM ESQUECER DO CARACTER QUE MARCA O FIM ("\0").
	Para escrever em uma string o que esta sendo digitado (como o "scanf()"), usamos o "gets", pois, se algujm espaço for digitado com o "scanf()", ela ANULA tudo o que foi digitado depois do espaço, já o "gets" não.
	veja:
		char nome[20]; //o vinte, é um valor qualquer, que representa o tamanho da string
		clrscr();
		puts("Digite seu nome: ");
		gets (nome);
		...
FUNÇÃO "strcpy()"
	#include <stedio.h>
	#include <string.h>
	SERVE PARA copiar COPNTEÚDOS DE UMA STRING PARA OUTRA, SUBSTITUINDO O VALOR ANTERIOR DA QUE RECEBE!!!
	também pode ser usado para copiar uma valor qualquer, como por exemplo "joão" para uma string, substituindo o valor na string que recebe.
	veja:
		...
		strcpy(para,de); //copia o conteúdo da string "de" para a string "para".
		...
	ou:
		...
		strcpy(para, "João"); //Copia "João" para a string "para".

FUNÇÃO "strcat()":
	#include <stedio.h>
	#include <string.h>
	SERVE PARA ADICIONAR ALGUM CONTEUDO À UMA STRING.
	Como se fosse copiar, o conteudo de uma string, para outro, só que agora, sem substituir, nem sobrescrever, e sim "SOMAR" isso;
	veja:
		strcat(para, de); //adiciona o valor da string "de" ào conteudo da string "para".
		...
	ou:
		strcat(para, "João"); //adiciona o conteudo "João" á string "para.
		strcat(para, "é loiro"); // Adiciona á string "para", o conetúdo "é loiro".
		// Agora, o valor da string "para", é: "João é loiro".

FUNÇÃO "strcmp()"
	#include <stedio.h>
	#include <string.h>
	COMPARA O CONTEÚDO DE DUAS STRINGS, E RETORNA UMA VALOR MAIOR QUE ZERO, SE A PRIMEIRA FOR MAIOR, E UM MENOR QUE ZERO, SE A SEGUNDA FOR MAIOR. RETORNA ZERO, SE ELAS FOREM IGUAIS.
	Exemplo:
		...
		char s1[10];
		char s2[10];
		clrscr();
		puts("Digite a senha");
		gets(s1);
		puts("Redigite a senha");
		gets(s2);		
		if (strcmp(s1,s2)) prinf("As senhas não conferem"); //aqui, ele comparam,m e se as duas forem IGUAIS, ele vai retornar ZERO, por isso, que quando forem iguais, o "if" será falço, e quando forem diferentes, ele retorna, qualquer valor maior ou menor que zero (dependendo do caso), e como qualquer outro valor que seja diferente de zero, é identificado como VERDADEIRO, SEMPRE será verdadeiro quando forem diferentes.
			else prinf ("senhas conferem");
		...

FUNÇÃO "streql()"
	#include <string.h>
	COMAPARA O CONTEÚDO DE DUAS STRINGS, E SE FOREM IGUAIS, RETORNA 1, E SE DIFERENTES, RETORNA 0.
	EXEMPLO:
		char senha[10];
		char sen[10];
		clrscr();
		puts("digite a senha: ");
		gets(senha);
		puts("Digite novamente");
		gets(sen);
		if(streql(senha, sen)) printf("senhas conferem"); //compara o valor das strings, e se for igual, vai retornar "1", que no "if", é verdadeiro.
		else Senhas diferentes;
		...

FUNÇÃO "strlen()"
	#include <string.h>
	RETORNA O TAMANHO DE UMA STRING
	EXEMPLO:
		char nome[10]=João; //definio a tring "nome" com o conteúdo de "João";
		int quantidade;
		quantidade=strlen(nome); // aqui ele vai retornar q quantidade de caracters que a string esta ocupando, que no caso, são 4.
		...

FUNÇÃO "sprintf()"
	faz uma espécie de simulação de "printf()", só que, ao invés de escrever na tela, escreve em uma string:
	veja:
		char frase[50];
		sprintf(frase, “Ivoti, %d de %s de %d \n”, 6, “maio”,2011); //aqui, podem ser usadas variaveis no lugar dos valores...
		...
FUNÇÃO "strrev()"
	INVERTE o conteúdo de uma string.
	veja:
		char nome[20]=João;
		printf("%s",strrev(nome)); //escreve "oãoJ" e SALVA ISSO NA STRING.

MANIPULAÇÂO DE ARQUIVOS
	Promeiro, precisa-se criar uma "variavel" que contenha o endereço de memoria(não do HD), q é onde os arquivos vão ser salvos. o C, NAO CONTEM NENHUM COMANDO PARA ACESSAR DIRETAMENTE ALGUM ARQUIVO.
	Para definir, usa-se:
		FILE *fp; //cria a variavel "fp" que vai conter o endereço que o sistema operacional "forneceu" na memoria RAM.
		fp=fopen("nome","modo") //ABRE a conexão com o arquivo, agora sim, no disco rigido. no lugar de "nome" vai o nome do arquivo. no lugar de "modo" vão duas letras, que ja veremos:
	O MODO, deve ser setado da seguinte forma:
		"r" Abre um arquivo para leitura
		"w" Cria um arquivo para escrita
		"a" Acrescenta dados para um arquivo existente
		"rb" Abre um arquivo binário para leitura
		"wb" Cria um arquivo binário para escrita
		"ab" Acrescenta dados a um arquivo binário existente
		"r+" Abre um arquivo para leitura/escrita
		"w+" Cria um arquivo para leitura/escrita
		"a+" Acrescenta dados ou cria um arquivo para leitura/escrita
		"r+b" Abre um arquivo binário para leitura/escrita
		"w+b" Cria um arquivo binário para leitura/escrita
		"a+b" Acrescenta ou cria um arquivo binário para leitura/escrita
		"rt" Abre um arquivo texto para leitura
		"wt" Cria um arquivo texto para escrita
		"at" Acrescenta dados a um arquivo texto
		"r+t" Abre um arquivo-texto para leitura/escrita
		"w+t" Cria um arquivo texto para leitura/escrita
		"a+t" Acrescenta dados ou cria um arquivo texto para leitura/escrita
	FUNÇÔES:
		fopen() Abre um fluxo
		fclose() Fecha um fluxo
		putc() Escreve um caractere para um fluxo
		getc() Lê um caractere para um fluxo
		fseek() Procura por um byte especificado no fluxo
		fprintf() É para um fluxo aquilo que printf() é para o console
		fscanf() É para um fluxo aquilo que scanf() é para o console
		feof() Retorna verdadeiro se o fim do arquivo é encontrado
		ferror() Retorna verdadeiro se ocorreu um erro
		fread() Lê um bloco de dados de um fluxo
		fwrite() Escreve um bloco de dados para um fluxo
		rewind() Reposiciona o começo do arquivo
		remove() Apaga um arquivo
	OBS: Para usar essas funções, PRECISA colocar DENTRO DOS PARÊNTESES, o nome da "variavel" que tem o diretório do "fluxo"
		Fluxo, é a "memoria intermediaria", ou seja, onde as coisas então na RAM. as alterações, no arquivo na unidade(HD), não são salvas imediatamente, ou seja, só é alterado, quando o arquivo é fechado(fclose()).
		
	USANDO AS FUNÇÔES:
		putc():
			exemplo de escrita:
				#include <stdio.h>
				#include <stdlib.h>
				int main(void)
				{
				FILE *fp; //Abre o fluxo "fp"
				char ch;  // cria a variavel "ch"
				fp=fopen("teste.txt","wt“); //ABRE O ARQUIVO
				do
				{
				ch=getchar(); //espera o que a pessoa vai digitar, para salvar na variavel "ch"
				putc(ch, fp); //escreve o que tem na variavel no fluxo "fp"
				} while (ch!='$'); //condição, que diz, que quando a pessoa digitar "$", ele para a escrita
				fclose(fp); //fecha o flux
				}
			exemplo de leitura:
				#include <stdio.h>
				#include <stdlib.h>
				int main(void)
				{
				FILE *fp; //abre o fluxo "fp"
				char ch;  //cria a variavel "ch"
				fp=fopen("teste.txt","rt"); //abre o fluxo, em modo de leitura de texto
				ch= getc(fp);    //usa o comando "getc()" para ler caracter por caracter do texto, e atribuir o valor à "ch"
				while(!feof(fp)) //usa a função "feof()" para ver se o caminho existe, e se não existir, a função retorna "1", mas como tem o "!" lá , NEGA isso, e fica "0" aí sim, ele diz que falhou
				{
				putchar(ch); //escreve na tela
				ch=getc(fp); //paga mais um caracter no arquivo, e atribui para a variavel "ch"
				}
				getch();
				}
				
			escrevendo uma stringem um arquivo:
				fputs(char *string, FILE *fp);
					OBS: "*string", é a string a ser escrita., e "fp" é o fluxo(caminho\arquivo.extensão), onde o troço será escrito.


ESTRUTURAS:
	- É um registro
	- Uma coleção de veriaveis referenciadas sobre o mesmo nome
	- Tipo de dado estruturado heterogêneo
	- Cada tipo de "elemento" do registro, pode ser de um tipo diferente... (int, char, etc)
	- Os "elementos" do registro, serão chamados de campo

	- Um conjunto de informações sobre um mesmo objeto
	- Cada elemento tem uma certa quantidade de bytes

	FORMA GERAL:

		struct nome_do_tipo_da_estrutura
			{
			tipo nome_de_elemento_1;
			tipo nome_de_elemento_2;
			...
			tipo nome_de_elemento_n;
			}

		OBS: "nome_do_tipo_da_estrutura" define a quantidade de bytes que a estrutura armazena, ou seja, o tipo da estrutura.


	DECLARANDO UMA ESTRUTURA:
		
		ESTRUTURA É COMO SE FOSSE UM NOVO TIPO DE VARIAVEL QUE VOCE CRIA... E ELA SERVE DE MODELO PARA CRIAR OUTRAS INFINITAS VARIAVEIS COM AQUELE TIPO

		Forma 1(pior delas):

			struct{
			char nome[30];
			char rua[40];
			char cidade[20];
			char estado[3];
			unsigned long inte cep;
			}info;

			OBS: Onde "info" é o nome do "conjunto de variaveis" que é criado... onde se cria somente UM conjunto... e cada conjunto "info" terá o "nome", "cep", etc...

		Forma 2:

			struct MODELO{
			char nome[30];
			char rua[40];
			char cidade[20];
			char estado[3];
			unsigned long inte cep;
			}info, binfo, cinfo;

			OBS: 	onde "MODELO" é o TIPO de variavel criada... o novo tipo de variavel.. e todas as outras que forem criadas com base naquele "modelo" de variavel, terá "nome", "rua", "cep", etc
				e "info", "binfo", e "cinfo" são "conjuntos de variaveis" que tem o mesmo modelo... ou seja, cada uma tem "dentro" de si, "nome", "rua", "cep", etc...

		Forma 3 (mais usual)

			struct MODELO{
			char nome[30];
			char rua[40];
			char cidade[20];
			char estado[3];
			unsigned long inte cep;
			};


			OBS: onde "MODELO" é o TIPO de variavel criada... o novo tipo de variavel.. e todas as outras que forem criadas com base naquele "modelo" de variavel, terá "nome", "rua", "cep", etc...

		IMPORTANTE: 	esta não serve para salvar nada ainda, e não ocupa memoria, pois ela é SOMENTE UM "MODELO", ou um "TIPO" de variavel, de onde eu posso criar outras, iguais, que servirão para salvar dados.

				pode-se notar que, não se tem nome de variavel ali... somente o "tipo"

				para criar variaveis com esse modelo, usa-se:

					struct MODELO info;

						OBS: agora, criou-se uma variavel com o nome "info" que segue o modelo "MODELO", e terá "dentro de si" as "subvariaveis" "rua", "cidade", "cep", etc...

	ESCREVENDO OU LENDO UMA ESTRUTURA:
		supondo-se que a estrutura foi declarada da seguinte forma:

			struct MODELO{
			char nome[30];
			char rua[40];
			char cidade[20];
			char estado[3];
			unsigned long inte cep;
			}info;
		
		e ai sim, posso me referir à cada variavel da estrutura com o NOME.VARIAVEL. Ex: "info.nome" (como no caso da acima)

	USANDO PONTEIROS:
		Para criar um ponteiro para uma estrutura, usa-se:(considerando o exemplo anterior)
			
			scruct MODELO *p;
			p=&info;

			OBS: onde "MODELO" é o tipo de estrutura, e "p" é o ponteiro criado...
			OBS2: "info" é O NOME da estrutura que esta sendo "apontada"...

		Apontando pára uma das "subvariaveis" da estrutura...

			p->nome

			OBS: onde "p" é o ponteiro, "nome" é a "subvariavel" que tem dentro da estrutura "info"(seguindo o exemplo anterior...), e "->" é o comando que PRECISA estar ali para usar isso...

			exemplo:
				*p->nome=NOME;






ESCREVENDO E LENDO ARQUIVOS COM "fread()" e "fwrite()"
	SERVEM PARA ESCREVER E LER ARQUIVOS DE FORMA MUIITO MAIS SIMPLES E RAPIDA... PRINCIPALEMTNE PARA ARMAZENAR ESTRUTURAS OU VARIAVEIS...
	IMPORTANTE: Para que a leitura e gravação de certo, é preciso que a leitura seja feita da MESMA FORMA como foi feita a escrita... tem que ter um padrão
	COMO FUNCIONA:
		fread(&variavel, quantidade_de_bits_da_variavel, quantidade_de_vezes, fluxo);

		fwrite(&variavel, quantidade_de_bits_da_variavel, quantidade_de_vezes, fluxo);

			bom... 	o primeiro "campo" a ser preenchido ("&variavel"), corresponde ao ENDEREÇO INICIAL da variavel que tem as informações.
				O segundo "campo", contem a quantidade de bits que tem cada CONJUNTO DE INFORMAÇÔES, onde se pode usar uma função que calcula isso... que é: sizeof()... usada da seguinte forma: sizeof(tipo da variavel);
				no terceiro "campo", coloca-se a quantidade de vezes que se precisa repetir o comando...
				e por fim... o fluxo do arquivo...
	VEJA UM EXEMPLO:
		struct evento{
		int dia;
		int hora;
		char nome[30];
		}
		struct evento agenda[20]; //CRIA UMA STRUCT DO TIPO EVENTO COM O NOME DE AGENDA...
		FILE *fluxo;
		fluxo=fopen("nomedoarquivo.txt", "rt");//abre o fluxo como gravação
		fread(&agenda[0], sizeof(struct evento), 20, fluxo); //copia os dados do conjunto de structs "agenda", para o arquivo...
		fclose(fluxo);//fehca o fluxo

			OBS: Como vooce pode ver, "agenda" tem 20 posições... por isso, precisa-se colocar o "20" na "quantidade de vezes"...

CONVERTER VARIAVEIS
	CONVERTER UMA CHAR OU STRING PARA INT
		#include <stdlib.h>
		int=atoi(string); // "int" é a variavel inteira. "atoi" é o comando, e esta na biblioteca "stdlib.h". "string" é a char ou a string...
	CONVERTER UMA CHAR OU STRING PARA UMA FLOAT
		#include <stdlib.h>
		float=atof(string); // "float" é a variavel float. "atof" é o comando, e esta na biblioteca "stdlib.h". "string" é a char ou a string...























