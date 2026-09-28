#include <iostream>
#include "string"

int main() {
    
    int age;
    std::string name;
    
    std::cout << "Enter your age: " << std::endl;
    std::cin >> age;
    std::cout << "You entered: " << age << std::endl;

    std::cout << "Enter your name: " << std::endl;
    std::cin >> name;
    std::cout << "You entered: " << name << std::endl;

    std::cerr << "This is an error message" << std::endl; 
    std::clog << "This is a log message" << std::endl;

    

    return 0;
}

