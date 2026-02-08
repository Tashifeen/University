#include <stddef.h>

size_t myfun(int *arr, int *loc) {  /* Your function */
	ptrdiff_t d = loc - arr;
	return d;
}

int main(void)
{
    int x[100] = {0};
    return myfun(x, &x[67]);  /* Returns 67 */
}
