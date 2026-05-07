#ifndef LAB3_AMBER_H
#define LAB3_AMBER_H

#define RELU(arr, len) do {								\
	for (size_t _i = 0; _i < (len); _i++) {				\
		(arr)[_i] = ((arr)[_i] < 0 ? 0 : (arr)[_i]);	\
	}													\
} while (0)

#endif
