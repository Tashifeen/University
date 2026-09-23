#include <stdio.h>
#include <math.h>
#include <stdint.h>
/*
void setup(void) {
    stdio_init_all();
    adc_init();
    adc_select_input(0);
}
*/

void loop(void) {
    uint16_t raw = 2048;
    int pressure = floor(raw/4095.0 *500);
    char arr[19];
    arr[0] = 'P';
    arr[1] = 'r';
    arr[2] = 'e';
    arr[3] = 's';
    arr[4] = 's';
    arr[5] = 'u';
    arr[6] = 'r';
    arr[7] = 'e';
    arr[8] = ':';
    arr[9] = ' ';
    arr[10] = '0' + pressure/100;
    arr[11] = '0' + (pressure/10)%10;
    arr[12] = '0' + pressure%10;
    arr[13] = ' ';
    arr[14] = 'k';
    arr[15] = 'P';
    arr[16] = 'a';
    arr[17] = '\n';
    arr[18] = '\0';
    
    printf("\n\n\n%s\n\n\n", arr);
}

int main(void) {
    loop();
    return 0;
}
