#include "mergesort.h"

// ReSharper disable once CppUnusedIncludeDirective
#include <omp.h>

void merge(int* A, const long p, const long q, const long r) {

    // L = A[p...q] R = A[q+1...r]
    const long len1 = q - p + 1;
    const long len2 = r - q;

    const auto L = new int[len1];
    const auto R = new int[len2];

    for (int i = 0; i < len1; i++)
        L[i] = A[p + i];

    for (int j = 0; j < len2; j++)
        R[j] = A[q + 1 + j];

    long i = 0, j = 0, k = p;

    while (i < len1 && j < len2) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
        k++;
    }

    // move remaining
    while (i < len1) {
        A[k] = L[i];
        i++;
        k++;
    }

    while (j < len2) {
        A[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergesort_serial(int * __restrict__ A, const long low, const long high) {
    if (low >= high)
      return;
    const long m = low + (high - low) / 2;

    mergesort_serial(A, low, m);
    mergesort_serial(A, m + 1, high);

    merge(A, low, m, high);
}

void mergesort_parallel(int * __restrict__ A, const long low, const long high, const long cutoff) {
    if (high<=low)
        return;
    if (high-low<cutoff)
        return mergesort_serial(A,low,high);
    const long m = low + (high - low) / 2;
    #pragma omp task default(none) firstprivate(low,m,A,cutoff)
    mergesort_parallel(A,low,m);
    #pragma omp task default(none) firstprivate(high,m,A,cutoff)
    mergesort_parallel(A,m+1,high);

    #pragma omp taskwait
    merge(A, low, m, high);
}
