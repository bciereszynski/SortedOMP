cmake_minimum_required(VERSION 3.31)
project(SortedOMP)

find_package(OpenMP REQUIRED)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")


set(CMAKE_CXX_STANDARD 23)

add_executable(SortedOMP main.cpp
        quicksort.cpp
        mergesort.cpp)
target_link_libraries(${PROJECT_NAME} OpenMP::OpenMP_C)