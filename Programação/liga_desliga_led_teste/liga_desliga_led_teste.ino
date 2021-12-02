void setup() 
{ 
  pinMode(D1,OUTPUT);
  Serial.begin(115200);
  Serial.println("Estado do led");
}
void loop() 
{ 
   digitalWrite(D1,HIGH);
   Serial.println("Ligado");
   delay(1500);  
   digitalWrite(D1,LOW);
   Serial.println("Desligado");   
   delay(1500);
}
