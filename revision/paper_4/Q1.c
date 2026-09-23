#include <stdio.h>

unsigned compress(char *str, char const search, char const replace) {
    unsigned count = 0;
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == search) {
            count++;
            str[i] = replace;
        }
    }
    return count;
}


int main(void) {
    char str[] = "aaaa";
    unsigned count = compress(str, 'a', 'a');
    printf("\n\n\n%s    %u\n\n", str, count);
    return 0;
}
