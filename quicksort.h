//
// Created by bcier on 1/8/2025.
//

#ifndef QUICKSORT_H
#define QUICKSORT_H
void quicksort_parallel(int * __restrict__ A, long low, long high, long cutoff = 10000);
void quicksort_serial(int * __restrict__ A, long low, long high);
#endif //QUICKSORT_H
