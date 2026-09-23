double f(double x) {
    return x*x - 2;
}

double bisect(double (*f)(double), double a, double b, unsigned n) {
    if (n == 0) {
        return (a + b / 2);
    }
    double mid = (a + b) / 2;
    if ((f(mid) >= 0 && f(a) >= 0) || (f(mid) < 0 && f(a) < 0)) {
        a = mid;
    } else {
        b = mid;
    }
    return bisect(f, a, b, n - 1);
}

#include <stdio.h>
int main(void) {
    double val = bisect(f, 1.0, 2.0, 2);
    printf("\n\n\n%f\n\n", val);
    return 0;
}
