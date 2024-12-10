# Sistema de Controle de uma Torre Eolica Experimental com ESP32

## Proposta

O objetivo deste trabalho é desenvolver um sistema de controle e gerenciamento para uma torre eólica experimental, utilizando exclusivamente dados recebidos de sensores. O sistema será responsável por processar informações de direção e velocidade do vento, fornecidas por sensores instalados na torre, e, com base nesses dados, ajustar de forma automatizada a posição da nacele e o ângulo das pás. Além disso, o sistema de controle irá medir a rotação das pás, sincronizando-a com a velocidade do gerador, garantindo que o gerador opere em sua faixa de eficiência máxima. O foco do projeto é a otimização do desempenho da torre eólica através de um controle preciso, utilizando dados em tempo real, sem a necessidade de intervenções manuais ou ajustes de hardware.

## Arquitetura do Projeto:

O projeto segue uma arquitetura onde o ESP32 coleta dados dos sensores e posiciona a nacele e os angulos das pás de acordo com os dados coletados. Além do controle, o ESP32 enviará esses dados coletados via protocolo MQTT para plataforma NODE-RED, que recebe os dados e os exibe em um dashboard, permitindo o monitoramento do sistema.

![image](https://github.com/user-attachments/assets/5903ac94-45bb-4f5f-aa36-ad93eabd69e4)

## Hardware:

### Visão Geral

O sistema utiliza o microcontrolador ESP32 como núcleo principal para coletar dados de sensores, processá-los e controlar atuadores. Sensores como anemômetro, sensor de direção do vento e medidor de RPM fornecem informações para ajustar automaticamente a posição da nacele e o ângulo das pás, otimizando a eficiência da torre eólica. Atuadores são usados para alinhar a nacele e modificar o ângulo das pás conforme necessário. Além disso, o sistema conta com comunicação via MQTT para enviar dados ao dashboard no Node-RED, permitindo o monitoramento remoto.

### Componentes Utilizados:

- [ESP-32 DevKitV1 (microcontrolador)]()
- [Encoder Rotativo W-040]()
- [Sensor de Velocidade de Rotação Infra-Vermelho ]()
- [Servo Motor SM-S4306R]()

## Configuração de Software:
### Pinagem:

| Pino (Nome no Código) | Número do Pino | Observações                                                                     |
| --------------------- | -------------- | ------------------------------------------------------------------------------- |
| `outputServopitch`    | 2              | Utilizado para sinal PWM do motor do pitch                                      |
| `outputServoYAW`      | 4              | Utilizado para sinal PWM do motor do YAW                                        |
| `ENCODER_PIN_A`       | 25             | Utlizado para interrupção do Sensor de Velocidade de Rotação Infra-Vermelho     |
| `CLKpitch`            | 21             | Utilizado como sinal CLK do encoder do pitch                                    |
| `DTpitch`             | 22             | Utilizado como sinal DT do encoder do pitch                                     |
| `CLKyaw`              | 21             | Utilizado como sinal CLK do encoder do YAW                                      |
| `DTyaw`               | 22             | Utilizado como sinal DT do encoder do YAW                                       |

### Plataforma NODE-RED

O NODE-RED é uma plataforma baseada em Browser para aplicações orientadas a eventos. É responsável pela criação do Broker MQTT, além de receber os dados via MQTT, criar uma página WEB onde consta a dashboard, e passar os dados recebidos para o dashboard. Seu uso é baseado em Nodes, onde cada node tem uma função e podem se interligar entre si, criando um fluxo fácil de compreender.
![image](https://github.com/user-attachments/assets/b60e41ac-28d1-4a55-86d6-d01f91dd5b94)

### Dashboard

![image](https://github.com/user-attachments/assets/a235ccc9-2ad5-4261-83fd-98e05beb57a9)

### Programa Final:

A pasta Programas [codigo/codigo.ino](https://github.com/pedrohgceolin/Controle_Torre_Eolica_Experimental/blob/main/codigo/codigo.ino) contém o código-fonte consolidado que será executado no ESP32. Inclui a integração dos códigos de todos os sensores utilizados.

## Instruções de Execução:

Para executar o projeto localmente, siga estas etapas:

1. **Pré-requisitos**:
   - Instale a última versão da Arduino IDE a partir do [site oficial](https://www.arduino.cc/en/software).
   - Configure a Arduino IDE para suportar o ESP32 seguindo as instruções disponíveis na [documentação do ESP32](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html).
   - Instale todas as bibliotecas necessárias mencionadas no arquivo [bibliotecas](./bibliotecas.txt).

2. **Execução da Aplicação**:
   - **Carregar o Código no ESP32**:
     1. Conecte o ESP32 ao seu computador.
     2. Abra o Arduino IDE.
     3. Carregue o código no ESP32.
        - [Código Final](https://github.com/pedrohgceolin/Controle_Torre_Eolica_Experimental/blob/main/codigo/codigo.ino)
   - **Monitoramento via Node-Red**:
     1. Instale o Node-Red em seu computador, pelo website [Node-Red](https://nodered.org/)
     2. Assim que estiver instalado e rodando, baixe o [arquivo .json](https://github.com/pedrohgceolin/Controle_Torre_Eolica_Experimental/blob/main/Node-Red/flows.json), e faça upload.
     3. Faça o deploy.
     4. Agora terá acesso a dashboard gerada pelo Node-Red, pelo endereço [http://127.0.0.1:1880/dashboard/](http://127.0.0.1:1880/dashboard/), e todas os nodes, podendo mudar ou configurar da forma que quiser.
