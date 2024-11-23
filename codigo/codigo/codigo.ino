#include <WiFi.h>
#include <PubSubClient.h>


// WiFi
const char* ssid = "";
const char* password = "";

// MQTT
const char *mqtt_broker = "localhost"; // Pegar IP do broker no NODE-RED
const char *mqtt_username = "";
const char *mqtt_password = "";
const int mqtt_port = 1883; // porta padrão

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char *topic, byte *payload, unsigned int length);

// Variaveis globais dos sensores
String messageTemp;
int direcao;
int velocidade;

void setup() {
  
  Serial.begin(115200);

  //Conexao WiFi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

  // Conectando ao Broker
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected()) {
    String client_id = "esp32-";
    client_id += String(WiFi.macAddress());
    Serial.printf("O cliente %s se conectou ao broker\n", client_id.c_str());
    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("Conectado com usuario e senha");
    } else {
      Serial.print("Falhou com o codigo: ");
      Serial.print(client.state());
      delay(2000);
    }
  }

  // Sensores

  // Recebendo dados dos sensores
  // Anemometro
  client.subscribe("metereologica/velocidade");
  //biruta
  client.subscribe("metereologica/direcao");

}

void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Mensagem chegou no topico: ");
  Serial.println(topic);
  Serial.print("Mensagem:");
  messageTemp = "";
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    messageTemp += (char)payload[i];
  }
  Serial.println();
  Serial.println("-----------------------");

  if(topic == "metereologica/velocidade"){
    velocidade = messageTemp.toInt();
  }
  if(topic == "metereologica/direcao"){
    direcao = messageTemp.toInt();
  }
}

void loop() {
  // MQTT
  client.loop();
}
