#include <iostream>
#include <stdexcept>   // for std::out_of_range

template <typename T, int N>
class NewArray {
private:
    T data[N];   // internal fixed-size storage

public:

    // operator[] — no bounds checking
    T& operator[](int index) {
        return data[index];
    }

    const T& operator[](int index) const {
        return data[index];
    }

    // at() — with bounds checking
    T& at(int index) {
        if (index < 0 || index >= N)
            throw std::out_of_range("Index out of range");
        return data[index];
    }

    const T& at(int index) const {
        if (index < 0 || index >= N)
            throw std::out_of_range("Index out of range");
        return data[index];
    }

    // front()
    T& front() {
        return data[0];
    }

    const T& front() const {
        return data[0];
    }

    // back()
    T& back() {
        return data[N - 1];
    }

    const T& back() const {
        return data[N - 1];
    }

    // empty()
    bool empty() const {
        return N == 0;
    }

    // size()
    int size() const {
        return N;
    }
};



int main() {
    NewArray<int, 3> narr;
    narr[0] = 0;
    narr[1] = 9;
    narr[2] = 2;
    
    std::cout << narr.front() << std::endl;
    std::cout << narr.at(1)   << std::endl;
    std::cout << narr.back()  << std::endl;
    std::cout << "Size: "  << narr.size()  << std::endl;
    std::cout << "Empty: " << narr.empty() << std::endl;
    return 0;
}
