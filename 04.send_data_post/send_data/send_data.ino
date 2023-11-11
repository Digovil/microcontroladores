#include <ESP8266WiFi.h>

const char* ssid = "Claro_01919C";
const char* password = "P5K8H2P3B2A2";

const char* server = "dgvesp8266.000webhostapp.com";
const int port = 80;

void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a la red Wifi...");
  }
  Serial.println("Conectado a la red Wifi");
}

void loop() {
  String dato = "dato=77";

  WiFiClient client;

  if (client.connect(server, port)) {
    // Realiza la solicitud POST
    client.println("POST /conexionbdpost.php HTTP/1.1");
    client.println("Host: " + String(server));
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Content-Length: " + String(dato.length()));
    client.println();
    client.println(dato);

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
