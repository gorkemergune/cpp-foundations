// ============================================================================
//  Lab 06 · function templates · YOU WORK HERE (this header) and in lab06.cpp
//  Reference solution. @solution-note
//  Test everything:      .\run.ps1 L06
// ============================================================================
#pragma once

#include <array>
#include <cstddef>
#include <vector>

#include "todo.h"

// L06-A · Largest element of a non-empty vector of ANY comparable type T.
// Example: maxOf(std::vector<int>{3, 9, 2}) == 9, maxOf(std::vector<std::string>{"b", "a"}) == "b"
// @begin maxOf
template <typename T>
T maxOf(const std::vector<T>& v) {
    T best = v[0];                     // precondition: v is not empty
    for (const T& x : v)               // const T&: no copy of big objects (strings)
        if (best < x) best = x;        // only operator< is required from T
    return best;
}
// @end maxOf

// L06-B · Number of elements > 0 in a std::array of any length N.
// Example: countPositive(std::array<int, 4>{3, -1, 0, 8}) == 2
// @begin countPositive
template <std::size_t N>
int countPositive(const std::array<int, N>& a) {
    int count = 0;
    for (int x : a)
        if (x > 0) count++;
    return count;
}
// @end countPositive

// L06-V · Reverse a std::array in place (any element type, any length).
// Example: {1, 2, 3} -> {3, 2, 1}
// @begin reverseArray
template <typename T, std::size_t N>
void reverseArray(std::array<T, N>& a) {
    for (std::size_t i = 0; i < N / 2; i++) {
        T tmp = a[i];
        a[i] = a[N - 1 - i];
        a[N - 1 - i] = tmp;
    }
}
// @end reverseArray
