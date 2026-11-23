// ============================================================================
//  Lab 06 · function templates · YOU WORK HERE (this header) and in lab06.cpp
//  Test everything:      .\run.ps1 L06
// ============================================================================
#pragma once

#include <array>
#include <cstddef>
#include <vector>

#include "todo.h"

// L06-A · Largest element of a non-empty vector of ANY comparable type T.
// Example: maxOf(std::vector<int>{3, 9, 2}) == 9, maxOf(std::vector<std::string>{"b", "a"}) == "b"
template <typename T>
T maxOf(const std::vector<T>& v) {
    TODO();
}

// L06-B · Number of elements > 0 in a std::array of any length N.
// Example: countPositive(std::array<int, 4>{3, -1, 0, 8}) == 2
template <std::size_t N>
int countPositive(const std::array<int, N>& a) {
    TODO();
}

// L06-V · Reverse a std::array in place (any element type, any length).
// Example: {1, 2, 3} -> {3, 2, 1}
template <typename T, std::size_t N>
void reverseArray(std::array<T, N>& a) {
    TODO();
}
