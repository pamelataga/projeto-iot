#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];  


//DHT Area
#define DHTPIN D5 // pin do DHT que conecta
#define DHTTYPE DHT22 // versão do DHTset the DHT version
DHT dht(DHTPIN, DHTTYPE); // Declara o objeto DHT 
int t,h; //variaveis para temperatura e humidade 
char sala;

//Wifi area
const char* ssid = "2.4G PAMELA"; // nome da rede wifi 
const char* password = "393545339"; // senha da rede wifi 
const char* mqtt_broker = "mqtt.eclipseprojects.io"; // MQTT Broker utilizado
WiFiClient nodemcuClient;
PubSubClient client(nodemcuClient);

void setup() {
  sala = D1;
  Serial.begin(9600);
  dht.begin(); // inicializa o dht
  Serial.println("\n\n***************************************");
  Serial.println(" Iniciacizando o termometro IoT ...");
  wifi_connect();
  client.setServer(mqtt_broker,1883); // MQTT server e porta
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(D1, OUTPUT);// 
}

void loop() {
  if (!client.connected()) {
    reconnect_MQTT();
  }
  DHT_readings();
  publish_MQTT();
  delay(5000);
}

//função estabelece conexao com rede wifi 
void wifi_connect(){
  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  digitalWrite(LED_BUILTIN,HIGH);
  Serial.println("***************************************\n\n");
}

//reestabelece conexao com MQTT broker
void reconnect_MQTT(){
  while (!client.connected()) {
    client.connect("IoT_Termometer");
    Serial.println("Reconnecting MQTT...");
  }
}

void callback(char* topic, byte* payload, unsigned int length) {                                  
  Serial.print("Mensagem recebida [");                                                            
  Serial.print(topic);                                                                            
  Serial.print("] ");                                                                             
  for (int i = 0; i < length; i++) {                                                              
    Serial.print((char)payload[i]);                                                               
  }
  Serial.println("");                                                                             
  if ((char)payload[0] == '1') {                                                                  
    digitalWrite(sala, HIGH);                                                                     
    snprintf (msg, MSG_BUFFER_SIZE, "A luz da sala está ligada");                                 
    Serial.print("Publica mensagem: ");                                                           
    Serial.println(msg);                                                                          
    client.publish("casa/sala", msg);                                                             
  }
  Serial.println("");                                                                             
  if ((char)payload[0] == '0') {                                                                  
    digitalWrite(sala, LOW);                                                                      
    snprintf (msg, MSG_BUFFER_SIZE, "A luz da sala está desligada");                              
    Serial.print("Publica mensagem: ");                                                           
    Serial.println(msg);                                                                          
    client.publish("casa/sala", msg);                                                             
  }
}

// Função para ler temperatura e exibir resultados 
void DHT_readings(){
  // Reading temperature or humidity takes about 250 milliseconds!
  h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  //float f = dht.readTemperature(true);

  // verifica se a leitura deu errada, exibe mensagem e tenta novamente
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

}

// Função publish readings no MQTT 
void publish_MQTT(){
  // persiste informação no topico 
  client.publish("lab/temp", String(t).c_str(), true); // pode alterar o topico
  client.publish("lab/humid", String(h).c_str(), true); // pode alterar o topico

  // imprime as mensagens e leituras 
  Serial.println("\n---------------------------------------");
  Serial.println("Leitura de Temperatura e Humidade: \n");
  Serial.print(F("Humidade: "));
  Serial.print(h);
  Serial.print(F("%  Temperatura: "));
  Serial.print(t);
  Serial.println(F("°C "));

  // exibe a publicação com sucesso no topic mqtt 
  digitalWrite(LED_BUILTIN, LOW);
  delay(200);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);
  delay(200);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);
}
