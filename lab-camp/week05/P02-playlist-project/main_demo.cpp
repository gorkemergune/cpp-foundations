// Mini Project 02 · the finished program:
//   g++ -std=c++17 -Wall main_demo.cpp playlist.cpp -o playlist.exe
//   Commands: add <seconds> <title> | next | prev | remove <title> | up <title> | quit
#include <iostream>
#include <sstream>
#include <string>

#include "playlist.h"

int main() {
    Playlist p;
    std::string line;
    while (std::cout << "> " && std::getline(std::cin, line)) {
        std::istringstream in(line);
        std::string cmd, title;
        in >> cmd;
        if (cmd == "quit") break;
        if (cmd == "add") {
            int s = 0;
            in >> s;
            std::getline(in >> std::ws, title);
            p.add(title, s);
        } else if (cmd == "next") {
            if (!p.next()) std::cout << "(already the last song)\n";
        } else if (cmd == "prev") {
            if (!p.prev()) std::cout << "(already the first song)\n";
        } else if (cmd == "remove" || cmd == "up") {
            std::getline(in >> std::ws, title);
            bool ok = cmd == "remove" ? p.remove(title) : p.moveUp(title);
            if (!ok) std::cout << "(not possible)\n";
        }
        std::cout << p.listing() << "total " << p.totalSeconds() << " s\n";
    }
    return 0;
}
