#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#define UART_ID uart0
#define BAUD_RATE 9600
#define UART_TX_PIN 0
#define UART_RX_PIN 1
void setup(void) {
	stdio_init_all();
	uart_init(UART_ID, BAUD_RATE);
	gpio_set_function(UART_TX_PIN, UART_FUNCSEL_NUM(UART_ID, UART_TX_PIN));
	gpio_set_function(UART_RX_PIN, UART_FUNCSEL_NUM(UART_ID, UART_RX_PIN));	
}

int loop(void){
	// Block until character is received
    char c = uart_getc(UART_ID);
	
    // If 'z', wrap to 'a', else increment
    if (c == 'z') {
        c = 0x61;
    } else {
        c++;
	}
	
    // Transmit the new character
    printf("%c", c);
    uart_putc(UART_ID, c);
    return 1;
	
}



/* Do not modify main, though remember to comment it out for submission */ 
int main(void)
{
    setup();
    sleep_ms(1000);  
    uart_putc(UART_ID, 0x61);  
    while (loop()) sleep_ms(250);
    return 0;
}
