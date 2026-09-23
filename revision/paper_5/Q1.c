#include <stdlib.h>

int minilang(char const *program) {
    int* arr = (int*) calloc(10, sizeof(int));
    int p = 0;
    for (int i = 0; program[i] != '\0'; i++) {
        char c = program[i];
        switch (c) {
            case '+':
                (arr[p])++;
                break;
            case '-':
                (arr[p])--;
                break;
            case '>':
                if (p == 9) {
                    p = 0;
                } 
                else {
                    p++;
                }
                break;
            case '<':
               if (p == 0) {
                    p = 9;
                } 
                else {
                    p--;
                }
                break;
        }
    }
    int val = arr[p];  // save the value first
    free(arr);         // then free
    return val;
}

#include <stdio.h>
int main(void) {
    char program[] = "<+";
    int val = minilang(program);
    printf("\n\n\n%d\n\n", val);
    return 0;
}
