#include <stdio.h>

double f(double x) {
    return x*x - 2;
}

double secant(double (*f)(double), double x0, double x1, unsigned n) {
    if (n == 0) {
        return x1;        
    }
    double x_new = 0;
    
    for (int i = 0; i < n; i++) {
        x_new = x1 - f(x1) * (x1 - x0) / (f(x1) - f(x0));
        x0 = x1;
        x1 = x_new;
    }
    return x_new;
}

int main(void) {
    double result = secant(f, 1.0, 2.0, 1);
    printf("\n\n\n%f\n\n", result);
    return 0;
}
