#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>

#include "sos.h"

// Shell sort (gap sequence: n/2, n/4, ..., 1)
void shellSort(std::vector<double>& v)
{
    const std::size_t n = v.size();
    for (std::size_t gap = n / 2; gap > 0; gap /= 2)
    {
        for (std::size_t i = gap; i < n; ++i)
        {
            double temp = v[i];
            std::size_t j = i;

            while (j >= gap && v[j - gap] > temp)
            {
                v[j] = v[j - gap];
                j -= gap;
            }
            v[j] = temp;
        }
    }
}

int main()
{
    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    std::ofstream out("results_shell.txt");
    if (!out) {
        std::cerr << "Error: could not open results_shell.txt\n";
        return 1;
    }

    out << "n\tt\tdt\n";
    std::cout << "n\tmean_t(s)\terr_t(s)\n";
    std::cout << "------------------------------\n";

    const int trials = 20;

    // Larger sizes than insertion sort (shell sort is faster)
    for (int n = 1000; n <= 200000; n *= 2)
    {
        Sos stats;

        for (int k = 0; k < trials; ++k)
        {
            std::vector<double> v(n);
            for (auto& x : v) x = dist(gen);

            auto start = std::chrono::high_resolution_clock::now();
            shellSort(v);
            auto end = std::chrono::high_resolution_clock::now();

            double elapsed = std::chrono::duration<double>(end - start).count();
            stats += elapsed;
        }

        double t  = stats.av();
        double dt = stats.err();

        out << n << "\t" << t << "\t" << dt << "\n";
        std::cout << n << "\t" << t << "\t" << dt << "\n";
    }

    std::cout << "\nSaved: results_shell.txt (columns: n, t, dt)\n";
    return 0;
}
