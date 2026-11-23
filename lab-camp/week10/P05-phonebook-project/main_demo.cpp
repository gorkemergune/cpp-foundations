// Mini Project 05 · the finished program:
//   g++ -std=c++17 -Wall -I../../framework main_demo.cpp phonebook.cpp -o phonebook.exe
//   Commands: add <name> <phone> | find <name> | del <name> | list <prefix> | save | quit
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "phonebook.h"

int main() {
    PhoneBook book;
    std::ifstream file("contacts.txt");
    book.load(file);
    std::cout << book.size() << " contacts, tree height " << book.height() << "\n";
    std::string line;
    while (std::cout << "> " && std::getline(std::cin, line)) {
        std::istringstream in(line);
        std::string cmd, name, phone;
        in >> cmd >> name >> phone;
        if (cmd == "quit") break;
        if (cmd == "add") std::cout << (book.add(name, phone) ? "added" : "already there") << "\n";
        else if (cmd == "find") std::cout << (book.find(name, phone) ? phone : "not found") << "\n";
        else if (cmd == "del") std::cout << (book.remove(name) ? "removed" : "not found") << "\n";
        else if (cmd == "list") {
            for (const std::string& n : book.namesWithPrefix(name)) std::cout << n << " ";
            std::cout << "\n";
        } else if (cmd == "save") {
            std::ofstream out("contacts.txt");
            book.save(out);
            std::cout << "saved " << book.size() << " contacts\n";
        }
    }
    return 0;
}
