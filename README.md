# Temporizador_OneShot
O algoritmo implementa a ativação de 3 leds ao pressionar um push button utilizando da temporização, após acesos os leds apagam em sequência com 3 s de diferença entre eles. O processo só pode reiniciar apertando o botão após o último LED apagar
## Funcionalidades

- Inicializa e controla três LEDs (vermelho, verde e azul) conectados a pinos específicos do Raspberry Pi Pico.
- Ao apertar o botão, os 3 leds são acesos e apagam em sequência num intervalo de 3s entre cada.
- Caso o botão seja apertado novamente não ira realizar a ação novamente enquanto algum dos leds permanecer aceso.

## Hardware Necessário

- 1 Raspberry Pi Pico W (rp2040).
- 3 LEDs (Vermelho, Azul, Verde).
- Resistores apropriados para os LEDs.
- Fios de conexão.

## Pinagem

- LED Vermelho: Pino GPIO 13
- LED Azul: Pino GPIO 12
- LED Verde: Pino GPIO 11

## Configuração do Ambiente

Antes de começar, certifique-se de que você tenha o ambiente de desenvolvimento do **Raspberry Pi Pico** configurado corretamente. Siga as instruções do [Raspberry Pi Pico SDK](https://www.raspberrypi.org/documentation/rp2040/getting-started/) para configurar o SDK e as ferramentas de compilação. Para visualição do projeto no simulador também é importante configurar o simuldor WOKWI no VS code, conforme as instruções no link [WOKWI para VS code](https://docs.wokwi.com/pt-BR/vscode/getting-started).

## Compilação e Upload

1. Compile o código usando o ambiente de desenvolvimento configurado.
2. Após a compilação, faça o upload do código para o seu **Raspberry Pi Pico**.

## Tecnologias Utilizadas

- **C/C++**
- **Raspberry Pi Pico SDK**

## Contribuições

Contribuições são bem-vindas! Sinta-se à vontade para abrir um problema ou enviar um pull request.
