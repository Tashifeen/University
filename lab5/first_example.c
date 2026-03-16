#include <stdio.h>
#include "pico/stdlib.h"

int main(void) {
    stdio_init_all();
    while (1)
    {
        printf("Despite all my rage, I am still just a rat in a cage\n");
        sleep_ms(1000);
    }
    return 0;
}
