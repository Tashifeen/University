template <typename T> int count_occurrences(std::vector<T> vec, T value) {
	int count = 0;
	for (const T& element : vec) { // & = reference = alias for another variable. It allows you to create a new name for an existing variable.
		if (element == value) {
			count++;
		}
	}
	return count;
}
/*
Alternate answer:

#include <algorithm>

template <typename T> int count_occurrences(std::vector<T> vec, T value) {
	return std::count(vec.begin(), vec.end(), value);
}
*/
