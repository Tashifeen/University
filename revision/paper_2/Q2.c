#include <stdio.h>

double f(double x) {
    return x*x;
}

double simpson(double (*f)(double), unsigned const n, double const a, double const b) {
    double h = (b-a)/n;
    double x_k = 0;
    double temp = 0;
    int factor;
    for (unsigned int k = 0; k <= n; k++) {
        x_k = a + k*h;
        if (k == 0 || k == n) {
            factor = 1;          // first and last
        } else if (k % 2 == 1) {
            factor = 4;          // odd middle terms
        } else {
            factor = 2;          // even middle terms
        }
        printf("%i", factor);
        
        temp += factor * f(x_k);
    }
    double result = (h/3) * temp;
    return result;
}

int main(void) {
    double result = simpson(f, 4, 0, 1);
    printf("\n\n\n%f\n\n\n", result);
    return 0;
}
