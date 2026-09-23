// #include <fan.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
/*
void init_sensor(void) {
    init_sensor();
    init_fan();
    init_lcd();
}
*/

int loop(void) {
    uint8_t raw = 0x66; // read_temp();
    unsigned temp = floor((raw / 255.0) * 100);
    int speed;
    if (temp < 40) {
        speed = 25;
    }
    if (temp >= 40 && temp < 70) {
        speed = 60; 
    }
    if (temp >= 70) {
        speed = 100;
    }
    
    // set_fan_speed(speed);
    char msg[18];
    sprintf(msg, "Temp: %02uC Fan: %d", temp, speed);
    printf("\n\n\n%s\n\n", msg);
    // lcd_write(msg);
    return 1;
}

int main(void) {
    loop();
    return 0;
}
