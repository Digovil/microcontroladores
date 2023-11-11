

/*
 Configuración imperativa del microcontrolador nodemcu
 en loop led
*/

int pinled=2; // D4

void setup() {

  Serial.begin(9600);
  pinMode(pinled, OUTPUT);
}


void loop() {
  digitalWrite(pinled, HIGH); 
  Serial.println("Apagado v2");  
  delay(3000);                       
  digitalWrite(pinled, LOW);
  Serial.println("Encendido v2");     
  delay(3000);                       
}
