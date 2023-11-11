#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Claro_01919C"; // Cambia por el nombre de tu red Wi-Fi
const char* password = "P5K8H2P3B2A2"; // Cambia por la contraseña de tu red Wi-Fi

int ledPin = 2; // Pin al que está conectado el LED

ESP8266WebServer server(80);

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  Serial.begin(115200);

  // Conéctate a la red Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a la red Wi-Fi...");
  }
  Serial.println("Conexión exitosa a la red Wi-Fi");

  // Configura las rutas para encender y apagar el LED
  server.on("/", HTTP_GET, []() {
    server.send(200, "text/html", "<html><body><a href=\"/on\"><button>Encender LED</button></a> <a href=\"/off\"><button>Apagar LED</button></a></body></html>");
  });
  server.on("/on", HTTP_GET, []() {
    digitalWrite(ledPin, LOW);
    server.send(200, "text/html", "LED encendido. <a href=\"/\">Regresar</a>");
  });
  server.on("/off", HTTP_GET, []() {
    digitalWrite(ledPin, HIGH);
    server.send(200, "text/html", "LED apagado. <a href=\"/\">Regresar</a>");
  });

  server.begin();
}

void loop() {
  server.handleClient();
}
