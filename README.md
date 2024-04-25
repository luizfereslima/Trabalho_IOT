# Documentação do Projeto: Sistema de Monitoramento do CPD (Centro de Processamento de Dados)

## Introdução

O projeto foi desenvolvido para solucionar um problema de controle na sala do CPD (Centro de Processamento de Dados), onde a necessidade de monitorar a presença de pessoas, a temperatura ambiente e o estado da porta é crucial para garantir a segurança e a integridade dos equipamentos e dados. Com a implementação deste sistema de monitoramento, espera-se solucionar esse problema ao fornecer informações em tempo real sobre o ambiente da sala, permitindo um controle mais eficaz e a tomada de medidas preventivas quando necessário.

## Componentes Utilizados

- Microcontrolador ESP8266
- Sensor de Presença
- Sensor de Temperatura
- Sensor de Porta
- Protoboard
- Resistores e cabos para conexão
- Fonte de energia

## Funcionamento do Sistema

O ESP8266 é o componente central do sistema e é responsável por coletar dados dos sensores e enviar as informações para uma plataforma de monitoramento remoto.

### Sensor de Presença

O sensor de presença é utilizado para detectar a presença de pessoas no ambiente. Ele detecta movimentos e aciona um sinal elétrico quando identifica atividade. Este sinal é então interpretado pelo ESP32 para determinar se há alguém presente no local.

### Sensor de Temperatura

O sensor de temperatura mede a temperatura ambiente e fornece essa informação ao ESP8266.

### Sensor de Porta

O sensor de porta é utilizado para monitorar o estado da porta, isto é, se está aberta ou fechada. Ele envia um sinal ao ESP8266 indicando o status atual da porta, permitindo que o sistema acompanhe se a porta está sendo aberta ou fechada.

## Diagrama de relacionamento

O diagrama a seguir ilustra como os componentes serão relacionados:

![Imagem do WhatsApp de 2024-04-25 à(s) 13 47 12_7d4aa5e4](https://github.com/luizfereslima/Trabalho_IOT/assets/75223914/2cc20f77-6761-45d2-a4ff-1ea3cffb5033)

## Conclusão

O sistema de monitoramento de ambiente com ESP8266 oferece uma solução eficaz e versátil para monitorar a presença de pessoas, a temperatura ambiente e o estado da porta em tempo real. Com sua flexibilidade e capacidade de expansão, pode ser adaptado para uma variedade de aplicações, desde residenciais até comerciais e industriais.
