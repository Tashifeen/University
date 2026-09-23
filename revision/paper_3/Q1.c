#include <stdio.h>

int double_it(int x) { return x * 2; }
int identity(int x)  { return x; }

unsigned apply_map(int *arr, size_t len, int (*transform)(int)) {
    unsigned count = 0;
    for (size_t i = 0; i < len; i++) {
        int temp = transform(arr[i]);
        if (temp != arr[i]) {
            count++;
        }
    }
    return count;
}

int main(void) {
    int arr[] = {-1,-2,-3};
    unsigned count = apply_map(arr, 4, double_it);
    printf("\n\n\n%o\n", count);
    printf("%ls", arr);
    return 0;
}
