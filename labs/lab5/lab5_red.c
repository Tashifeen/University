#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

// Base time unit (333 ms)
static const uint32_t BASE = 333;

// Dot = 1 unit ON, 1 unit OFF
static void dot(void) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    sleep_ms(BASE);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    sleep_ms(BASE);
}

// Dash = 3 units ON, 1 unit OFF
static void dash(void) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    sleep_ms(3 * BASE);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    sleep_ms(BASE);
}

void setup(void) {
    stdio_init_all();
    cyw43_arch_init();  // required for Wi-Fi LED
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
}

int sos(void) {
    // S = dot dot dot
    dot(); dot(); dot();

    // Letter spacing = 2 units
    sleep_ms(2 * BASE);

    // O = dash dash dash
    dash(); dash(); dash();

    // Letter spacing
    sleep_ms(2 * BASE);

    // S = dot dot dot
    dot(); dot(); dot();

    // Word spacing = 6 units (2331 ms)
    sleep_ms(6 * BASE);

    return 1;  // keep looping
}


/*int main(void)
{
    setup();
    while (sos());
    return 0;
}
*/
