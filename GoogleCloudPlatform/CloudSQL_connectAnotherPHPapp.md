# Conectando um servidor PHP externo ao CloudSQL

Contexto: Minha aplicação PHP está rodando em **outra hospedagem, fora do google**, e meu banco de dados é do **CloudSQL**.
Também é importante notar que **não é possível usar o SLQ Proxy no meu contexto** por conta de ser uma hospedagem limitada à execução do PHP.

Portanto, é necessário que seja acessado usando os certificados `.pem` para autenticar.


### Configuração do CloudSQL

Na sua instância do CloudSQL, certifique-se de:
- Ativar o IP Público;
- Em **Conexões > Rede > Redes Autorizadas**, adicione o IP de onde seu PHP irá acessar ao banco; 
- Em **Conexões > Segurança**, marque `Exigir certificados do cliente confiáveis`;
- Em **Conexões > Segurança > Gerenciar certificados do cliente**, crie um certificado para o seu servidor, e salve os três arquivos `.pem` em local seguro;


 ### Acessando pelo PHP

 Primeiramente, crie um arquivo zerado PHP e adicione o código para testar, depois aplique ao seu código.
 Embora pareça ómbio, testar ele dentro da sua aplicaçã pode restringir os logs, ou o verbose da saída de dados, então, para evitar interferência, use um arquivo limpo.

*Modelo 1 - Acesso via MySQLi*
 ```php
<?php

$conn = mysqli_init();
$conn->options(MYSQLI_OPT_SSL_VERIFY_SERVER_CERT, true);
mysqli_report(MYSQLI_REPORT_ERROR | MYSQLI_REPORT_STRICT);

try{
    $conn->ssl_set(
        'client-key.pem',
        'client-cert.pem',
        'server-ca.pem',
        NULL,
        NULL
    );
    $conn->real_connect(
        '35.195.52.215',
        'user',
        'password',
        'database-name',
        3306,
        NULL,

        // Configuração de Verificação de Certificado server-CA -->> Para Ativar a verificação, use MYSQLI_CLIENT_SSL no lugar (o que é OBRIGATÓRIO se você estiver usando o nome do host, e não um IP)
        MYSQLI_CLIENT_SSL_DONT_VERIFY_SERVER_CERT //não tem impacto na segurança, pois está sendo acessado VIA IP FIXO
    );

    if($conn->connect_error){
        throw new Exception('Impossível conectar com o banco de dados: '.$this->conn->connect_error);
    }
} catch (mysqli_sql_exception $e) {
    die("Erro de conexão ({$e->getCode()}): " . $e->getMessage());
}

echo "Conexão criptografada estabelecida com sucesso!";
```

*Modelo 2 - Usando PDO -> Adaptado do Exemplo do Google*
```php
<?php

namespace Google\Cloud\Samples\CloudSQL\MySQL;

use PDO;
use PDOException;
use RuntimeException;
use TypeError;

class DatabaseTcp
{
    public static function initTcpDatabaseConnection(): PDO
    {
        try {
            // Note: Saving credentials in environment variables is convenient, but not
            // secure - consider a more secure solution such as
            // Cloud Secret Manager (https://cloud.google.com/secret-manager) to help
            // keep secrets safe.
            $username = 'user'; // e.g. 'your_db_user'
            $password = 'password'; // e.g. 'your_db_password'
            $dbName = 'database-name'; // e.g. 'your_db_name'
            $port = '3306';
            $host = '35.195.52.215'; // e.g. '127.0.0.1' ('172.17.0.1' for GAE Flex)
            
            $options = [
                PDO::MYSQL_ATTR_SSL_CA     => __DIR__ . '/server-ca.pem',
                PDO::MYSQL_ATTR_SSL_CERT   => __DIR__ . '/client-cert.pem',
                PDO::MYSQL_ATTR_SSL_KEY    => __DIR__ . '/client-key.pem',
                PDO::MYSQL_ATTR_SSL_VERIFY_SERVER_CERT => false, // Quando se acessa o IP diretamente, pode-se desativar. JAMAIS DEIXAR EM FALSE SE USAR O NOME DO HOST
                PDO::ATTR_ERRMODE          => PDO::ERRMODE_EXCEPTION,
                PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
            ];

            // Connect to the database
            $conn = new PDO(
                "mysql:host=$host;port=$port;dbname=$dbName;charset=utf8",
                $username,
                $password,
                $options
            );
        } catch (TypeError $e) {
            var_dump($e->getMessage());

            throw new RuntimeException(
                sprintf(
                    'Invalid or missing configuration! Make sure you have set ' .
                        '$username, $password, $dbName, and $instanceHost (for TCP mode). ' .
                        'The PHP error was %s',
                    $e->getMessage()
                ),
                $e->getCode(),
                $e
            );
        } catch (PDOException $e) {
            throw new RuntimeException(
                sprintf(
                    'Could not connect to the Cloud SQL Database. Check that ' .
                        'your username and password are correct, that the Cloud SQL ' .
                        'proxy is running, and that the database exists and is ready ' .
                        'for use. For more assistance, refer to %s. The PDO error was %s',
                    'https://cloud.google.com/sql/docs/mysql/connect-external-app',
                    $e->getMessage()
                ),
                $e->getCode(),
                $e
            );
        }

        return $conn;
    }
}

$c = DatabaseTcp::initTcpDatabaseConnection();

echo "Conexão criptografada estabelecida com sucesso!";
```

**Por que posso desativar a verificação do sertificado do servidor?**
Neste caso (acessando o CloudSQL diretamente pelo IP público), isso não representa risco, pois você não está exposto a ataques como os de *DNS spoofing*.
Além do fato de o servidor estar restringindo o acesso adequadamente ao seu app, tanto pelos certificados (e o CloudSQL, sim, vai continuar verificando a validade da origem), quanto pela restrição por IP.

# Sobre

By: William Pilger
2025-01-31 10:19
