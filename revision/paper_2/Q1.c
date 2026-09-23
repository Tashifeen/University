#include <stdio.h>
#include <ctype.h>

int to_upper(int c) { return toupper(c); }
int to_lower(int c) { return tolower(c); }

unsigned apply(char *str, int (*transform)(int)) {
    unsigned count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ') {
            char temp = transform(str[i]);
            if (temp != str[i]) {
                str[i] = temp;
                count++;
            }
        }
    }
    return count;
}

int main(void) {
    char s[] = "Hello World";
    unsigned count = apply(s, to_upper);
    printf("\n\n\n%s %o\n", s, count);
    count = apply(s, to_lower);
    printf("%s %o\n\n\n", s, count);
    return 0;
}
