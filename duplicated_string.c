#include <stdio.h>
#include <string.h>

int main(void)
{
	int num;
	char string[100];

	// Ask user to type a number and a string
	printf("Type a number and a string: \n");

	// Get and save the number AND string the user types
	scanf("%d %s", &num, string);

	printf("Your inputs were: %d %s\n", num, string);

	char output[1000] = "";

	for (int i=0; i <= num; i++) {
		// Concatenate input str to output str
		printf("%d %s\n", i, output);
		strcat(output, string);
	}

	// Display output
	printf("\nOutput:%s\n", output);

	return 0;
}
