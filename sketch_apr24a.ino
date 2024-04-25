#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "DHTesp.h"

DHTesp dht;
const int pinoSensorPorta = 5;    // Pino onde o reed switch está conectado
const int pinoBuzzer = 4;  // Pino do buzzer

const char* ssid = "Ti-2G";
const char* password = "Sup4@test";

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
    // Desliga o buzzer quando a porta está fechada
    digitalWrite(pinoBuzzer, HIGH);
  } else {
    portaStatus = "Fechada";
    // Liga o buzzer quando a porta está aberta
    digitalWrite(pinoBuzzer, LOW);
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
                   "Porta: " + portaStatus + "\n";
  
  server.send(200, "text/plain", valorMonitoramento);

  // Escreve os valores lidos no Serial Monitor
  Serial.print("Umidade: ");
  Serial.print(valorUmidade);
  Serial.print("%\t");
  Serial.print("Temperatura: ");
  Serial.print(valorTemperatura, 1);
  Serial.print(" °C\t");
  Serial.print("Porta: ");
  Serial.println(portaStatus);
}

void handleNotFound(){
  String valorMonitoramento = "Página não encontrada\n";
  server.send(404, "text/plain", valorMonitoramento);
}

void setup(void){
  Serial.begin(9600);
  dht.setup(14, DHTesp::DHT11); // D5
  pinMode(pinoSensorPorta, INPUT_PULLUP); // Configura o pino do reed switch como entrada
  pinMode(pinoBuzzer, OUTPUT);  // Configura o pino do buzzer como saída
  
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
    // Desliga o buzzer quando a porta está fechada
    digitalWrite(pinoBuzzer, HIGH);
  } else {
    portaStatus = "Fechada";
    // Liga o buzzer quando a porta está aberta
    digitalWrite(pinoBuzzer, LOW);
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
  Serial.println(portaStatus);
}
