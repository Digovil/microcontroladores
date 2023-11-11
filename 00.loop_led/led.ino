

/*
 
  Mi primer programa :'D

*/

void setup() {

  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}


void loop() {
  digitalWrite(LED_BUILTIN, HIGH); 
  Serial.println("Apagado");  
  delay(3000);                       
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("Encendido");     
  delay(3000);                       
}
