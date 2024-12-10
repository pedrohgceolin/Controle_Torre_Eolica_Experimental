# Encoder Rotativo HW-040
![image-removebg-preview (1)](https://github.com/pedrohgceolin/Controle_Torre_Eolica_Experimental/blob/main/Sensores%20e%20atuadores/Encoder%20Rotativo%20HW-040/encoderW040.jpeg)

O [Encoder incremental HW-040](https://github.com/pedrohgceolin/Controle_Torre_Eolica_Experimental/blob/main/Sensores%20e%20atuadores/Encoder%20Rotativo%20HW-040/Rotary%20Encoder.pdf) é um dispositivo usado para medir posição, velocidade ou direção de movimento em sistemas eletromecânicos. Ele é comum em aplicações como automação industrial, controle de motores e sistemas robóticos.

## Funcionamento Básico:
Um encoder converte movimento rotacional ou linear em sinais elétricos. Esses sinais são usados por controladores para monitorar e ajustar a posição ou velocidade de um motor ou eixo, neste caso, está sendo usado para monitorara as posições do pitch e do yaw da torre.

## Especificações do encoder do pitch
| Pino                                | Pino no ESP32
|-------------------------------------|-----------------------------------|
| GND                                 | GND                               |
| +                                   | 3V3                               |
| SW                                  | Não Utilizado                     | 
| DT                                  | 22                                |
| CLK                                 | 21                                |

## Especificações do encoder do yaw
| Pino                                | Pino no ESP32
|-------------------------------------|-----------------------------------|
| GND                                 | GND                               |
| +                                   | 3V3                               |
| SW                                  | Não Utilizado                     | 
| DT                                  | 35                                |
| CLK                                 | 34                                |
