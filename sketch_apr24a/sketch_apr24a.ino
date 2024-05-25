#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "DHTesp.h"

DHTesp dht;
const int pinoSensorPorta = 5;    // GPIO5 (D1)
const int pinoBuzzer = 16;        // GPIO16 (D0)
const int pinoSensorPresenca = 4; // GPIO4 (D2)
const int pinoLedVermelho = 15;   // GPIO15 (D8)
const int pinoLedVerde = 13;      // GPIO13 (D7)

const char* ssid = "Ti-2G";
const char* password = "Sup4@test";

ESP8266WebServer server(80);
bool presencaDetectada = false; // Variável booleana para o sensor de presença

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
    presencaDetectada = true;
  } else {
    presencaStatus = "Presença não detectada";
    presencaDetectada = false;
  }
  
  // Verifica se houve falha na leitura do sensor de valorTemperatura e valorUmidade
  if (isnan(valorUmidade) || isnan(valorTemperatura)) {
    Serial.println("Falha ao ler do sensor DHT!");
    server.send(500, "text/plain", "Falha ao ler do sensor DHT");
    return;
  }

  // Constrói a mensagem de resposta com os valores lidos
  String valorMonitoramento = "Umidade: " + String(valorUmidade) + "\n" +
                   "Temperatura: " + String(valorTemperatura, 1) + "\n" +
                   "Porta: " + portaStatus + "\n" +
                   "Presença: " + presencaStatus + "\n" +
                   "PresencaDetectada: " + String(presencaDetectada ? 1 : 0) + "\n";
  
  server.send(200, "text/plain", valorMonitoramento);

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
  Serial.print(presencaStatus);
  Serial.print("\tPresencaDetectada: ");
  Serial.println(presencaDetectada ? 1 : 0);
}

void handleNotFound(){
  String valorMonitoramento = "Página não encontrada\n";
  server.send(404, "text/plain", valorMonitoramento);
}

void setup(void){
  Serial.begin(9600);
  dht.setup(14, DHTesp::DHT11); // GPIO14 (D5)
  pinMode(pinoSensorPorta, INPUT_PULLUP); // Configura o pino do reed switch como entrada (GPIO5)
  pinMode(pinoBuzzer, OUTPUT);  // Configura o pino do buzzer como saída (GPIO16)
  pinMode(pinoSensorPresenca, INPUT); // Configura o pino do sensor de presença como entrada (GPIO4)
  pinMode(pinoLedVermelho, OUTPUT); // Configura o pino do LED vermelho como saída (GPIO15)
  pinMode(pinoLedVerde, OUTPUT); // Configura o pino do LED verde como saída (GPIO13)
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Aguarda conexão
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
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
}

void loop(void){
  server.handleClient();
  delay(600); // Delay entre cada leitura
  
  // Lê o estado do reed switch e imprime no Serial Monitor
  int portaEstado = digitalRead(pinoSensorPorta);
  String portaStatus;
  
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

  // Lê o estado do sensor de presença e imprime no Serial Monitor
  int presencaEstado = digitalRead(pinoSensorPresenca);
  String presencaStatus;
  
  if (presencaEstado == HIGH) {
    presencaStatus = "Presença detectada";
    presencaDetectada = true;
  } else {
    presencaStatus = "Presença não detectada";
    presencaDetectada = false;
  }

  // Lê a valorUmidade e valorTemperatura e imprime no Serial Monitor
  float valorUmidade = dht.getHumidity();
  float valorTemperatura = dht.getTemperature();

  Serial.print("Umidade: ");
  Serial.print(valorUmidade);
  Serial.print("%\t");
  Serial.print("Temperatura: ");
  Serial.print(valorTemperatura, 1);
  Serial.print(" °C\t");
  Serial.print("Porta: ");
  Serial.print(portaStatus);
  Serial.print("\tPresença: ");
  Serial.print(presencaStatus);
  Serial.print("\tPresencaDetectada: ");
  Serial.println(presencaDetectada ? 1 : 0);
}
