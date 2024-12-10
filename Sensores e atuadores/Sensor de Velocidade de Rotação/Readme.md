# ESP32
![image](https://github.com/pedrohgceolin/Controle_Torre_Eolica_Experimental/blob/main/Sensores%20e%20atuadores/Sensor%20de%20Velocidade%20de%20Rota%C3%A7%C3%A3o/sensorencoder.jpeg)

O [encoder de rotação infravermelho](https://www.makerhero.com/img/files/download/LM393-Datasheet.pdf) é um sensor que usa luz infravermelha para detectar movimentos rotacionais. Ele é comum em sistemas de controle de posição e velocidade, como impressoras 3D, robôs e motores elétricos.
 ## Como Funciona:

Disco Codificado:
O encoder possui um disco com padrões de marcações (buracos).
O disco é acoplado a um eixo rotativo.

Sensor Infravermelho:
Um emissor de luz infravermelha ilumina o disco.
Um receptor infravermelho detecta a luz bloqueada ou que passou pelas faixas do disco.

Geração de Pulsos:
Quando o disco gira, a luz que passa e a que é bloqueada se alternam, criando uma sequência de pulsos elétricos.
A frequência desses pulsos indica a velocidade de rotação.
A ordem dos pulsos em dois canais (A e B) indica a direção do movimento.

## Especificações
| Pino                                | Pino no ESP32                     |
|-------------------------------------|-----------------------------------|
| VCC                                 | 3V3                               |
| GND                                 | GND                               |
| D0                                  | 25                                | 
| A0                                  | Não Utilizado                     |

## Bibliotecas

Não foi necessário.

## Código:

```bash
#define ENCODER_PIN_A 25  // Sinal do encoder

volatile long pulseCount = 0;
unsigned long lastTime;
float rpm;

void IRAM_ATTR handleEncoder() {
  pulseCount++;  // Incrementa pulsos ao detectar borda
}

void setup() {
  Serial.begin(115200);

  pinMode(ENCODER_PIN_A, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_A), handleEncoder, RISING);
  
  lastTime = millis();
  
}

void loop() {
  //Calcula RPM a cada segundo
  unsigned long currentTime = millis();
  if (currentTime - lastTime >= 1000) {
    rpm = ((float)pulseCount / 8) * 12.0;
    Serial.print("RPM: ");
    Serial.println(rpm);
    pulseCount = 0;  // Reseta contador
    lastTime = currentTime;
  }
}
```
## Resultados
Serial
![image](https://github.com/user-attachments/assets/5f771697-e281-48d8-8a01-cc1cd6010aac)
