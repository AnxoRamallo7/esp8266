#include <ESP8266WiFi.h>

//Wifi móbil
#define MAX_INTENTOS 50
#define WIFI_SSID "ssd"
#define WIFI_PASS "pass"

// Pins datos
// GPIO14: D5
#define LED 14
int tempo = 500;
bool conectado = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  pinMode(LED, OUTPUT);
  conectado = conectarWiFi();
}

void loop() {
  if(conectado) escintila(tempo);
  else escintila(tempo/10);
}

void escintila(int espera) {
  digitalWrite(LED, HIGH);
  delay(espera);
  digitalWrite(LED, LOW);
  delay(espera);
}

// Función que se encarga de xestionar a conexión á rede
bool conectarWiFi() { 
  WiFi.mode(WIFI_STA);
  WiFi.disconnect(); 
  WiFi.begin(WIFI_SSID, WIFI_PASS); 
  Serial.print("\n\nAgardando pola WiFi "); 
  int contador = 0;
  while(WiFi.status() != WL_CONNECTED and contador < MAX_INTENTOS) {
    contador++;
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  // Informa do estado da conexion e IP en caso de éxito
  if(contador < MAX_INTENTOS) {
    conectado = true;
    Serial.print("Conectado á WiFi coa IP: "); Serial.println(WiFi.localIP());
  }
  else{
    Serial.println("Non se puido conectar á WiFi");
    conectado = false;
  }
  return(conectado); 
}
