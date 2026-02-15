#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>

#include "sos.h"   // uses your existing Sos class

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

    std::ofstream out("results.txt");
    if (!out) {
        std::cerr << "Error: could not open results.txt\n";
        return 1;
    }

    // Header row (nice for readability)
    out << "n\tt\tdt\n";
    std::cout << "n\tmean_t(s)\terr_t(s)\n";
    std::cout << "------------------------------\n";

    const int trials = 20;

    for (int n = 10; n < 5000; n *= 2)
    {
        Sos stats;  // collects timing stats for this n

        for (int k = 0; k < trials; ++k)
        {
            std::vector<double> v(n);
            for (auto& x : v) x = dist(gen);

            auto start = std::chrono::high_resolution_clock::now();
            insertionSort(v);
            auto end = std::chrono::high_resolution_clock::now();

            double elapsed = std::chrono::duration<double>(end - start).count();
            stats += elapsed;
        }

        double t  = stats.av();   // mean time
        double dt = stats.err();  // estimated error in mean time (standard error)

        // write to file (3 columns)
        out << n << "\t" << t << "\t" << dt << "\n";

        // also display in terminal
        std::cout << n << "\t" << t << "\t" << dt << "\n";
    }

    out.close();
    std::cout << "\nSaved: results.txt (columns: n, t, dt)\n";
    return 0;
}
