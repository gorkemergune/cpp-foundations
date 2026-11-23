// Mini Project 04 · the finished program:
//   g++ -std=c++17 -Wall main_demo.cpp metro.cpp -o metro.exe
//   metro.txt: one line per metro line, "M1 Gar Carsi Kampus ..."
//   Commands: route <from> <to> | near <station> <k> | quit
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "metro.h"

int main() {
    Metro m;
    std::ifstream file("metro.txt");
    std::string text;
    while (std::getline(file, text)) {
        std::istringstream in(text);
        std::string line, station;
        std::vector<std::string> stations;
        in >> line;
        while (in >> station) stations.push_back(station);
        m.addLine(line, stations);
    }
    std::cout << m.stationCount() << " stations loaded\n";
    while (std::cout << "> " && std::getline(std::cin, text)) {
        std::istringstream in(text);
        std::string cmd, a, b;
        int k = 0;
        in >> cmd;
        if (cmd == "quit") break;
        if (cmd == "route" && in >> a >> b) {
            std::vector<std::string> r = m.route(a, b);
            if (r.empty()) { std::cout << "no route\n"; continue; }
            for (size_t i = 0; i < r.size(); i++) std::cout << (i ? " -> " : "") << r[i];
            std::cout << "\n" << r.size() - 1 << " stops, " << m.transfers(r) << " transfer(s)\n";
        } else if (cmd == "near" && in >> a >> k) {
            for (const std::string& s : m.withinStops(a, k)) std::cout << s << " ";
            std::cout << "\n";
        }
    }
    return 0;
}
