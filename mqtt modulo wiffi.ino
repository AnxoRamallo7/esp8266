#include <ESP8266WiFi.h>
#include <Servo.h>
#include <PubSubClient.h>



//WIFI MOBIL
#define MAX_INTENTOS 50
#define WIFI_SSID "robotica"
#define WIFI_PASS "pass"


//MQTT
//Datos MQTTHQ broker en mqtthq.com
//URL : public.mqtthq.com // TCP Port: 1883
//WebSocket Port: 8083
//WebSocket Path: /mqtt
#define MQTT_HOST IPAddress (52, 13, 116, 147)
#define MQTT_PORT 1883


//Servo
#define SERVOPIN 0 // PIN D3
Servo servo;
#define MQTT_PUB_SERVO "wemos/robotica/servo"
#define MQTT_NOME_CLIENTE "Cliente servo"


WiFiClient espClient;
PubSubClient mqttClient(espClient);


//pins datos
//GPI014: d5

#define LED 14
  int tempo = 500;
  bool conectado = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  servo.attach(SERVOPIN);
  conectado = conectarWiFi();
  mqttClient.setServer(MQTT_HOST, MQTT_PORT);
  mqttClient.setCallback(callback);
  conectarWiFi();
}


void loop() {
  // put your main code here, to run repeatedly:
   if(conectado) escintila(tempo);
   else escintila(tempo/10);
}


void escintila(int espera) {
  digitalWrite(LED, HIGH);
  delay(espera);
  digitalWrite(LED, LOW);
  delay(espera);
  }





//funcion que se encarga de gestionar la conexion a la red
bool conectarWiFi() {
   WiFi.mode(WIFI_STA);      // indica modo station (conexion a otro dispositivo)
   WiFi.disconnect();        // desconecta una posible conexion previa
   WiFi.begin(WIFI_SSID, WIFI_PASS);   /// indica la conexion
   Serial.print("\n\nAgardando pola WiFi ");
   int contador = 0;         //comprueba el estado de la conexion y hace varias tentativas 
   while(WiFi.status() !=WL_CONNECTED and contador < MAX_INTENTOS) {
     contador++;
     delay(500);
     Serial.print(".");
  }

   Serial.println(".");
   //informa del estado de la conexion e ip en caso de exito
   if(contador < MAX_INTENTOS) {
     Serial.print("Conectado ó WiFi con IP: "); Serial.println(WiFi.localIP());
     conectado = true; 
   }

   else {
    Serial.println("no se puede conectar a wifi");
    conectado = false;
   }
   return(conectado);
}

void callback(String topic, byte* message, unsigned int len) {
  Serial.print("Received on ");
  Serial.print(topic);
  Serial.print(": ");

  topic = "";  
  for (size_t i = 0; i < len; i++) {
    topic.concat((char)message[i]);
  }
  Serial.print(topic);
  Serial.println();
}

