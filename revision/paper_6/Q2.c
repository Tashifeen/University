double f(double x, double y) {
    return x + y;
}

double euler(double (*f)(double, double), double x0, double y0, double h, unsigned n) {
    if (n == 0) {
        return y0;
    }
    double y_new = y0 + h * f(x0, y0);
    double x_new = x0 + h;
    return euler(f, x_new, y_new, h, n-1); 
}

#include <stdio.h>
int main(void) {
    double ans = euler(f, 0, 1, 0.1, 2);
    printf("\n\n\n%f\n\n", ans);
    return 0;
}
