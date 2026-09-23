#include <vector>
#include <algorithm>
#include <random>

template <typename T>
class randomList : public std::vector<T> {
public:

    // Custom iterator for random traversal
    class random_iterator {
    public:
        random_iterator(const randomList<T>* parent, bool at_end)
            : parent(parent)
        {
            if (parent && !at_end) {
                // Build a permutation of indices
                int n = parent->size();
                indices.resize(n);
                for (int i = 0; i < n; i++)
                    indices[i] = i;

                // Shuffle the permutation
                std::shuffle(indices.begin(), indices.end(), rng);

                pos = 0;
            } else {
                pos = -1; // marks end
            }
        }

        // Dereference
        const T& operator*() const {
            return parent->at(indices[pos]);
        }

        // Increment
        random_iterator& operator++() {
            pos++;
            if (pos >= (int)indices.size())
                pos = -1; // end
            return *this;
        }

        // Comparison
        bool operator!=(const random_iterator& other) const {
            return pos != other.pos;
        }

    private:
        const randomList<T>* parent;
        std::vector<int> indices;
        int pos; // -1 means end

        static inline std::mt19937 rng{ std::random_device{}() };
    };

    // rbegin() and rend() return our custom iterator
    random_iterator rbegin() const {
        return random_iterator(this, false);
    }

    random_iterator rend() const {
        return random_iterator(this, true);
    }
};

#include <iostream>
int main() {
    randomList<int> l;
    for (int i=0; i<10; i++)
    	l.push_back(i);   

    for (auto it = l.rbegin(); it != l.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout<<std::endl;
    return 0;
}
