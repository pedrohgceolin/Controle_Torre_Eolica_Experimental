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
- [Encoder Rotativo]()
- [Sensor de Velocidade de Rotação Infra-Vermelho]()
- [Servo Motores]()


### Plataforma NODE-RED

O NODE-RED é uma plataforma baseada em Browser para aplicações orientadas a eventos. É responsável pela criação do Broker MQTT, além de receber os dados via MQTT, criar uma página WEB onde consta a dashboard, e passar os dados recebidos para o dashboard.
![image](https://github.com/user-attachments/assets/b60e41ac-28d1-4a55-86d6-d01f91dd5b94)
![image](https://github.com/user-attachments/assets/a235ccc9-2ad5-4261-83fd-98e05beb57a9)

