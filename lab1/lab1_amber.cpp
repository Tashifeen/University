#include <cstddef> // size_t
#include <algorithm> // std::sort

void sort_amber(float* values, size_t length, int (*comp)(float, float)) {
	std::sort(values, values + length, [comp](float a, float b)) {
	            return comp(a, b) < 0;   // convert your comparator to boolean
	        }
	
}
