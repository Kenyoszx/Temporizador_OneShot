#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define LED_PIN_GREEN 11
#define LED_PIN_BLUE 12
#define LED_PIN_RED 13
#define BUTTON_A_PIN 5

#define QTD_LEDS 3

static volatile bool led_active = false;
static volatile uint32_t last_time = 0;
static volatile i = 0;
uint8_t LEDS[QTD_LEDS] = {
    LED_PIN_GREEN,
    LED_PIN_BLUE,
    LED_PIN_RED
};

void init();
static void gpio_irq_handler(uint gpio, uint32_t events);
int64_t alarm_callback(alarm_id_t id, void *user_data);

int main()
{
    stdio_init_all();
    init();

    while (true)
    {

    }
}
void init()
{
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);
    gpio_put(LED_PIN_GREEN, 0);

    gpio_init(LED_PIN_BLUE);
    gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);
    gpio_put(LED_PIN_BLUE, 0);

    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    gpio_put(LED_PIN_RED, 0);

    // inicialização do botões com resistor interno pull-up
    gpio_init(BUTTON_A_PIN);
    gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_A_PIN);
    gpio_set_irq_enabled_with_callback(BUTTON_A_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler); // Rotina de Interrupção
}
int64_t alarm_callback(alarm_id_t id, void *user_data)
{
    return 0;
}
static void gpio_irq_handler(uint gpio, uint32_t events)
{
    // Configura a ação ao apertar o botão e implementa o Debouce

    // Obtém o tempo atual em microssegundos
    uint32_t current_time = to_us_since_boot(get_absolute_time());

    // Verifica se passou tempo suficiente desde o último evento
    if (current_time - last_time > 200000) // 200 ms de debouncing
    {
        last_time = current_time; // Atualiza o tempo do último evento
        if (!led_active)
        {
            gpio_put(LED_PIN_RED, 1);
            gpio_put(LED_PIN_BLUE, 1);
            gpio_put(LED_PIN_GREEN, 1);
            // Define 'led_active' como true para indicar que o LED está aceso.
            led_active = true;
            for (i = 0; i < QTD_LEDS; i++)
            {
                add_alarm_in_ms(3000, alarm_callback, NULL, false);
            }
        }
    }
}
