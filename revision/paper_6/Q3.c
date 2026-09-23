//#include <coins.h>

/*
void setup(void) {
    init_sensor();
    init_display();
} */

#include <stdio.h>
static int total = 0;

int loop(void) {
    int val = 100; //read_coin();
    if (val != 0 && val != 1 && val != 2 && val != 5 
    	&& val != 10 && val != 20 && val != 50 && 
    	val != 100 && val != 200) {
        return 1;
    } 
            
    char msg[16];
    total += val;
    sprintf(msg, "Total: %03up", total);
    // display_write(char const *const msg)
    printf("\n\n\n%s\n\n", msg);
    return 1;
}

int main(void) {
    loop();
    loop();
    return 0;
}
