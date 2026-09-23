#include <math.h>

double f(double x) {
    return x*x*x;
}


double deriv(double (*f)(double), double x, double h, unsigned n) {
    if (n == 0) {
        return f(x);        // base case — just evaluate f
    }
    // apply forward difference once, using deriv(n-1) as the "function"
    return (deriv(f, x + h, h, n - 1) - deriv(f, x, h, n - 1)) / h;
}

#include <stdio.h>
int main(void) {
    double df = deriv(f, 2.0, 0.001, 2);
    printf("\n\n\n%f\n\n", df);
    return 0;
}
