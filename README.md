# SortedOMP

SortedOMP is a project that examines **parallel sorting algorithms** implemented with **OpenMP**. It includes parallel versions of **Merge Sort** and **Quick Sort**, allowing for performance testing and comparison on multi-core systems.

---

## Features
- Parallel **Merge Sort** and **Quick Sort** implementations.
- Performance evaluation by sorting large datasets.
- Comparison of serial and parallel versions.

---

## Requirements
- C++ compiler with OpenMP support (e.g., `g++` or `clang`).
- CMake (for building the project).

---

## Build Instructions

Create a build directory and compile:
```bash
   mkdir build && cd build
   cmake ..
   make
```
This will produce an executable (sorted_omp).
