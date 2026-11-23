// Assignment 2 (2021) · g++ -std=c++17 main.cpp editor.cpp codeStack.cpp
#include <iostream>

#include "editor.h"

int main() {
    std::cout << "Commands: text, /delete, /undo, /print, /reversePrint, /exit\n";
    run_editor(std::cin);
}
