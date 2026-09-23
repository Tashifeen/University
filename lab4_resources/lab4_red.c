/* This is a C99 Fibonacci number generator with a subtle bug in it. Your
 * objective is to fix this implementation by finding the bug, and repairing
 * the source file.
 *
 * To pass this exercise, submit the fixed source file to the submission system
 * to have it checked. To pass, make as few modifications to this source file
 * as possible.
 *
 * The Fibonacci sequence is a mathematical sequence governed by the rule
 * $x_{n+1}=x_n+x_{n-1}$, where x_0=0 and x_1=1.
 * (https://quicklatex.com/cache3/68/ql_783ae9ec1e3597a6c5e1fdd85d5c8668_l3.png),
 * where n is always an unsigned integer. By way of example, the tenth (n=9)
 * fibonacci number is 34.
 *
 * The function below should return the nth fibonacci number, but it does not. */
unsigned fib(unsigned n)
{
	unsigned fib[3] = {0, 1, 1};
	if (!n) return 0;
	while (n--)
	{
		fib[2] = fib[0] + fib[1];
		fib[0] = fib[1];
		fib[1] = fib[2];
	}
	return fib[0];
}

/* Here is a main function you can use to play with the fibonacci function. It
 * doesn't contain the bug, and thus should not be modified.
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    if (argc != 2)
	{
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return -1;
    }

    int n = atoi(argv[1]);
    if (n < 0)
	{
        fprintf(stderr, "n must be unsigned\n");
        return -1;
    }

	printf("Fib(%u)=%u\n", (unsigned)n, fib(n));
    return 0;
}
*/
