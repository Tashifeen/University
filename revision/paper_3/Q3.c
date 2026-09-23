#include <stdio.h>
#include <stdint.h>
/*#include <tank.h>

void setup(void) {
    init_sensor();
    init_display();
}*/

int loop(void) {
    uint16_t raw = 312; //read_level();
    char arr[17];
    arr[0] = 'L';
    arr[1] = 'e';
    arr[2] = 'v';
    arr[3] = 'e';
    arr[4] = 'l';
    arr[5] = ':';
    arr[6] = ' ';
    arr[7] = '0' + raw/1000;
    arr[8] = '0' + (raw/100)%10;
    arr[9] = '0' + (raw/10)%10;
    arr[10] = '0' + raw%10;
    arr[11] = '/';
    arr[12] = '1';
    arr[13] = '0';
    arr[14] = '0';
    arr[15] = '0';
    arr[16] = '\0';
    printf("\n\n\n%s\n\n", arr); //display_write(char const *const arr);
    return 0;
}

int main(void) {
    loop();
    return 0;
}
