# Sistema de Controle de uma Torre Eolica Experimental com ESP32

## Proposta

O objetivo deste trabalho é desenvolver um sistema de controle e gerenciamento para uma torre eólica experimental, utilizando exclusivamente dados recebidos de sensores. O sistema será responsável por processar informações de direção e velocidade do vento, fornecidas por sensores instalados na torre, e, com base nesses dados, ajustar de forma automatizada a posição da nacele e o ângulo das pás. Além disso, o sistema de controle irá medir a rotação das pás, sincronizando-a com a velocidade do gerador, garantindo que o gerador opere em sua faixa de eficiência máxima. O foco do projeto é a otimização do desempenho da torre eólica através de um controle preciso, utilizando dados em tempo real, sem a necessidade de intervenções manuais ou ajustes de hardware.

## Arquitetura do Projeto:

O projeto segue uma arquitetura onde o ESP32 coleta dados dos sensores e posiciona a nacele e os angulos das pás de acordo com os dados coletados. Além do controle, o ESP32 enviará esses dados coletados via protocolo MQTT para plataforma NODE-RED, que recebe os dados e os exibe em um dashboard, permitindo o monitoramento do sistema.

<img src="/Sistema de Controle Torre Eólica.png">

## Hardware:

### Visão Geral

O sistema utiliza o microcontrolador ESP32 como núcleo principal para coletar dados de sensores, processá-los e controlar atuadores. Sensores como anemômetro, sensor de direção do vento e medidor de RPM fornecem informações para ajustar automaticamente a posição da nacele e o ângulo das pás, otimizando a eficiência da torre eólica. Atuadores são usados para alinhar a nacele e modificar o ângulo das pás conforme necessário. Além disso, o sistema conta com comunicação via MQTT para enviar dados ao dashboard no Node-RED, permitindo o monitoramento remoto.

### Componentes Utilizados:

- [ESP-32 NodeMCU (microcontrolador)]()
- [Encoder Rotativo]()
- [Sensor de Velocidade de Rotação Infra-Vermelho]()
- [Servo Motores]()


### Plataforma NODE-RED

O NODE-RED é uma plataforma baseada em Browser para aplicações orientadas a eventos. É responsável pela criação do Broker MQTT, além de receber os dados via MQTT, criar uma página WEB onde consta a dashboard, e passar os dados recebidos para o dashboard.
![image](https://github.com/user-attachments/assets/8166ffa2-e58d-47e6-82a4-4ad5feec9738)
![image](https://github.com/user-attachments/assets/d772308c-2259-4324-8865-a00badf1c3c3)



### Objetivos

- Receber dados dos sensores de velocidade e direção do vento.
- Exercer o controle da posição da nacele e o ângulo das pás de acordo com os dados coletados.
- Transmitir dados para um servidor.
