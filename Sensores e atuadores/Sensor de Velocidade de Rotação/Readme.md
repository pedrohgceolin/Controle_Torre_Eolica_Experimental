# ESP32
![image](https://github.com/pedrohgceolin/Controle_Torre_Eolica_Experimental/blob/main/Sensores%20e%20atuadores/Sensor%20de%20Velocidade%20de%20Rota%C3%A7%C3%A3o/sensorencoder.jpeg)

O [encoder de rotação infravermelho](https://www.makerhero.com/img/files/download/LM393-Datasheet.pdf) é um sensor que usa luz infravermelha para detectar movimentos rotacionais. Ele é comum em sistemas de controle de posição e velocidade, como impressoras 3D, robôs e motores elétricos.
 ## Como Funciona:

Disco Codificado:
O encoder possui um disco com padrões de marcações (faixas claras e escuras).
O disco é acoplado a um eixo rotativo.

Sensor Infravermelho:
Um emissor de luz infravermelha ilumina o disco.
Um receptor infravermelho detecta a luz refletida ou bloqueada pelas faixas do disco.

Geração de Pulsos:
Quando o disco gira, as faixas claras e escuras alternam, criando uma sequência de pulsos elétricos.
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

Não foi necessário;

## Código:

```bash
#include <ESP32Encoder.h>

ESP32Encoder encoder;

#define CLK 22
#define DT  23

void setup() {
  Serial.begin(115200);
  
  encoder.attachHalfQuad(CLK, DT);  // Pinos CLK e DT
  
  encoder.setCount(0);
}

void loop() {
  int contagem = encoder.getCount();
  Serial.println(contagem);
  delay(1000);
}
```
## Resultados
Serial
![image](https://github.com/user-attachments/assets/d1ff3040-3b90-4c83-8bbc-ed7ff1ac0185)
