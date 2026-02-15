#include <iostream>
#include <vector>
#include <random>
#include <chrono>

// Insertion sort
void insertionSort(std::vector<double>& v)
{
    for (std::size_t i = 1; i < v.size(); ++i)
    {
        double key = v[i];
        std::size_t j = i;

        while (j > 0 && v[j - 1] > key)
        {
            v[j] = v[j - 1];
            --j;
        }

        v[j] = key;
    }
}

int main()
{
    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    std::cout << "n\tTime (seconds)\n";
    std::cout << "--------------------------\n";

    for (int n = 10; n < 5000; n *= 2)
    {
        std::vector<double> v(n);

        // Fill vector with random numbers
        for (auto& x : v)
            x = dist(gen);

        auto start = std::chrono::high_resolution_clock::now();
        insertionSort(v);
        auto end = std::chrono::high_resolution_clock::now();

        double elapsed =
            std::chrono::duration<double>(end - start).count();

        std::cout << n << "\t" << elapsed << "\n";
    }

    return 0;
}
