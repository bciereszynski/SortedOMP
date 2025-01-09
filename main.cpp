#include <iostream>
#include <cstdint>
#include <random>
#include <chrono>

// ReSharper disable once CppUnusedIncludeDirective
#include <omp.h>

#include "mergesort.h"
#include "quicksort.h"


int main()
{
    constexpr size_t arraySize = 100000000;
    constexpr bool verbose = true;

    auto* numbers_serial_merge = new int32_t[arraySize];
    auto* numbers_serial_quick = new int32_t[arraySize];
    auto* numbers_merge = new int32_t[arraySize];
    auto* numbers_quick = new int32_t[arraySize];


    // data generation
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, INT32_MAX);

        for (std::size_t i = 0; i < arraySize; ++i) {
            const int32_t value = dis(gen);
            numbers_serial_quick[i] = value;
            numbers_serial_merge[i] = value;
            numbers_quick[i] = value;
            numbers_merge[i] = value;
        }
    }

    // quicksort parallel
    {
        if (verbose) {
            std::cout << "Starting quicksort parallel..." <<std::endl;
        }
        const auto start_parallel = std::chrono::high_resolution_clock::now();
        #pragma omp parallel default(none) shared(numbers_quick, arraySize) num_threads(6)
        {
        #pragma omp single nowait
            quicksort_parallel(numbers_quick, 0, arraySize - 1);
        }
        const auto end_parallel = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double> elapsed_parallel = end_parallel - start_parallel;
        std::cout<< elapsed_parallel.count() << std::endl;
    }

    // quicksort serial
    {
        if (verbose) {
            std::cout << "Starting quicksort serial..." <<std::endl;
        }

        const auto start_serial = std::chrono::high_resolution_clock::now();
        quicksort_serial(numbers_serial_quick, 0, arraySize - 1);
        const auto end_serial = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double> elapsed_serial = end_serial - start_serial;
        std::cout<< elapsed_serial.count() << std::endl;
    }

    // mergesort parallel
    {
        if (verbose) {
            std::cout << "Starting mergesort parallel..." << std::endl;
        }
        const auto start_parallel = std::chrono::high_resolution_clock::now();
        #pragma omp parallel default(none) shared(numbers_merge, arraySize) num_threads(6)
        {
        #pragma omp single nowait
            mergesort_parallel(numbers_merge, 0, arraySize - 1);
        }
        const auto end_parallel = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double> elapsed_parallel = end_parallel - start_parallel;
        std::cout<< elapsed_parallel.count() << std::endl;
    }

    // mergesort serial
    {
        if (verbose) {
            std::cout << "Starting mergesort serial..." <<std::endl;
        }

        const auto start_serial = std::chrono::high_resolution_clock::now();
        mergesort_serial(numbers_serial_merge, 0, arraySize - 1);
        const auto end_serial = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double> elapsed_serial = end_serial - start_serial;
        std::cout<< elapsed_serial.count() << std::endl;
    }

    // validation
    {
        if (verbose) {
            std::cout << "Output validation..." <<std::endl;
        }
        auto end = false;
        for (std::size_t i = 0; i < arraySize; ++i) {
            if (numbers_serial_quick[i] != numbers_quick[i]) {
                std::cout << "Error - quicksort! " << i << ": " << numbers_serial_quick[i] << " != " <<
                    numbers_quick[i] << std::endl;
                end = true;
            }
            if (numbers_serial_quick[i] != numbers_serial_merge[i]) {
                std::cout << "Error - integration! " << i << ": " << numbers_serial_quick[i] << " != " <<
                    numbers_serial_merge[i] << std::endl;
                end = true;
            }
            if (numbers_serial_merge[i] != numbers_merge[i]) {
                std::cout << "Error - mergesort! " << i << ": " << numbers_serial_merge[i] << " != " <<
                    numbers_merge[i] << std::endl;
                end = true;
            }
            if(end) {
                break;
            }
        }
    }

    delete[] numbers_serial_quick;
    delete[] numbers_quick;
    return 0;
}
