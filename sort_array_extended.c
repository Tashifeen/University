#include <stdio.h>
#include <stddef.h>

// static - function is only visible inside the same .c file
static void swap(float *a, float *b) {
	float temp = *a;
	*a = *b;
	*b = temp;
// swapped values stored at memory addresses (a*, b*) so no need to return anything
}


void sort_amber(float* values, size_t length, int(*comp)(float, float))
{
	for (size_t i = 0; i < length - 1; i++) {
		for (size_t j=0; j < length - 1 - i; j++) {
			if (comp(values[j], values[j + 1]) == 0) { // CHANGE CONDITION - if first float appears after 2nd float then swap (comp returns 0)
				swap(&values[j], &values[j + 1]);
			}
		}
	}
// swapped values stored at memory addresses (a*, b*) so no need to return anything
}


