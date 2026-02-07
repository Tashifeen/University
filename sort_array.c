#include <stdio.h>
#include <stddef.h>

// static - function is only visible inside the same .c file
static void swap(float *a, float *b) {
	float temp = *a;
	*a = *b;
	*b = temp;
// swapped values stored at memory addresses (a*, b*) so no need to return anything
}


void sort_red(float* values, size_t count)
{
	for (size_t i = 0; i < count -1; i++) {
		for (size_t j=0; j < count - 1 - i; j++) {
			if (values[j] > values[j+1]) {
				swap(&values[j], &values[j + 1]);
			}
		}
	}
// swapped values stored at memory addresses (a*, b*) so no need to return anything
}


