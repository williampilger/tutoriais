# Configurar restrição por IP com DNS dinâmico

Como configurar restrição de acesso por IP para um DNS Dinâmico no Apache HTACCESS.

## Iniciando

Primeiro crie um host no seu provedor de DNS Dinâmico preferido, eu uso [No-IP](noip.com).

Para ver como instalar o DUC no seu PC linux, veja [esse tutorial](../ubuntu_server/configurew_no-ip.md).

Para instalar o DUC no windows, confira no site do No-IP as orientações, é bastante simples.

## Script para atualizar o endereço

A atualização do endereço de IP autorizado não é automática no servidor, portanto será necessário chamar um `script.php` para realizar a tarefa.
Isso poderá ser feito manualmente ou você pode configurar uma rotina de servidor para faze-lo.

Veja o exemplo abaixo:

```php
<?php
/*
 * Authenty AE - Bom Princípio-RS  |  github.com/authentyAE
 * by: Holodyn Atlanta             |  github.com/holodyn
 * Adaptação: will.i.am            |  github.com/williampilger
 *
 * 2021.11.05 - Bom Princípio - RS
 * ♪ Otherside / Red Hot Chili Peppers
 * 
 * .htaccess updater com DNC Dinâmico
 * 
 * 1 - Lê o arquivo $FileName
 * 2 - Profura por uma linha no formato abaixo:
 *  # DYNDNS {hostname} {notes}
 * 3 - Pega hostname e obtém o IP vinculado ao DNS
 * 4 - Sobrescreve o IP da linha logo abaixo da marcação encontrada com o IP obtido da pesquisa do passo 3.
 */


$FileName        = '.htaccess';
$salvaBackup      = true;
$seErroMantemAnterior   = true; // Se falhar com essa opção em false, remove o IP anterior
$echoOutput           = false; // Escreve resultado ao final da execução

$outputRows           = array();
$followTask           = null;
$host_ip              = null;
$host_dns             = null;
$host_result          = null;

if( $fh = fopen($FileName, 'r') ){
    while( isset($fh) && !feof($fh) && $line = fgets($fh) ){
        $line = trimLine( $line);
        # DYNDNS account.dyndns.org
        if( preg_match('/^\# DYNDNS ([0-9A-Za-z\.\-]+)(\s*|\s.*)$/', $line, $matches) ){
            $followTask = 'dns_allow';
            $host_ip = null;
            $host_dns = $matches[1];
            $host_result = gethostbyname($host_dns);
            if( !empty($host_result) && $host_result != $host_dns ){
                $host_ip = $host_result;
            }
            elseif( function_exists('shell_exec') ){
                $host_result = trimLine( shell_exec('host ' . $host_dns) );
                if( !empty($host_result) && preg_match('/^.* ([\d\.]+)$/', $host_result) ){
                    $host_ip = preg_replace('/^.* ([\d\.]+)$/', '$1', $host_result);
                }
            }
            $outputRows[] = $line;
        }
        else if( !empty($followTask) ){
            switch( $followTask ){
                case 'dns_allow':
                    if( preg_match('/^\# host /', $line) ){
                    continue 2;
                    }
                    if( empty($host_ip) ){
                        $outputRows[] = '# host lookup failed: ' . $host_dns . ' - ' . $host_result;
                        if( $seErroMantemAnterior ){
                            $outputRows[] = $line;
                        }
                    }
                    else {
                        if ($host_result !== $host_ip)
                            $outputRows[] = '# host result: ' . $host_result;
                        $outputRows[] = 'allow from ' . $host_ip;
                    }
                    break;
                case 'default':
                    $outputRows[] = $line;
                    break;
            }
            $followTask = null;
        }
        else {
            $outputRows[] = $line;
        }
    }
    fclose( $fh );

    if( $salvaBackup ){
        copy( $FileName, $FileName.'.bak' );
    }

    if( !empty($outputRows) ){
        $fw = fopen($FileName, 'w');
        fwrite( $fw, implode("\n", $outputRows)."\n" );
        fclose( $fw );
    }

    if( !empty($echoOutput) ){
        echo implode( "\n", $outputRows );
    }

}

function trimLine( $line ){
    return preg_replace('/[\n\r].*/s','',$line);
}

?>
```

O arquivo `.htaccess` precisará estar de acordo com o formato abaixo:

```txt
Order Deny,Allow
Deny from all

# DYNDNS seudnsdinamico.ddns.net
allow from 192.168.1.1

# DYNDNS maisum.ddns.net - voce pode colocar notas
allow from 192.168.1.1
```

## Configurando rotina automática

Você pode configurar uma rotina para atualizar este IP automaticamente:

```
30 * * * *
php -q /home/account/public_html/seuScript.php > /dev/null
```


## Sobre

by: will.i.am

**Agradecimentos**

Desenvolvido com base em [dyndns-htaccess](https://github.com/holodyn/dyndns-htaccess).
