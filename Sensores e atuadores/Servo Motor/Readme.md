# Servo Motor
![image](https://github.com/pedrohgceolin/Controle_Torre_Eolica_Experimental/blob/main/Sensores%20e%20atuadores/Servo%20Motor/servomotor.jpeg)

Um servo motor rotativo é um tipo de motor que realiza movimento rotacional contínuo ou em ângulos limitados, dependendo de sua configuração. Ele é usado em aplicações que exigem controle preciso de posição, velocidade ou torque, sendo comum em robótica, automação industrial e sistemas de controle.

##Como Funciona um Servo Motor Rotativo
Sinal de Controle (PWM):
Recebe um sinal PWM (Modulação por Largura de Pulso).
A largura do pulso determina a posição (para servo de rotação limitada) ou a direção e velocidade (para rotação contínua).

Feedback Interno:
Um potenciômetro interno mede a posição do eixo (nos de rotação limitada).
Um circuito de controle compara a posição atual com a desejada e ajusta o motor.

Motor e Engrenagens:
Um motor DC ou AC aciona um conjunto de engrenagens para aumentar o torque e reduzir a velocidade.

## Especificações
| Pino                                | Pino no ESP32                     |
|-------------------------------------|-----------------------------------|
| VCC                                 | Vin                               |
| GND                                 | GND                               |
| D0                                  | 2                                 | 

## Bibliotecas

```bash
#include <ESP32Servo.h>
```

## Código:

```bash
#include <ESP32Servo.h>

Servo servoPitch;

#define outputServopitch 2

void setup() {
  Serial.begin(115200);
  servoPitch.attach(outputServopitch, 500, 2500);
}

void loop() {
  servoPitch.writeMicroseconds(1500);
  Serial.println("Parado");
  delay(2000);
  servoPitch.writeMicroseconds(2500);
  Serial.println("Horario");
  delay(2000);
  servoPitch.writeMicroseconds(1500);
  Serial.println("Parado");
  delay(2000);
  servoPitch.writeMicroseconds(500);
  Serial.println("Anti-Horario");
  delay(2000);
}
```
## Resultados
Serial
![image](https://github.com/user-attachments/assets/ef0a3af2-5cb4-4032-b228-2658738b72c6)

