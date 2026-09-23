#include <stdio.h>
#include <stdlib.h>

int brainfart_red(char const *commands) {
	// Initalse results array
	int* arr = (int*) calloc(20, sizeof(int)); // All elements set to zeo
	int p = 0; // pointer to results array
	
	// Iterate through commands
	int i = 0;
	while (commands[i] != '\0') {
		char op = commands[i];
		printf("%c\n", op);

		switch (op) {
			case '+':
				arr[p] += 1;
				break;
			case '-':
				arr[p] -= 1;
				break;
			case '>':
				p = (p == 19) ? 0 : p + 1;
				break;
			case '<':
				p = (p == 0) ? 19 : p - 1;
				break;
			default:
				break;
		}
		i++;
	}
	return arr[p];
}

int main(void)
{
    printf("output: %d\n", brainfart_red("+++>--<+<octopus>"));
    /* Should print 4 */
    return 0;
}
