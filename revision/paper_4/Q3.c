//#include <humidity.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
/*
void setup(void) {
    init_sensor();
    init_lcd();
}
*/

int loop(void) {
    uint8_t raw = 26; //read_humidity();
    int percent = floor((raw/255.0) * 100);
    char msg[16];
    msg[0] = 'H';
    msg[1] = 'u';
    msg[2] = 'm';
    msg[3] = 'i';
    msg[4] = 'd';
    msg[5] = 'i';
    msg[6] = 't';
    msg[7] = 'y';
    msg[8] = ':';
    msg[9] = ' ';
    msg[10] = '0' + percent/100;
    msg[11] = '0' + (percent/10)%10;
    msg[12] = '0' + percent%10;
    msg[13] = '%';
    msg[14] = '\0';
    //lcd_write(msg);
    printf("\n\n\n%s\n\n", msg);
    return 0;
}

int main(void){
    loop();
    return 0;
}
