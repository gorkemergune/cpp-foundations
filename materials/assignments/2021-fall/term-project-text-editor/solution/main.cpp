// Term project (2021) · g++ -std=c++17 main.cpp editor.cpp
#include <iostream>
#include <string>

#include "editor.h"

int main() {
    TextEditor ed;
    std::string command;
    std::cout << "Commands: open f, save f, insert n text, delete n, move n m, replace n text, next, prev, undo, quit\n";
    while (true) {
        std::cout << ed.page() << "> ";
        if (!std::getline(std::cin, command) || command == "quit") break;
        std::string msg = ed.execute(command);
        if (!msg.empty()) std::cout << msg << "\n";
    }
}
