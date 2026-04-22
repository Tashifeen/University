#include <stdio.h>

int factorial(void) {
	int n;
	int output = 1;

	printf("Type a number: \n");
	scanf("%d", &n);

	if (n == 0) {
		return 1;
	}
	
	for (int i=1; i<=n; i++) {
		output *= i;
	}
			
	return output;
}

int main(void) {
	printf("%d\n", factorial());
	return 0;
}
