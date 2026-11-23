// Labwork 8 Q2 · g++ -std=c++17 main.cpp heap.cpp
#include <iostream>

#include "heap.h"

int main() {
    int data[] = {13, 10, 9, 12, 55, 23, 34, 1, 2};
    const int n = sizeof(data) / sizeof(data[0]);
    heap h(data, n);
    std::cout << "heap:  ";
    h.print();
    for (int i = 0; i < n; i++) {
        h.delete_min();
        std::cout << "step " << i + 1 << ": ";
        h.print();
    }
}
