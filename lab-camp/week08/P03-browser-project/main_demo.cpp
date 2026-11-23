// Mini Project 03 · the finished program:
//   g++ -std=c++17 -Wall -I../../framework main_demo.cpp browser.cpp -o browser.exe
//   Commands: visit <url> | back <n> | forward <n> | get <file> <MB> | tick <MB> | quit
#include <iostream>
#include <sstream>
#include <string>

#include "browser.h"

int main() {
    Browser b("home");
    std::string line;
    while (std::cout << "> " && std::getline(std::cin, line)) {
        std::istringstream in(line);
        std::string cmd, arg;
        int n = 0;
        in >> cmd;
        if (cmd == "quit") break;
        if (cmd == "visit" && in >> arg) b.visit(arg);
        else if (cmd == "back" && in >> n) b.back(n);
        else if (cmd == "forward" && in >> n) b.forward(n);
        else if (cmd == "get" && in >> arg >> n) b.download(arg, n);
        else if (cmd == "tick" && in >> n) {
            for (const std::string& f : b.tick(n)) std::cout << "finished: " << f << "\n";
        }
        std::cout << b.historyReport() << " | downloads: " << b.pendingDownloads() << "\n";
    }
    return 0;
}
