#include <stdlib.h>
#include <stdio.h>

float comp(const void *a, const void *b) {
	return (*(float *)a - *(float *)b); // cast to float before derefrencing
}

void sort_red(float* values, size_t count) {
	qsort(values, count, sizeof(values[0]), comp);	
}

int main(void)
{
    float fs[] = {1.5, -2.6, 4.3, 99462};
    sort_red(fs, sizeof(fs) / sizeof(float));
    /* fs should now be ordered -2.6, 1.5, 4.3, 99462. */
    for (size_t i=0; i < (sizeof(fs) / sizeof(float)); i++) {
    	printf("%f\n", fs[i]);
    }
    return 0;
}
