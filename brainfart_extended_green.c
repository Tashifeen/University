#include <stdio.h>
int brainfart_green(const char *commands)
{
    int array[10] = {0};
    int a_i = 0;  // data pointer
    int c_i = 0;  // instruction pointer
    int depth = 0;

    printf("Index\tValue\tOperation\tDepth\n");

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

            case '.': // CHANGE THIS
            	break;

            case '[':
                // If current cell is zero, skip forward to next ']'
                if (array[a_i] == 0) {
                	depth++;
                    while (commands[c_i] != ']') {
                    	c_i++;
						if (commands[c_i] == '[')
							depth++;
                    }
                    c_i--; // Decremrent c because c increments at the end of this function
                }
                break;

            case ']':
                // If current cell is non-zero, jump back to previous '['
                if (array[a_i] != 0) {
                    while (depth > 0) {
                    	if (commands[c_i] == '[')
                    		depth--;
                    	c_i--;
                    }
                }
                break;

            default:
                break;
        }

        printf("%d\t%d\t%c\t%d\n", a_i, array[a_i], op, depth);
        c_i++;
    }

    printf("Result: %d\n", array[a_i]);
    return array[a_i];
}

int main(void)
{
    printf("output: %d\n", brainfart_green("What is a program?++++++++[>++++[>++>+++>+++>+<<<<-]>+A miserable little>+>->>+[<]<-]>>.>---.+++++++..+++.>>pile of instructions.<-.<.+++.------.--------.>>+.>++."));
    /* Should print 10 */
    return 0;
}
