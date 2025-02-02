// Inclusão das Bibliotecas
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

// Definição Dos pinos
#define LED_PIN_GREEN 11
#define LED_PIN_BLUE 12
#define LED_PIN_RED 13
#define BUTTON_A_PIN 5

// Variáveis Globais
static volatile bool led_active = false;
static volatile uint32_t last_time = 0;
static volatile uint i = 0;

// Protótipos de funções
void init();
int64_t led_red_callback(alarm_id_t id, void *user_data);
int64_t led_blue_callback(alarm_id_t id, void *user_data);
int64_t led_green_callback(alarm_id_t id, void *user_data);
void set_all_pin_on();

int main()
{
    // inicialização
    stdio_init_all();
    init();

    // laço de repetição
    while (true)
    {
        // Verifica se o botão foi pressionado (nível baixo no pino) e se o LED não está ativo.
        if (!gpio_get(BUTTON_A_PIN) && !led_active)
        {
            uint32_t current_time = to_us_since_boot(get_absolute_time());
            if (current_time - last_time > 50000) // 50 ms de debouncing
            {
                last_time = current_time;                               // Atualiza o tempo do último evento
                set_all_pin_on();                                       // acende todos os leds
                led_active = true;                                      // Marca a variável global informando que os leds estão acesos
                add_alarm_in_ms(3000, led_green_callback, NULL, false); // alarme para desligar led verde
                add_alarm_in_ms(6000, led_blue_callback, NULL, false);  // alarme para desligar led azul
                add_alarm_in_ms(9000, led_red_callback, NULL, false);   // alarme para desligar led vermelho
            }
        }
        if (!gpio_get(LED_PIN_GREEN) && !gpio_get(LED_PIN_BLUE) && !gpio_get(LED_PIN_RED))
            led_active = false; // Atualiza a Variável global caso todos os leds já tenham apagado
    }
}
void init()
{
    // inicialização dos pinos de LEDs
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);
    gpio_put(LED_PIN_GREEN, 0);

    gpio_init(LED_PIN_BLUE);
    gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);
    gpio_put(LED_PIN_BLUE, 0);

    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    gpio_put(LED_PIN_RED, 0);

    // inicialização do botão com resistor interno pull-up
    gpio_init(BUTTON_A_PIN);
    gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_A_PIN);
}
int64_t led_red_callback(alarm_id_t id, void *user_data)
{
    // desliga o led vermelho
    gpio_put(LED_PIN_RED, 0);
    return 0;
}
int64_t led_blue_callback(alarm_id_t id, void *user_data)
{
    // desliga o led azul
    gpio_put(LED_PIN_BLUE, 0);
    return 0;
}
int64_t led_green_callback(alarm_id_t id, void *user_data)
{
    // desliga o led verde
    gpio_put(LED_PIN_GREEN, 0);
    return 0;
}
void set_all_pin_on()
{
    // acende todos os leds
    gpio_put(LED_PIN_RED, 1);
    gpio_put(LED_PIN_BLUE, 1);
    gpio_put(LED_PIN_GREEN, 1);
}
