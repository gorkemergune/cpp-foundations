#include <iostream>
#include <cstring>


int main() {

    int scores [] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int count = sizeof(scores) / sizeof(scores[0]);

    for (size_t i {0} ; i < count ; i++) {
        std::cout << scores[i] << std::endl;
    }
    std::cout << "Count: " << count << std::endl;


    for (auto s : scores) {
        std::cout << s << std::endl;
    }


    char name [] = "Hello World";
    std::string name2 = "Hello World";

    std::cout << name << std::endl;

    for (auto c : name) {
        std::cout << c << std::endl;
    }

    int f = strlen(name);
    int f2 = name2.length();
    



}