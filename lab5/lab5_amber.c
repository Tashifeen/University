#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/adc.h"
#include <stdio.h>

void setup(void) {
	    stdio_init_all();
	    sleep_ms(500);   // <-- important for Pico W USB serial
	    cyw43_arch_init();
	    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
	
	    adc_init();
	    adc_set_temp_sensor_enabled(true);
	    adc_select_input(4);
}

int sense_and_light(void) {
    const float conversionFactor = 3.3f / (1 << 12);

    float adc = (float)adc_read() * conversionFactor;
    float tempC = 27.0f - (adc - 0.706f) / 0.001721f;

    printf("Temp = %.2f C\n", tempC);

    if (tempC > 0) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    } else {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    }

    return 1;
}


int main(void)
{
    setup();
    while (sense_and_light()) sleep_ms(1000);
    return 0;
}

