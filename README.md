# SPRINT4_EDGE
# Challenge - First Year - Edge Computing: Alerta Leitos

## Resumo
O projeto **Alerta-Leitos** é um sistema de monitoramento inteligente de leitos hospitalares, desenvolvido com o foco em melhorar a gestão hospitalar através da **Internet das Coisas (IoT)**, unindo hardware, automação e nuvem para fornecer alertas em tempo real e dados confiáveis sobre a ocupação dos leitos.

---

## Visão Geral
Hospitais enfrentam desafios constantes na gestão eficiente dos seus leitos. Pensando nisso, o Alerta-Leitos surge como uma solução moderna e integrada que monitora o status de cada leito hospitalar de forma automatizada, emitindo alertas sempre que há mudanças no status de ocupação de cada um dos leitos.

### Tecnologias Utilizadas no Projeto

* **Arduino IDE**: Para o desenvolvimento do hardware de monitoramento e a programação do microcontrolador, incluindo o uso de bibliotecas para display LCD, módulo RTC e serialização JSON.
* **Node-RED**: Plataforma de automação que intermedeia os dados entre o hardware e o back-end, permitindo a criação de fluxos lógicos e alertas.
* **Tago.io**: Plataforma em nuvem utilizada para armazenar, processar e visualizar os dados coletados, funcionando como o "cérebro na nuvem" do projeto.

### Funcionalidades
O sistema Alerta-Leitos oferece **monitoramento em tempo real** dos leitos hospitalares, permitindo o acompanhamento contínuo do estado de ocupação de cada unidade. Ele é capaz de emitir **alertas automáticos** por meio da plataforma Tago.io, garantindo uma resposta rápida diante de qualquer mudança de status. Além disso, conta com um **painel de visualização intuitivo**, composto por dashboards personalizados que facilitam a interpretação dos dados. A automação das regras operacionais é realizada por meio do Node-RED, que processa as informações recebidas e executa ações predefinidas. Todo esse ecossistema é integrado a componentes físicos conectados a um Arduino, possibilitando uma solução completa e eficaz de IoT aplicada à saúde.

---

### Especificações Técnicas (Hardware)
A parte física do sistema é composta por componentes simples e de baixo custo, permitindo fácil replicação:

1.  **Arduino Uno**: Microcontrolador responsável por ler as entradas (botão), controlar as saídas (LEDs, servo, LCD) e enviar os dados ao Node-RED.
2.  **Servo Motor**: Utilizado como indicador físico do status do leito, girando para diferentes ângulos conforme a ocupação. Seguem aqui as descrições dos ângulos e seus respectivos estados:
    * **0°**: Leito Ocupado
    * **36°**: Iniciando Limpeza
    * **72°**: Finalizando Limpeza
    * **108°**: Iniciando Manutenção
    * **144°**: Finalizando Manutenção
    * **180°**: Desocupado / Leito Pronto
3.  **Seis LEDs**: Indicação visual complementar ao servo motor e ao LCD, representando os diferentes estados:
    * **Vermelho (ledR)**: Leito Ocupado
    * **Amarelo (ledY)**: Iniciando Manutenção
    * **Verde (ledG)**: Desocupado / Leito Pronto
    * **Ciano (ledC)**: Iniciando Limpeza
    * **Laranja (ledO)**: Finalizando Limpeza
    * **Roxo (ledP)**: Finalizando Manutenção
4.  **Botão de Acionamento**: Permite a mudança manual dos estados do leito no próprio hardware.
5.  **Display LCD 16x2 I2C**: Exibe o número do leito, a hora atual e o status, fornecendo feedback direto no ambiente hospitalar.
6.  **Módulo RTC DS1307**: Real-Time Clock para manter a hora e a data, garantindo a precisão dos dados de tempo.

Este conjunto garante um feedback local direto no ambiente hospitalar, mesmo sem acesso à plataforma digital.

---

### Como Funciona?
O status do leito é alterado por meio de um **botão físico** (ou comando via serial), que é processado pelo microcontrolador Arduino. O Arduino, então, atualiza o **servo motor**, acende o **LED** correspondente ao novo status e exibe as informações (número do leito, status e hora atual via RTC) no **display LCD**.

Simultaneamente, o Arduino envia esses dados (número do leito, status e hora) em formato **JSON** via comunicação serial para o **Node-RED**. O Node-RED processa esses dados e os encaminha à nuvem pela plataforma **Tago.io**, onde os dados são armazenados, exibidos em dashboards e utilizados para disparar alertas automatizados.

---

### Instalação e Execução

#### ⚠️ Atenção: Este projeto envolve componentes de hardware e acesso a plataformas externas. Abaixo estão os passos principais:

1.  **Configure o Arduino**:
    * Conecte o Arduino Uno, o servo motor, os seis LEDs, o botão, o display LCD I2C e o módulo RTC conforme as especificações do circuito.
    * Instale as bibliotecas necessárias na Arduino IDE: `Servo`, `ArduinoJson`, `LiquidCrystal_I2C` e `RTClib`.
    * Carregue o código Arduino fornecido para o microcontrolador via Arduino IDE.
2.  **Instale o Node-RED**: Instale o Node-RED localmente ou em um servidor.
3.  **Importe o Fluxo Node-RED**: Importe o fluxo `.json` do projeto para o Node-RED. Certifique-se de configurar um nó de entrada serial para receber os dados do Arduino.
4.  **Conecte o Node-RED ao Tago.io**: Conecte o Node-RED à sua conta do Tago.io via tokens de acesso e configure os nós de saída para enviar os dados dos leitos.
5.  **Crie um Dashboard no Tago.io**: Crie um dashboard no Tago.io e configure os widgets para visualizar os dados de cada leito.
