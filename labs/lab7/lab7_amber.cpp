#include <unordered_map>
#include <vector>
#include <cmath>
using namespace std;

template<typename T1, typename T2>
unordered_map<T1, T2> swag(vector<pair<T1, T2>> in, int op) {

	// Step 1: group values by key
	unordered_map<T1, vector<T2>> groups;

	for (const auto& p : in) {
		groups[p.first].push_back(p.second);
	}

	// Step 2: compute the required mean per key
	unordered_map<T1, T2> result;

	for (const auto& entry : groups) {
		const T1& key = entry.first;
		const vector<T2>& vals = entry.second;
		int n = vals.size();

		T2 answer = T2(); // default-initalise (which is 0 for numbers)

		if (op == 0) {
			// Arithmetic mean
			T2 sum = 0;
			for (const auto& x : vals) sum += x;
			answer = sum / n;
		}
		else if (op == 1) {
			// Geometric mean
			T2 product = 1;
			for (const auto& x: vals) product *= x;
			answer = pow(product, 1.0 / n);
		}
		else if (op == 2) {
			// Harmonic mean
			double denom = 0;
			for (const auto& x : vals) denom += 1.0 / x;
			answer = n / denom;
		}

		result[key] = answer;
	}

	return result;
}
