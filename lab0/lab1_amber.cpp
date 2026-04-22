#include <iostream>

int factorial() {
	int n;
	int output = 1;

	std::cout << "Type a number";
	std::cin >> n;

	if (n == 0) {
		return 1;
	}
	for (int i=1; i <= n; i++) {
		output *= i;
	}
	return output;
}

int main() {
	std::cout << factorial() << "\n";
	return 0;
}
