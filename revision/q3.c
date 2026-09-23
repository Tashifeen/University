#include "light.h"
#include <math.h>
#include <cstdint>

struct foo {
	char a;
	char b;
	char c;
}

void setup(void) {
	init_sensor();
	init_lcd();
}


int loop(void) {
	uint8_t reading = read_light();
	int val = floor((reading/255.0) * 100);
    char arr[16];
    arr[0] = 'L';
    arr[1] = 'i';
    arr[2] = 'g';
    arr[3] = 'h';
    arr[4] = 't';
    arr[5] = ':';
    arr[6] = ' ';
    arr[7] = '0' + val/100;     // hundreds
    arr[8] = '0' + (val/10)%10; // tens
    arr[9] = '0' + val/100; // units
    arr[10] = '%';
    arr[11] = '\0';
    lcd_write(arr);
    return 0;
}


int main(void) {
        setup();
        while (loop()) sleep_ms(1000);
        return 0;
    }

/*
#include <math.h>
#include <cstdint>
#include <stdio.h>


int loop(void) {
	uint8_t reading = 0x80;
	int val = floor((reading/255.0) * 100);
    char arr[16];
    arr[0] = 'L';
    arr[1] = 'i';
    arr[2] = 'g';
    arr[3] = 'h';
    arr[4] = 't';
    arr[5] = ':';
    arr[6] = ' ';
    arr[7] = '0' + val/100;     // hundreds
    arr[8] = '0' + (val/10)%10; // tens
    arr[9] = '0' + val/100; // units
    arr[10] = '%';
    arr[11] = '\0';
    printf("\n\n\n%s\n\n\n", arr);
    return 0;
}

int main(void) {
        loop();
        return 0;
    }
*/
