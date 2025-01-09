//
// Created by bcier on 1/8/2025.
//
#include "quicksort.h"
#include <algorithm>

#include <omp.h>

long partition(int * __restrict__ A, const long low, const long high) {
    int pivot=A[high];
    long i=low-1;
    for (long j=low;j<=high-1;j++) {
        if (A[j] < pivot) {
            i++;
            std::swap(A[i],A[j]);
        }
    }
    std::swap(A[i + 1],A[high]);
    return i + 1;
}

void quicksort_serial(int * __restrict__ A, const long low, const long high) {
    if (high<=low)
        return;
    const long p=partition(A,low,high);
    quicksort_serial(A,low,p-1);
    quicksort_serial(A,p+1,high);

}

void quicksort_parallel(int * __restrict__ A, const long low, const long high, const long cutoff) {
    if (high<=low)
        return;
    if (high-low<cutoff)
        return quicksort_serial(A,low,high);
    long p=partition(A,low,high);
    #pragma omp task default(none) firstprivate(low,p,A,cutoff)
    quicksort_parallel(A,low,p-1,cutoff);
    #pragma omp task default(none) firstprivate(high,p,A,cutoff)
    quicksort_parallel(A,p+1,high,cutoff);
}




