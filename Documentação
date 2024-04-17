# Documentação do Projeto: Sistema de Monitoramento de Ambiente com ESP32 e Protoboard

## Introdução

Este documento descreve o projeto de um sistema de monitoramento de ambiente utilizando um microcontrolador ESP32, sensores de presença, temperatura e porta, além de uma protoboard para facilitar a conexão dos componentes. O sistema é capaz de monitorar a presença de pessoas, a temperatura ambiente e o estado da porta em tempo real.

## Componentes Utilizados

- Microcontrolador ESP32
- Sensor de Presença
- Sensor de Temperatura
- Sensor de Porta
- Protoboard
- Resistores e cabos para conexão
- Fonte de energia

## Funcionamento do Sistema

O ESP32 é o componente central do sistema e é responsável por coletar dados dos sensores e enviar as informações para um dispositivo de visualização ou para uma plataforma de monitoramento remoto.

### Sensor de Presença

O sensor de presença é utilizado para detectar a presença de pessoas no ambiente. Ele detecta movimentos e aciona um sinal elétrico quando identifica atividade. Este sinal é então interpretado pelo ESP32 para determinar se há alguém presente no local.

### Sensor de Temperatura

O sensor de temperatura mede a temperatura ambiente e fornece essa informação ao ESP32. O microcontrolador então pode processar esses dados e, se necessário, enviar alertas caso a temperatura esteja fora de uma faixa desejada.

### Sensor de Porta

O sensor de porta é utilizado para monitorar o estado da porta, isto é, se está aberta ou fechada. Ele envia um sinal ao ESP32 indicando o status atual da porta, permitindo que o sistema acompanhe se a porta está sendo aberta ou fechada.

## Diagrama de Conexão com Protoboard

O diagrama a seguir ilustra como os componentes estão conectados ao ESP32 utilizando uma protoboard:

```
   +--------------+       +---------------------+
   |              |       |                     |
   | Sensor de    |       | ESP32               |
   | Presença     |       |                     |
   |              |       |                     |
   +------+-------+       +----------+----------+
          |                           |
          |                           |
          |    +--------------+       |
          |    |              |       |
          +----+ Protoboard   +-------+--------+
               |              |                |
               +------+-------+                |
                      |                        |
                      |                        |
               +------+-------+       +--------+--------+
               |              |       |                 |
               | Sensor de    |       | Sensor de       |
               | Temperatura  |       | Porta           |
               |              |       |                 |
               +--------------+       +-----------------+
```

## Funcionalidades Adicionais

Além da simples coleta de dados, o sistema pode ser expandido com as seguintes funcionalidades:

- **Alertas:** O sistema pode ser configurado para enviar alertas por e-mail ou mensagem de texto caso detecte movimento inesperado, temperatura fora da faixa aceitável ou se a porta for aberta sem autorização.
- **Histórico de Dados:** Os dados coletados podem ser armazenados em um banco de dados local ou na nuvem para posterior análise e referência.
- **Integração com Plataforma IoT:** Os dados podem ser integrados a uma plataforma de IoT para monitoramento remoto e controle do ambiente.

## Conclusão

O sistema de monitoramento de ambiente com ESP32 e Protoboard oferece uma solução eficaz e versátil para monitorar a presença de pessoas, a temperatura ambiente e o estado da porta em tempo real. Com sua flexibilidade e capacidade de expansão, pode ser adaptado para uma variedade de aplicações, desde residenciais até comerciais e industriais. A utilização da protoboard simplifica o processo de conexão dos componentes, facilitando o desenvolvimento e a manutenção do sistema.
