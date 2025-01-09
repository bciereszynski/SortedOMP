#ifndef MERGESORT_H
#define MERGESORT_H
void mergesort_serial(int * __restrict__ A, long low, long high);
void mergesort_parallel(int * __restrict__ A, long low, long high, long cutoff = 10000);
#endif //MERGESORT_H
