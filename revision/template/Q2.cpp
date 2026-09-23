template <typename T>

bool all_equal(std::vector<T> const &vec) {
	if (vec.size() <= 1)
		return true;  // empty or single element

	const T &first = vec[0];
	for (size_t i = 1; i < vec.size(); i++) {
		if (!(vec[i] == first))
			return false;
	}
	return true;
}
