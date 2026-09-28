#include <iostream>
#include "string"


int main() {

    int age;
    std::string name;

    std::cout << "Enter your name and age: ";
    std::cin >> name >> age;

    std::cout << "Hello, " << name << "! You are " << age << " years old." << std::endl;

    std::string full_name;
    int age2;
    std::cout << "Enter your full name and age: ";
    std::getline(std::cin >> std::ws, full_name); // Use std::ws to consume any leading whitespace
    std::cin >> age2;
    std::cout << "Hello, " << full_name << "! You are " << age2 << " years old." << std::endl;

    return 0;
}