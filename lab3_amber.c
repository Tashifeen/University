#include <stdio.h>
#include "lab3_amber.h"  /* That's what I've called my header file */
#define SIZE 5



int main(void)
{
    int x[SIZE] = {-4, 9, -13, 0, 4963};
    RELU(x, SIZE);
    for (size_t i = 0; i < SIZE; printf("%d ", x[i++]));
    /* This should print: 0, 9, 0, 0, 4963 */
    return 0;
}
