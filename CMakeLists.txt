cmake_minimum_required(VERSION 3.31)
project(SortedOMP)

find_package(OpenMP REQUIRED)

set(CMAKE_CXX_STANDARD 23)

add_executable(SortedOMP main.cpp
        quicksort.h
        quicksort.cpp)
target_link_libraries(${PROJECT_NAME} OpenMP::OpenMP_C)