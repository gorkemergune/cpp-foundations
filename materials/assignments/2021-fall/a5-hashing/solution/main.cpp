// Assignment 5 (2021) · g++ -std=c++17 main.cpp hashing.cpp intsllist.cpp
#include <iostream>

#include "hashing.h"

int main() {
    insertIntoHashTable(1);
    insertIntoHashTable(11);
    insertIntoHashTable(6);
    insertIntoHashTable(121);
    insertIntoHashTable("AAA");
    insertIntoHashTable("Y");
    insertIntoHashTable("30E");
    printHashTable();
    std::cout << "search: " << searchInHashTable(11) << searchInHashTable(10) << searchInHashTable(66)
              << searchInHashTable("AAA") << searchInHashTable("AA") << "\n";   // 10010
}
