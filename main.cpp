#include <iostream>
#include <cstdint>
#include <random>
#include <chrono>

#include <omp.h>
#include "quicksort.h"



int main()
{
    const size_t arraySize = 100000000;
    const bool verbose = true;

    int32_t* numbers = new int32_t[arraySize];
    int32_t* numbers_serial = new int32_t[arraySize];

    std::srand(std::time(nullptr));

    for (std::size_t i = 0; i < arraySize; ++i) {
        numbers[i] = std::rand();
    }
    std::copy_n(numbers, arraySize, numbers_serial);

    if (verbose) {
        std::cout << "Starting quicksort serial" <<std::endl;
    }

    auto start_serial = std::chrono::high_resolution_clock::now();
    quicksort_serial(numbers_serial, 0, arraySize - 1);
    auto end_serial = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_serial = end_serial - start_serial;
    std::cout<< elapsed_serial.count() << std::endl;

    if (verbose) {
        std::cout << "Starting quicksort parallel" <<std::endl;
    }
    auto start_parallel = std::chrono::high_resolution_clock::now();
    #pragma omp parallel default(none) shared(numbers, arraySize)
    {
        #pragma omp single nowait
        quicksort_parallel(numbers, 0, arraySize - 1);
    }
    auto end_parallel = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_parallel = end_parallel - start_parallel;
    std::cout<< elapsed_parallel.count() << std::endl;

    for (std::size_t i = 0; i < arraySize; ++i) {
        if (numbers[i] != numbers_serial[i]) {
            std::cout << "Error - " << i << ": " << numbers_serial[i] << " != " << numbers[i] << std::endl;
        }
    }
    delete[] numbers;
    delete[] numbers_serial;
    return 0;
}
