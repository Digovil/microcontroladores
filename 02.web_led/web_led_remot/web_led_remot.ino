#include <ESP8266HTTPClient.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecureBearSSL.h>



const char* ssid = "Claro_01919C";   // Nombre de la red Wi-Fi a la que se conectará el ESP8266
const char* password = "P5K8H2P3B2A2";   // Contraseña de la red Wi-Fi
const char* valor = "";
int LED_2 = 2;

//pin

// URL del servidor donde se enviarán las lecturas del sensor
const char* serverName = "https://diplomadoiot.000webhostapp.com/api.php";

// Las siguientes variables son unsigned longs porque el tiempo, medido en milisegundos,
// se volverá rápidamente un número mayor que el que se puede almacenar en un int..
unsigned long lastTime = 0;
// Temporizador configurado para 5 segundos (5000 milisegundos)
unsigned long timerDelay = 100;

void setup() {
  Serial.begin(9600);

  pinMode(LED_2, OUTPUT);

  digitalWrite(LED_2, HIGH);

  // Conexión a la red Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {


  // Enviar una solicitud HTTP POST cada 5 segundos
  if ((millis() - lastTime) > timerDelay) {
    // Comprobar el estado de la conexión Wi-Fi
    if(WiFi.status()== WL_CONNECTED){
      // Crear un cliente HTTPS seguro
      std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
      // Ignorar la validación del certificado SSL
      client->setInsecure();
     
      // Crear una instancia de HTTPClient
      HTTPClient https;
     
      // Especificar el encabezado Content-Type
      https.begin(*client, serverName);

      // Send HTTP POST request
      int httpResponseCode = https.GET();

      //validar envio de la data
      if(httpResponseCode == 200){

        String response_body = https.getString();
        Serial.print("Server reply: ");
        Serial.println(response_body);

        if(response_body == "0"){
          digitalWrite(LED_2, HIGH);
          Serial.println("Apagado");
        }

        else if(response_body == "1"){
          digitalWrite(LED_2, LOW);
          Serial.println("Prendido");
        }

      }

      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      // Free resources
      https.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
