#include<vector>

template <typename T> 

int count_occurrences(std::vector<T> vec, T value) {
	int count = 0;
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i] == value) {
			count++;
		}
	}
	return count;
}
