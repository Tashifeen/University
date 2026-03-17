#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/uart.h"
#define UART_TX_ID uart0
#define UART_TX_PIN 0
#define UART_RX_ID uart1
#define UART_RX_PIN 5
#define BAUD_RATE 9600
void setup(void) {
	stdio_init_all();
	uart_init(UART_TX_ID, BAUD_RATE);
	uart_init(UART_RX_ID, BAUD_RATE);
	gpio_set_function(UART_TX_PIN, UART_FUNCSEL_NUM(UART_ID, UART_TX_PIN));
	gpio_set_function(UART_RX_PIN, UART_FUNCSEL_NUM(UART_ID, UART_TX_PIN));
	cyw43_arch_init();
}

int loop(void) {
	// Checking device sends single byte to UART0
	int original = 0x01;
	uart_putc(UART_TX_ID, original);
	
	char b1 = uart_getc(UART_RX_ID);
	char b2 = uart_getc(UART_RX_ID);
	
	// If first byte recieved is not 0x00
	if (b1 != 0x00 || b2 != original * 2) {
		cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
		// If second byte recieved is not double originall 
	}
	return 1;
}

/* Do not modify main, though remember to comment it out for submission */
int main(void)
{
    setup();
    sleep_ms(1000);
    while (loop()) sleep_ms(10000);
    return 0;
}
