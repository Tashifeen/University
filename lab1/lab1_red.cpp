#include <iostream>
#include <algorithm>

void sort_red(float* values, std::size_t count) {
	std::sort(values, values + count);
}

int main(void) {
	float fs[] = {1.5, -2.6, 4.3, 99462};
	sort_red(fs, sizeof(fs) / sizeof(float));

	for (float f : fs) {
		std::cout << f << "\n";
	}
}
