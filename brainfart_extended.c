#include <stdio.h>
xint brainfart_amber(const char *commands)
{
    int array[10] = {0};
    int a_i = 0;  // data pointer
    int c_i = 0;  // instruction pointer

    printf("Index\tValue\tOperation\n");

    while (commands[c_i] != '\0') {
        char op = commands[c_i];

        switch (op) {
            case '+':
                array[a_i]++;
                break;

            case '-':
                array[a_i]--;
                break;

            case '>':
                a_i = (a_i == 9 ? 0 : a_i + 1);
                break;

            case '<':
                a_i = (a_i == 0 ? 9 : a_i - 1);
                break;

            case '[':
                // If current cell is zero, skip forward to next ']'
                if (array[a_i] == 0) {
                    c_i++;
                    while (commands[c_i] != ']') {
                        c_i++;
                    }
                }
                break;

            case ']':
                // If current cell is non-zero, jump back to previous '['
                if (array[a_i] != 0) {
                    c_i--;
                    while (commands[c_i] != '[') {
                        c_i--;
                    }
                }
                break;

            default:
                break;
        }

        printf("%d\t%d\t%c\n", a_i, array[a_i], op);
        c_i++;
    }

    printf("Result: %d\n", array[a_i]);
    return array[a_i];
}
/*
int main(void)
{
    printf("output: %d\n", brainfart_amber("+++[>++<-]>"));
    /* Should print 4 */
    /*return 0;
}
*/
