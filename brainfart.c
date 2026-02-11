#include <stdio.h>

int brainfart_red(char const *commands)
{
	int array[10] = {0}; // index from 0-9
	int c_i = 0;
	int a_i = 0;

	printf("Index\tValue\tOperation\n");


	while (1)
	{
		char op = commands[c_i];

		if (op == '\0') break;

		// Switch statement
		switch (op) {
			case '+': {
				array[a_i] += 1;
				break; 
				}
			case '-':
				{
                        	array[a_i] -= 1;
				break;
				}
			case '>': // Moves pointer right
				{
				a_i = (a_i == 9? 0: a_i+1); // if i points to the last element in the array, i will wrap around to the first value in the array
				break;
				}
			case '<': // Moves pointer left
				{
                        	a_i = (a_i == 0? 9: a_i-1); // if i points to the last element in the array, >
				break;
				}
			default:
				break;
		}
		printf("%d\t%d\t%c\n", a_i, array[a_i], op);
		c_i++;
	}

	printf("Result: %d", array[a_i]);
	return array[a_i];
}

/*
int main(void)
{
    printf("output: %d\n", brainfart_red("+++>--<+<>"));
    /* Should print 4 */ /*
    return 0;
}
*/
