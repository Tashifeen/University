#include <string.h>
#include <stdlib.h>

char *repeat(char const *str, unsigned n) {
    size_t len = strlen(str);
    size_t total = len * n;
    
    char *out = malloc(total + 1);
    // if (!out) return NULL;
    out[0] = '\0';
    
    /* or...
    char *out = calloc(total + 1, sizeof(char));
    */
    
    for (unsigned i = 0; i < n; i++) {
        strcat(out, str);
    }
    
    return out;
}

#include <stdio.h>
int main(void) {
    char *str = "";
    char *arr = repeat(str, 0);
    printf("\n\n\n%s\n\n", arr);
    free(arr);
    return 0;
}
