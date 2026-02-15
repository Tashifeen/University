// Allows us to print output to the terminal (std::cout)
#include <iostream>

// Provides the std::vector container (dynamic array)
#include <vector>

// Provides random number generation tools
#include <random>

// Provides timing utilities (clocks, durations)
#include <chrono>


// ------------------------------------------------------------
// Function: insertionSort
// Sorts a vector of doubles using the insertion sort algorithm
// ------------------------------------------------------------
void insertionSort(std::vector<double>& v)
{
    // Start at index 1 (the first element is treated as already sorted)
    for (std::size_t i = 1; i < v.size(); ++i)
    {
        // Store the current value we want to insert
        double key = v[i];

        // j keeps track of the position where we compare backwards
        std::size_t j = i;

        // Move elements that are larger than 'key'
        // one position to the right
        while (j > 0 && v[j - 1] > key)
        {
            v[j] = v[j - 1];
            --j;  // move left
        }

        // Place the value (key) in its correct sorted position
        v[j] = key;
    }
}


// ------------------------------------------------------------
// main() is where the program starts executing
// ------------------------------------------------------------
int main()
{
    // Number of random values we want to sort
    const std::size_t n = 1000;

    // Create a vector (dynamic array) of size 1000
    std::vector<double> v(n);

    // Set up random number generator
    // mt19937 is a commonly used high-quality random engine
    std::mt19937 gen(std::random_device{}());

    // Generate random doubles between 0.0 and 1.0
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    // Fill the vector with random numbers
    for (auto& x : v)
        x = dist(gen);

    // Start timing right before sorting
    auto start = std::chrono::high_resolution_clock::now();

    // Sort the vector
    insertionSort(v);

    // Stop timing immediately after sorting
    auto end = std::chrono::high_resolution_clock::now();

    // Compute how much time passed
    std::chrono::duration<double> elapsed = end - start;

    // Print the time (in seconds)
    std::cout << "Time to sort 1000 doubles: "
              << elapsed.count()
              << " seconds\n";

    return 0;  // Indicates successful program execution
}
