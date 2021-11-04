# Restringir o acesso a um diretório específico do FTP

Proteger diretório do FTP com restrição de IP e/ou senha.

# Restrição por Endereço de IP

Basta criar um arquivo `.htaccess` no diretório que se deseja proteger, com o seguinte conteúdo:

```
order deny,allow
deny from all
allow from 177.104.102.176
```

Para adicionar ou remover endereços de IP basta alterar a lista acima, e adicionar linhas com mais endereços.

# Restrição por senha

Crie um arquivo `.htaccess` no diretório desejado, com um conteúdo semelhante ao abaixo:

```
Options +Indexes
IndexOptions FancyIndexing FoldersFirst NameWidth=* DescriptionWidth=*

AuthType Basic
AuthName "NOME_DA_SUA_PREFERENCIA"
AuthUserFile /home/site/www/caminho/da/sua/pasta/.htpasswd
Require valid-user
```

Crie um arquivo `.htpasswd` dentro do diretório, ou no local onde você informou acima, contendo a chave de autorização htpassword, que pode ser gerada no servidor apache, ou em alguma ferramenta de sua preferência.
Como por exemplo:

```
william:$apr1$d4now26p$0kfiEDCw.fCBDtLmbHyhR2
```

# Extra: Exemplo de script para listar arquivos na pasta protegida

```
<?php

$diretorioAtual = __DIR__;
$arquivos 		= scandir($diretorioAtual);
foreach($arquivos as $arquivo){
	if($arquivo != "index.php" && $arquivo != "." && $arquivo != ".." && $arquivo != ".htaccess" && $arquivo != ".htpasswd"){
		echo "<a href=$arquivo>$arquivo</a><br>";
	}
}

?>
```

# Sobre

by: **will.i.am**

Agradecimanto: **IsDesign**
