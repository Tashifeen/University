#include <stdio.h>
double f(double x) {
    return x*x - 2;
}

double df(double x) {
    return 2*x;
}

double newton(double (*f)(double), double (*df)(double), double x0, unsigned n) {
	double x_new = x0;
	
	for (unsigned i = 0; i < n; i++) {
		x_new = x0 - f(x0) / df(x0);
		x0 = x_new;
	}
	return x_new;
}

int main(void) {
    double root = newton(f, df, 1.0, 3);
    printf("\n\n%f\n\n", root);
    return 0;
}
