#include <WiFi.h>
#include <PubSubClient.h>
#include <ESP32Servo.h>
#include <ESP32Encoder.h>
#include <Preferences.h>

// WiFi
const char* ssid = "Ceolin PC";
const char* password = "12345678";

// MQTT
const char *mqtt_broker = "192.168.0.115"; // Pegar IP do broker no NODE-RED
const char *mqtt_username = "";
const char *mqtt_password = "";
const int mqtt_port = 1883; // porta padrão

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char *topic, byte *payload, unsigned int length);
void ligarMotorPitch (int direcao, int angulo);
void ligarMotorYAW (int direcao, int angulo);

// Variaveis globais dos sensores
String messageTemp;
int direcao_mqtt[10];
int conta_direcao = 0;
int velocidade;

//Variaveis dos atuadores
int yaw;
int pitch;

// variveis do sensor de rotação das pas
#define ENCODER_PIN_A 25  // Sinal do encoder

volatile long pulseCount = 0;
unsigned long lastTime;
float rpm_pas;
float rpm_pas_anterior;


void IRAM_ATTR handleEncoder() {
  pulseCount++;  // Incrementa pulsos ao detectar borda
}

// variveis dos servos
Servo servoPitch;
Servo servoYAW;
#define outputServopitch 2
#define outputServoYAW 4

// variveis dos encoder
ESP32Encoder encoderPitchLib;
ESP32Encoder encoderYAWLib;
int pitchTemp = 10;
unsigned long lastTimePitch;
unsigned long lastTimeYAW;
// Pinos CLK e DT
#define CLKpitch 22
#define DTpitch 23
#define CLKyaw 35
#define DTyaw 34

//Para salvar na memoria
Preferences preferences;

void setup() {
  
  Serial.begin(115200);
  preferences.begin("Turbina", false);
  unsigned int yaw_flash = preferences.getUInt("yaw_flash", 0);
  unsigned int pitch_flash = preferences.getUInt("pitch_flash", 45);
  yaw = yaw_flash;
  pitch = pitch_flash;
  servoPitch.attach(outputServopitch, 500, 2500);
  servoYAW.attach(outputServoYAW, 500, 2500);
  Serial.print("Pitch: ");
  Serial.println(pitch);
  Serial.print("YAW: ");
  Serial.println(yaw);

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
  //sensor velocidade das pas
   // Configura pinos do encoder de velocidade das pas
  pinMode(ENCODER_PIN_A, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_A), handleEncoder, RISING);

  lastTime = millis();
  lastTimeYAW = millis();
  lastTimePitch = millis();
  //encoder
  // Inicializa o encoder
  //ESP32Encoder::useInternalWeakPullResistors = UP;
  encoderPitchLib.attachHalfQuad(CLKpitch, DTpitch);  // Pinos CLK e DT
  encoderPitchLib.setCount(pitch);

  encoderYAWLib.attachHalfQuad(CLKyaw, DTyaw);  // Pinos CLK e DT
  encoderYAWLib.setCount(yaw);

  servoPitch.writeMicroseconds(1500);
  servoYAW.writeMicroseconds(1500);

  for(int i; i<10; i++){
    direcao_mqtt[i] = yaw;
  } 
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

  if(strcmp(topic, "metereologica/velocidade") == 0){
    velocidade = messageTemp.toInt();
  }
  if(strcmp(topic, "metereologica/direcao") == 0){
    direcao_mqtt[conta_direcao] = messageTemp.toInt();
    Serial.print("Direcao recebida[");
    Serial.print(conta_direcao);
    Serial.print("]:");
    Serial.println(direcao_mqtt[conta_direcao]);
    conta_direcao++;
    if(conta_direcao==10){
      conta_direcao = 0;
    }
  }

  client.publish("turbina/motorpitch", String("Motor desligado").c_str(), true);
  client.publish("turbina/motoryaw", String("Motor desligado").c_str(), true);
  client.publish("turbina/pitch", String(pitch).c_str(), true);
  client.publish("turbina/yaw", String(yaw).c_str(), true);


}

void loop() {
  Serial.println("Entrou loop");
  // MQTT
  client.loop();

  // Sensor velocidade das pas
  unsigned long currentTime = millis();
  velocidade_pas();

  if(currentTime - lastTimePitch >= 5000){
    log_pitch();
    lastTimePitch = currentTime;
  }

  client.publish("turbina/velocidade", String(rpm_pas).c_str(), true);

  if(currentTime - lastTimeYAW >= 5000){
    log_yaw();
    lastTimeYAW = currentTime;
  }
  delay(1000);
}

void velocidade_pas(){
  //Calcula RPM a cada 5 segundos
  unsigned long currentTime = millis();
  if (currentTime - lastTime >= 5000) {
    rpm_pas_anterior = rpm_pas;
    rpm_pas = ((float)pulseCount / 8) * 12.0;
    Serial.print("RPM: ");
    Serial.println(rpm_pas);
    pulseCount = 0;  // Reseta contador
    lastTime = currentTime;
  }
}

void log_pitch(){
  Serial.println("Entrou log Pitch");
  // Há possibilidade da pá estar nos angulos de 10, 25 e 45 graus, sendo que o angulod e 45 graus é oq a pa retira mais energia do vento.
  if (rpm_pas >=300 && pitch !=10){
    if(pitch==45){
      ligarMotorPitch(0,10);
    } else if (pitch==25){
      ligarMotorPitch(0,10);
    }
    pitch = 10;
  } 
  if(rpm_pas >=200 && rpm_pas <300 && pitch !=25){
    if(pitch==45){
      ligarMotorPitch(0,25);
    } else if (pitch==10){
      ligarMotorPitch(1,25);
    }
    pitch = 25;
  }
  if(rpm_pas < 100 && pitch !=45){
    if(pitch==25){
      ligarMotorPitch(1,45);
    } else if (pitch==10){
      ligarMotorPitch(1,45);
    }
    pitch = 45;
  }
}

void ligarMotorPitch (int direcao, int angulo){
  Serial.println("Entrou motor pitch");
  if (direcao==0){
    client.publish("turbina/motorpitch", String("Motor ligado. Sentido Horário").c_str(), true);
    servoPitch.writeMicroseconds(2000);
    encoderPitch(angulo);
    client.publish("turbina/motorpitch", String("Motor desligado").c_str(), true);
    servoPitch.writeMicroseconds(1500);
  } else if(direcao==1){
      client.publish("turbina/motorpitch", String("Motor ligado. Sentido Anti-Horário").c_str(), true);
      servoPitch.writeMicroseconds(1000);
      encoderPitch(angulo);
      client.publish("turbina/motorpitch", String("Motor desligado").c_str(), true);
      servoPitch.writeMicroseconds(1500);
  }
}

void encoderPitch(int x){
  Serial.println("Entrou encoder Pitch");
  while (encoderPitchLib.getCount()!=x){
    int valor = encoderPitchLib.getCount();
    Serial.println("Pitch em:");
    Serial.println(valor);
    // Publica no tópico MQTT
    client.publish("turbina/pitch", String(valor).c_str(), true);
    delay(500);
  }
  preferences.putUInt("pitch_flash", pitch);
  delay(100);  // Atualização lenta para leitura
}

void log_yaw(){
  Serial.println("Entrou log YAW =");
  int soma = 0;
  for(int i = 0; i<10; i++){
    soma = soma + direcao_mqtt[i];
    Serial.print("Soma loop =");
    Serial.println(soma);
  }
  soma = soma/10;
  Serial.print("Soma YAW =");
  Serial.println(soma);
  if (soma != yaw){
    if(soma-yaw > 5){
      ligarMotorYAW(0,soma);
    }
    if(soma-yaw < -5){
      ligarMotorYAW(1,soma);
    }
  }
}

void ligarMotorYAW (int direcao, int angulo){
  Serial.println("Entrou motor YAW");
   if (direcao==0){
    client.publish("turbina/motoryaw", String("Motor ligado. Sentido Horário").c_str(), true);
    servoYAW.writeMicroseconds(2000);
    encoderYAW(angulo);
    client.publish("turbina/motoryaw", String("Motor desligado").c_str(), true);
    servoYAW.writeMicroseconds(1500);
   } else if(direcao==1){
    client.publish("turbina/motoryaw", String("Motor ligado. Sentido Antti-Horário").c_str(), true);
    servoYAW.writeMicroseconds(1000);
    encoderYAW(angulo);
    client.publish("turbina/motoryaw", String("Motor desligado").c_str(), true);
    servoYAW.writeMicroseconds(1500);
   }
}

void encoderYAW (int x){
  Serial.print("Entrou encoder YAW =");
  Serial.println(x);
  while (encoderYAWLib.getCount()!=x){
    yaw = encoderYAWLib.getCount();
    Serial.println("YAW em:");
    Serial.println(yaw);
    // Publica no tópico MQTT
    client.publish("turbina/yaw", String(yaw).c_str(), true);
    delay(500);
  }
  preferences.putUInt("yaw_flash", yaw);
  delay(100);  // Atualização lenta para leitura
}

