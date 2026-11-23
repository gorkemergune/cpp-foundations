// Mini Project 01 · the finished program. Build it once your tests are green:
//   g++ -std=c++17 -Wall main_demo.cpp gradebook.cpp -o gradebook.exe
//   Get-Content grades.txt | .\gradebook.exe      (or type lines, then Ctrl+Z, Enter)
#include <iostream>

#include "gradebook.h"

int main() {
    Gradebook book;
    int rejected = book.readAll(std::cin);
    std::cout << book.report(60);
    if (rejected > 0) std::cout << "(" << rejected << " line(s) rejected)\n";
    return 0;
}
