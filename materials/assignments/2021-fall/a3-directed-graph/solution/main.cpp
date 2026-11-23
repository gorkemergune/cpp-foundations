// Assignment 3 (2021) · g++ -std=c++17 main.cpp IntSLList.cpp   (run in this folder: in.txt)
#include <iostream>
#include <string>

#include "intDrGraph.h"

int main() {
    std::string filename = "in.txt";
    std::cout << "File: " << filename << "\n";
    intDrGraph g(filename);
    std::cout << "Adjacency lists:\n";
    g.printAdjList();
    std::cout << "BFS from 1: ";
    g.performBFS(1);
    std::cout << "Way from 5 to 11? " << (g.isThereWay(5, 11) ? "yes" : "no") << "\n";
    std::cout << "Routes from 1 to 8:\n";
    g.findRoutes(1, 8);
}
