#include <ESP8266WiFi.h>

const char* ssid = "Claro_01919C";   // Nombre de la red Wi-Fi a la que se conectará el ESP8266
const char* password = "P5K8H2P3B2A2";   // Contraseña de la red Wi-Fi

const char* server = "dgvesp8266.000webhostapp.com";
const int port = 80;

String urlEncode(const String &value) {
    String encodedValue = "";
    char c;
    char code0;
    char code1;

    for (unsigned int i = 0; i < value.length(); i++) {
        c = value.charAt(i);
        if (c == ' ') {
            encodedValue += '+';
        } else if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            encodedValue += c;
        } else {
            code1 = (c & 0xf) + '0';
            if ((c & 0xf) > 9) {
                code1 = (c & 0xf) - 10 + 'A';
            }
            c = (c >> 4) & 0xf;
            code0 = c + '0';
            if (c > 9) {
                code0 = c - 10 + 'A';
            }
            encodedValue += '%';
            encodedValue += code0;
            encodedValue += code1;
        }
    }
    return encodedValue;
}


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
  String dato = "El desarrollo de Internet de las Cosas (IoT) es un campo apasionante que impulsa la convergencia "
               "de la tecnología y el mundo físico, permitiendo la interconexión de dispositivos, sensores y "
               "sistemas para recopilar datos, tomar decisiones inteligentes y mejorar la calidad de vida de las "
               "personas. A medida que el IoT continúa evolucionando, los ingenieros y desarrolladores están "
               "explorando nuevas formas de crear soluciones innovadoras que aborden una amplia variedad de "
               "desafíos, desde la automatización industrial y la gestión de la energía hasta la atención médica y la "
               "agricultura inteligente.\n"
               "La clave para el éxito en el desarrollo de IoT radica en la capacidad de diseñar dispositivos "
               "eficientes y seguros, desarrollar aplicaciones y plataformas que permitan la gestión y el análisis de "
               "datos a gran escala, y garantizar la interoperabilidad de dispositivos de diferentes fabricantes.\n"
               "Además, la seguridad cibernética se convierte en un aspecto crítico, ya que la proliferación de "
               "dispositivos conectados aumenta la superficie de ataque. La privacidad y la protección de datos "
               "también son preocupaciones fundamentales a medida que se recopilan y comparten grandes "
               "cantidades de información personal y sensible.\n"
               "Los avances en tecnologías como la conectividad 5G, la inteligencia artificial y el aprendizaje "
               "automático están impulsando aún más el potencial del IoT al permitir una mayor velocidad de "
               "transmisión de datos, análisis en tiempo real y toma de decisiones automatizadas. Esto da lugar a "
               "aplicaciones innovadoras como ciudades inteligentes que optimizan el tráfico y la gestión de "
               "recursos, sistemas de salud que supervisan a los pacientes de manera remota y agricultura de "
               "precisión que mejora la eficiencia de los cultivos.\n"
               "A medida que el IoT se expande, también plantea cuestiones éticas y regulatorias que deben "
               "abordarse cuidadosamente. La recopilación y el uso de datos, así como la toma de decisiones "
               "basadas en algoritmos, plantean preguntas sobre la transparencia, la equidad y la responsabilidad.\n"
               "Los gobiernos y las organizaciones están trabajando en la elaboración de marcos normativos y "
               "estándares que garanticen un desarrollo ético y seguro del IoT.\n"
               "En resumen, el desarrollo de IoT es un campo en constante evolución que promete transformar la "
               "forma en que interactuamos con el mundo que nos rodea. A medida que la tecnología avanza y se "
               "superan los desafíos, el IoT continuará mejorando la eficiencia, la comodidad y la sostenibilidad en "
               "una amplia gama de aplicaciones, brindando un futuro emocionante y conectado para la sociedad.";

  WiFiClient client;

  if (client.connect(server, port)) {
    // Realiza la solicitud GET
    String encodedDato = urlEncode(dato);

    client.print("GET /conexionbdget.php?dato=");
    client.print(encodedDato);
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
