#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "DHTesp.h"

// Declaração das variáveis e objetos
DHTesp dht;
const int pinoSensorPorta = 5;    // D1
const int pinoBuzzer = 16;        // D0
const int pinoSensorPresenca = 4; // D2
const int pinoLedVermelho = 15;   // D8
const int pinoLedVerde = 13;      // D7

const char* ssid = "Lima"; // Nome da rede WI-FI
const char* password = "flav2275"; // Senha da rede WI-FI

ESP8266WebServer server(80);

void handleRoot() {
  float valorUmidade = dht.getHumidity();
  float valorTemperatura = dht.getTemperature();

  // Lê o estado do reed switch
  int portaEstado = digitalRead(pinoSensorPorta);
  String portaStatus;
  
  // Verifica se o reed switch está acionado ou não
  if (portaEstado == HIGH) {
    portaStatus = "Aberta";
    // Desliga o buzzer e acende o LED verde quando a porta está aberta
    digitalWrite(pinoBuzzer, HIGH);
    digitalWrite(pinoLedVermelho, LOW);
    digitalWrite(pinoLedVerde, HIGH);
  } else {
    portaStatus = "Fechada";
    // Liga o buzzer e acende o LED vermelho quando a porta está fechada
    digitalWrite(pinoBuzzer, LOW);
    digitalWrite(pinoLedVermelho, HIGH);
    digitalWrite(pinoLedVerde, LOW);
  }
  
  // Lê o estado do sensor de presença
  int presencaEstado = digitalRead(pinoSensorPresenca);
  String presencaStatus;
  
  if (presencaEstado == HIGH) {
    presencaStatus = "Presença detectada";
  } else {
    presencaStatus = "Presença não detectada";
  }
  
  // Verifica se houve falha na leitura do sensor de valorTemperatura e valorUmidade
  if (isnan(valorUmidade) || isnan(valorTemperatura)) {
    Serial.println("Falha ao ler do sensor DHT!");
    server.send(500, "text/plain", "Falha ao ler do sensor DHT");
    return;
  }

  // Constrói a página HTML de resposta
  String pagina = "<html><body>";
  pagina += "<h1>Informações do Sensor</h1>";
  pagina += "<table border='1'><tr><th>Parâmetro</th><th>Valor</th></tr>";
  pagina += "<tr><td>Umidade</td><td>" + String(valorUmidade) + "%</td></tr>";
  pagina += "<tr><td>Temperatura</td><td>" + String(valorTemperatura, 1) + " °C</td></tr>";
  pagina += "<tr><td>Porta</td><td>" + portaStatus + "</td></tr>";
  pagina += "<tr><td>Presença</td><td>" + presencaStatus + "</td></tr>";
  pagina += "</table>";
  pagina += "</body></html>";

  server.send(200, "text/html", pagina);

  // Escreve os valores lidos no Serial Monitor
  Serial.print("Umidade: ");
  Serial.print(valorUmidade);
  Serial.print("%\t");
  Serial.print("Temperatura: ");
  Serial.print(valorTemperatura, 1);
  Serial.print(" °C\t");
  Serial.print("Porta: ");
  Serial.print(portaStatus);
  Serial.print("\tPresença: ");
  Serial.println(presencaStatus);
}

void handleNotFound(){
  String valorMonitoramento = "Página não encontrada\n";
  server.send(404, "text/plain", valorMonitoramento);
}

void setup(void){
  Serial.begin(115200);
  dht.setup(14, DHTesp::DHT11); // GPIO14 (D5)
  pinMode(pinoSensorPorta, INPUT_PULLUP); // Configura o pino do reed switch como entrada (GPIO5)
  pinMode(pinoBuzzer, OUTPUT);  // Configura o pino do buzzer como saída (GPIO16)
  pinMode(pinoSensorPresenca, INPUT); // Configura o pino do sensor de presença como entrada (GPIO4)
  pinMode(pinoLedVermelho, OUTPUT); // Configura o pino do LED vermelho como saída (GPIO15)
  pinMode(pinoLedVerde, OUTPUT); // Configura o pino do LED verde como saída (GPIO13)
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Conectando ao Wi-Fi...");

  // Aguarda conexão
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Verifica se a conexão foi bem-sucedida
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("");
    Serial.print("Conectado a ");
    Serial.println(ssid);
    Serial.print("Endereço IP: ");
    Serial.println(WiFi.localIP());

    if (MDNS.begin("esp8266")) {
      Serial.println("MDNS iniciado");
    }

    server.on("/", handleRoot);
    server.onNotFound(handleNotFound);

    server.begin();
    Serial.println("Servidor HTTP iniciado");
  } else {
    Serial.println("Falha ao conectar ao Wi-Fi.");
  }
}

void loop(void) {
  if (WiFi.status() == WL_CONNECTED) {
    server.handleClient();

    // Lê os valores dos sensores
    float valorUmidade = dht.getHumidity();
    float valorTemperatura = dht.getTemperature();

    int portaEstado = digitalRead(pinoSensorPorta);
    String portaStatus;
    if (portaEstado == HIGH) {
      portaStatus = "Aberta";
      digitalWrite(pinoBuzzer, HIGH);
      digitalWrite(pinoLedVermelho, LOW);
      digitalWrite(pinoLedVerde, HIGH);
    } else {
      portaStatus = "Fechada";
      digitalWrite(pinoBuzzer, LOW);
      digitalWrite(pinoLedVermelho, HIGH);
      digitalWrite(pinoLedVerde, LOW);
    }

    int presencaEstado = digitalRead(pinoSensorPresenca);
    String presencaStatus;
    if (presencaEstado == HIGH) {
      presencaStatus = "Presença detectada";
    } else {
      presencaStatus = "Presença não detectada";
    }

    // Verifica se houve falha na leitura do sensor de valorTemperatura e valorUmidade
    if (isnan(valorUmidade) || isnan(valorTemperatura)) {
      Serial.println("Falha ao ler do sensor DHT!");
    } else {
      // Escreve os valores lidos no Serial Monitor
      Serial.print("Umidade: ");
      Serial.print(valorUmidade);
      Serial.print("%\t");
      Serial.print("Temperatura: ");
      Serial.print(valorTemperatura, 1);
      Serial.print(" °C\t");
      Serial.print("Porta: ");
      Serial.print(portaStatus);
      Serial.print("\tPresença: ");
      Serial.println(presencaStatus);
    }

    delay(600); // Delay entre cada leitura
  } else {
    Serial.println("Tentando reconectar ao Wi-Fi...");
    WiFi.reconnect();
    delay(5000); // Espera 5 segundos antes de tentar novamente
  }
}
