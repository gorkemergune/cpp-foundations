// Labwork 3 · example main (g++ -std=c++17 main.cpp palindrome.cpp)
#include <iostream>

#include "palindrome.h"

int main() {
    std::cout << is_palindrome("ey edip adanada pide ye") << "\n";  // 1
    std::cout << is_palindrome("test") << "\n";                     // 0
    std::cout << is_palindrome("mum") << "\n";                      // 1
}
