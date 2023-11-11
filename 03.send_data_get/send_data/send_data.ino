#include <ESP8266WiFi.h>

const char* ssid = "Claro_01919C";   // Nombre de la red Wi-Fi a la que se conectará el ESP8266
const char* password = "P5K8H2P3B2A2";   // Contraseña de la red Wi-Fi

const char* server = "dgvesp8266.000webhostapp.com";
const int port = 80;

void setup() {
  // Conectarse a la red wifi
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a la red Wifi...");
  }
  Serial.println("Conectado a la red Wifi");
}

void loop() {
  String dato = "12345";

  WiFiClient client;

  if (client.connect(server, port)) {
    // Realiza la solicitud GET
    client.print("GET /conexionbdget.php?dato=");
    client.print(dato);
    client.println(" HTTP/1.1");
    client.print("Host: ");   
    client.println(server);
    client.println("Connection: close");
    client.println();

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.print(c);
      }
    }
    client.stop();
  } else {
    Serial.println("Error de conexión");
  }
  delay(10000);
}
