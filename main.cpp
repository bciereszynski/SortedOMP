#include <iostream>
#include <cstdint>
#include <random>

#include "quicksort.h"



int main()
{
    const size_t arraySize = 10;
    int32_t* numbers = new int32_t[arraySize];

    std::srand(std::time(nullptr));

    for (std::size_t i = 0; i < arraySize; ++i) {
        numbers[i] = std::rand();
    }

    std::cout << "Generated array:" << std::endl;
    for (std::size_t i = 0; i < arraySize; ++i) {
        std::cout << i << ": " << numbers[i] << std::endl;
    }

    quicksort_parallel(numbers, 0, arraySize - 1);

    std::cout << "Sorted array:" << std::endl;
    for (std::size_t i = 0; i < arraySize; ++i) {
        std::cout << i << ": " << numbers[i] << std::endl;
    }
    delete[] numbers;
    return 0;
}
