// Mini Project 06 · the finished program:
//   g++ -std=c++17 -Wall -I../../framework main_demo.cpp triage.cpp -o triage.exe
//   Commands: arrive <name> <severity 1-5> | treat | up <name> <severity> | leave <name> | quit
#include <iostream>
#include <sstream>
#include <string>

#include "triage.h"

int main() {
    Triage er;
    std::string line;
    while (std::cout << "> " && std::getline(std::cin, line)) {
        std::istringstream in(line);
        std::string cmd, name;
        int severity = 0;
        in >> cmd >> name >> severity;
        if (cmd == "quit") break;
        if (cmd == "arrive") er.arrive(name, severity);
        else if (cmd == "treat") std::cout << (er.treat(name) ? "treating " + name : "nobody is waiting") << "\n";
        else if (cmd == "up") std::cout << (er.upgrade(name, severity) ? "upgraded" : "not changed") << "\n";
        else if (cmd == "leave") std::cout << (er.leave(name) ? "left" : "not waiting") << "\n";
        std::cout << "queue: " << er.report() << "\n";
    }
    return 0;
}
