#include <stddef.h>
#include <stdio.h>

void acc(int *a, int *b, size_t count)
{
	while (count-- > 0) {
		*a++ += *b++;
	}
}

int main(void)
{
    int a[6] = {1, 2, 3, 4, 5, 6};
    int b[6] = {6, 5, 4, 3, 2, 0};
    size_t count = sizeof(a)/sizeof(int);
    acc(a, b, count);
    /* a now contains 7, 7, 7, 7, 7, 6 */
    for (size_t i=0; i < count; i++) {
	printf("%d\n", a[i]);
    }
    return 0;
}
