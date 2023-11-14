#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <WebSocketsServer.h>
#include <EEPROM.h>
#include <ArduinoJson.h>  

// Define addresses in EEPROM for storing credentials
#define EEPROM_SSID_ADDR 0
#define EEPROM_PASS_ADDR 32

// Definir variables para almacenar las credenciales WiFi
char custom_ssid[32] = "";
char custom_password[32] = "";

const char* url = "dgvesp8266.000webhostapp.com";
const int port = 80;

// Define a structure to store client information
struct ClientInfo {
  uint8_t id;
  IPAddress ip;
};

const uint8_t MAX_CLIENTS = 5;  // Maximum number of clients
ClientInfo clients[MAX_CLIENTS];  // List of connected clients

WebSocketsServer webSocket = WebSocketsServer(81);
ESP8266WebServer server(80);

void sendToAllConnectedClients(const char* message) {
  for (uint8_t i = 0; i < webSocket.connectedClients(); i++) {
    webSocket.sendTXT(i, message);
  }
}

uint8_t getClientIdByIP(IPAddress ip) {
  for (int i = 0; i < MAX_CLIENTS; i++) {
    if (clients[i].ip == ip) {
      return clients[i].id;
    }
  }
  return 0;
}

void handleRoot() {
  String html = "<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta http-equiv='X-UA-Compatible' content='IE=edge'><meta name='viewport' content='width=device-width, initial-scale=1.0'><script src='https://kit.fontawesome.com/391827d54c.js' crossorigin='anonymous'></script><link rel='stylesheet' href='styles.css'><title>Whatsapp Clone</title><style>*{margin:0;padding:0;box-sizing:border-box;font-family:'Poppins',sans-serif;}body{display:flex;justify-content:center;align-items:center;min-height:100vh;background:#ccc;}.background-green{position:absolute;top:0;width:100%;height:20%;background-color:#009688;}.main-container{position:relative;width:100%;max-width:100%;height:100vh;background:#fff;display:flex;box-shadow:0px 1px 1px 0 rgba(0,0,0,0.5),0px 2px 5px 0 rgba(0,0,0,0.6);}.main-container .left-container{position:relative;width:30%;height:100%;flex:30%;background:#fff;}.main-container .right-container{position:relative;width:70%;height:100%;flex:70%;background:#e5ddd5;}.main-container .right-container::before{content:'';position:absolute;top:0;left:0;width:100%;height:100%;background:url('https://camo.githubusercontent.com/854a93c27d64274c4f8f5a0b6ec36ee1d053cfcd934eac6c63bed9eaef9764bd/68747470733a2f2f7765622e77686174736170702e636f6d2f696d672f62672d636861742d74696c652d6461726b5f61346265353132653731393562366237333364393131306234303866303735642e706e67');opacity:0.5;}.user-img{position:relative;width:40px;height:40px;overflow:hidden;border-radius:50%;}.dp{position:absolute;top:0;left:0;width:100%;height:100%;object-fit:cover;cursor:pointer;}.nav-icons{display:flex;justify-content:flex-end;padding-left:110px;}.nav-icons li{backgroud-color:pink;list-style:none;display:flex;cursor:pointer;color:#51585c;margin-left:22px;font-size:18px;}.chat-list{position:relative;height:calc(100% - 170px);overflow-y:auto;}.chat-list .chat-box{position:relative;width:100%;display:flex;align-items:center;cursor:pointer;padding:15px;border-bottom:1px solid #eee;}.chat-list .chat-box .img-box{position:relative;width:55px;height:45px;overflow:hidden;border-radius:50%;}.chat-list .chat-box .chat-details{width:100%;margin-left:10px;}.chat-list .chat-box .chat-details .text-head{display:flex;justify-content:space-between;align-items:center;margin-bottom:2px;}.chat-list .chat-box .chat-details .text-head h4{font-size:1.1em;font-weight:600;color:#000;}.chat-list .chat-box .chat-details .text-head .time{font-size:0.8em;color:#aaa;}.chat-list .chat-box .chat-details .text-message{display:flex;justify-content:space-between;align-items:center;}.chat-list .chat-box .chat-details .text-message p{color:#aaa;font-size:0.9em;overlay:hidden;}.chat-list .chat-box .chat-details .text-message b{background:#06e744;color:#fff;min-width:20px;height:20px;border-radius:50%;font-size:0.8em;font-weight:400;display:flex;justify-content:center;align-items:center;}.chat-list .active{background:#ebebeb;}.chat-list .chat-box:hover{background:#f5f5f5;}.chat-list .chat-box .chat-details .text-head .unread{color:#06e744;}.chat-container{position:relative;width:100%;height:calc(100% - 60px);padding:50px;overflow-y:auto;}.message-box{position:relative;display:flex;width:100%;margin:5px 0;}.message-box p{position:relative;right:0;text-align:right;max-width:65%;padding:12px;background:#dcf8c6;border-radius:10px;font-size:0.9em;}.message-box.my-message p::before{content:'';position:absolute;top:0;right:-12px;width:20px;height:20px;background:linear-gradient(135deg,#dcf8c6 0%,#dcf8c6 50%,transparent 50%,transparent);}.message-box p span{display:block;margin-top:5px;font-size:0.8em;opacity:0.5;}.my-message{justify-content:flex-end;}.friend-message p{background:#fff;}.friend-message{justify-content:flex-start;}.chat-container .my-message i{color:yellow;}.message-box.friend-message::before{content:'';position:absolute;top:0;left:-12px;width:20px;height:20px;background:linear-gradient(225deg,#fff 0%,#fff 50%,transparent 50%,transparent);}.chatbox-input{position:relative;width:100%;height:60px;background:#f0f0f0;display:flex;justify-content:space-between;align-items:center;}.chatbox-input i{cursor:pointer;font-size:1.8em;color:#515855;}.chatbox-input i:nth-child(1){margin:15px;}.chatbox-input i:last-child{margin-right:25px;}.chatbox-input input{position:relative;width:90%;margin:0 20px;padding:10px 20px;border-radius:10px;font-size:1em;border:none;outline:none;}</style></head><body><div class='main-container'><div class='right-container'><div class='chat-container'><div id='messages'></div></div><div class='chatbox-input'><input type='text' placeholder='Type a message' id='messageInput'><i class='fa-solid fa-paper-plane'  onclick='sendMessage()'></i></div></div></div><script>const socket=new WebSocket('ws://" + WiFi.localIP().toString() + ":81/');let codigo=null;socket.addEventListener('open',(event)=>{console.log('Conexión establecida ',event);});socket.addEventListener('message',(event)=>{console.log('Mensaje recibido:',event.data);let data=JSON.parse(event.data);if(!data.message){codigo=data.clientCode;}console.log('codigo: ',codigo);console.log('data.clientCode: ',data.clientCode);if(codigo==null||!data.message)return;if(codigo===data.clientCode){const messagesDiv=document.getElementById('messages');messagesDiv.innerHTML+=`<div class='message-box my-message'><p>${data.message}<br><span>${new Date().toLocaleTimeString('es-ES',{hour12:false,hour:'2-digit',minute:'2-digit'})}</span></p></div>`;}else{const messagesDiv=document.getElementById('messages');messagesDiv.innerHTML+=`<div class='message-box friend-message'><p>${data.message}<br><span>${new Date().toLocaleTimeString('es-ES',{hour12:false,hour:'2-digit',minute:'2-digit'})}</span></p></div>`;}});socket.addEventListener('close',(event)=>{console.log('Conexión cerrada');});function sendMessage(){const messageInput=document.getElementById('messageInput');const message=messageInput.value;console.log('Enviando el mensaje: ');socket.send(message);messageInput.value='';}</script></body></html>";
  server.send(200, "text/html", html);
}


void webSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Desconectado!\n", num);
      // Liberar el identificador del cliente desconectado
      for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].id == num) {
          clients[i].id = 0;
          break;
        }
      }
      break;
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Conectado desde %d.%d.%d.%d\n", num, ip[0], ip[1], ip[2], ip[3]);

        // Asignar un identificador único al cliente
        for (int i = 0; i < MAX_CLIENTS; i++) {
          if (clients[i].id == 0) {
            clients[i].id = num;
            clients[i].ip = ip;

            // Enviar el código del cliente al propio cliente
            DynamicJsonDocument doc(256);
            doc["clientCode"] = num;
            String jsonString;
            serializeJson(doc, jsonString);
            webSocket.sendTXT(num, jsonString);

            break;
          }
        }
      }
      break;
    case WStype_TEXT:
      Serial.printf("[%u] Recibido texto: %s\n", num, payload);

      // Obtener el identificador del cliente que envió el mensaje
      uint8_t senderId = getClientIdByIP(webSocket.remoteIP(num));

      // Crear un objeto JSON para enviar
      DynamicJsonDocument doc(256);
      doc["sender"] = senderId;
      doc["clientCode"] = num;  // Agregamos el código del cliente propio
      doc["message"] = reinterpret_cast<char*>(payload);

      // Serializar el objeto JSON a una cadena
      String jsonString;
      serializeJson(doc, jsonString);

      // Enviar el mensaje serializado a todos los clientes conectados
      sendToAllConnectedClients(jsonString.c_str());
      break;
  }
}

void setup() {
  Serial.begin(115200);


  // Intentar leer las credenciales almacenadas
  readCredentials(custom_ssid, custom_password);

  // Inicializar WiFiManager
  WiFiManager wifiManager;

  // Agregar campos personalizados para las credenciales WiFi
  WiFiManagerParameter custom_ssid_param("ssid", "SSID", custom_ssid, 32);
  WiFiManagerParameter custom_password_param("password", "Contraseña", custom_password, 32);

  wifiManager.addParameter(&custom_ssid_param);
  wifiManager.addParameter(&custom_password_param);

  // Intentar conectar con las credenciales almacenadas o abrir el portal cautivo
  if (!wifiManager.autoConnect("MiDispositivoAP")) {
    Serial.println("No se pudo establecer conexión y tiempo de espera alcanzado.");
    delay(3000);
    // Reiniciar para volver a intentar la conexión
    ESP.reset();
    delay(5000);
  }



  // Guardar las nuevas credenciales ingresadas
  saveCredentials(custom_ssid_param.getValue(), custom_password_param.getValue());

  // Imprimir la dirección IP asignada
  Serial.println("Conexión exitosa a la red Wi-Fi");
  Serial.println(WiFi.localIP());

  String dato = "dato="+WiFi.localIP().toString();

  WiFiClient client;

  if (client.connect(url, port)) {
    // Realiza la solicitud POST
    client.println("POST /conexionbdposturl.php HTTP/1.1");
    client.println("Host: " + String(url));
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

  // Inicializar servidor WebSocket
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

  // Manejar la ruta raíz y servir la página HTML
  server.on("/", HTTP_GET, handleRoot);

  // Iniciar el servidor HTTP
  server.begin();
}

void loop() {
  webSocket.loop();
  server.handleClient();
}

// Funciones para el almacenamiento en EEPROM
void saveCredentials(const char* ssid, const char* password) {
  EEPROM.begin(512);
  EEPROM.put(EEPROM_SSID_ADDR, ssid);
  EEPROM.put(EEPROM_PASS_ADDR, password);
  EEPROM.commit();
  EEPROM.end();
}

void readCredentials(char* ssid, char* password) {
  EEPROM.begin(512);
  EEPROM.get(EEPROM_SSID_ADDR, ssid);
  EEPROM.get(EEPROM_PASS_ADDR, password);
  EEPROM.end();
}
