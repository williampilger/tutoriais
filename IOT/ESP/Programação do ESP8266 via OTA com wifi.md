# Programação do ESP8266 via OTA com wifi

Aqui veremos como configurar um ESP8266 para programação via OTA (Over-The-Air).
Este passo-a-passo é baseado no [Tutorial do Felipeflop](https://www.filipeflop.com/blog/programacao-esp8266-ota-wifi/).

## Pré requisitos

Para iniciar, precisaremos ter instalado na máquina os seguintes programas:
- Arduíno IDE - Disponível no site oficial: [Arduino](arduino.cc)
- Python - Disponível no site oficial [Python](https://www.python.org/downloads)

Para preparar a Arduino IDE para reconhecer e programar o ESP, caso ele não já esteja, consule [este tutorial](https://www.filipeflop.com/blog/programar-nodemcu-com-ide-arduino/)

## Gravando o novo formware

Abra  o Arduino IDE, e utilize o sketch padrão que acompanha o plugin do ESP8266 (se você realizou as etapas descritas no tutorial mencionado acima, ele já estará disponível para você) cujo nome é **ArduinoOTA -> Basic OTA**. Lembre-se também de configurar a placa correta.
O código abaixo foi alterado pelo FelipeFlop, mas tem como base o modelo acima:

"""C++
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
 
const char* ssid = "NOME DA SUA REDE WIFI";
const char* password = "SENHA DA SUA REDE WIFI";
 
void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Conexao falhou! Reiniciando...");
    delay(5000);
    ESP.restart();
  }
 
  // Porta padrao do ESP8266 para OTA eh 8266 - Voce pode mudar ser quiser, mas deixe indicado!
  // ArduinoOTA.setPort(8266);
 
  // O Hostname padrao eh esp8266-[ChipID], mas voce pode mudar com essa funcao
  // ArduinoOTA.setHostname("nome_do_meu_esp8266");
 
  // Nenhuma senha eh pedida, mas voce pode dar mais seguranca pedindo uma senha pra gravar
  // ArduinoOTA.setPassword((const char *)"123");
 
  ArduinoOTA.onStart([]() {
    Serial.println("Inicio...");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("nFim!");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progresso: %u%%r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Erro [%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Autenticacao Falhou");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Falha no Inicio");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Falha na Conexao");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Falha na Recepcao");
    else if (error == OTA_END_ERROR) Serial.println("Falha no Fim");
  });
  ArduinoOTA.begin();
  Serial.println("Pronto");
  Serial.print("Endereco IP: ");
  Serial.println(WiFi.localIP());
}
 
void loop() {
  ArduinoOTA.handle();
}
"""

Após gravar este código no seu ESP (via cabo), ele já estará disponível na sua Wi-fi e aparecerá nas portas seriais via rede na Arduino IDE.

Você verá que ao enviar o primeiro codigo via OTA, será solicitada a autorização para o python acessar a rede, normal.