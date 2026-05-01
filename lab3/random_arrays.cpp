#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "binary_tree.h"
using namespace std;

int main() {
	srand(time(nullptr));

	int n;
	cout << "Enter n: ";
	cin >> n;

	double sum_avg = 0.0;

	for (int t = 0; t < 10; t++) {
		binary_tree<int> bt;

		// Insert n random numbers
		for (int i = 0; i < n; i++) {
			int x = rand();
			bt.insert(x);
		}

		double avg = bt.average_depth();
		cout << "Trial " << t+1 << ": " << avg << endl;

		sum_avg += avg;
	}

	cout << "\nOverall average of average depths = "
		 << sum_avg / 10.0 << endl;
	return 0;
}
