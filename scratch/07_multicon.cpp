#include <iostream>

int main() {

    int a, b;
    std::cin >> a >> b;

    while (a <= b) {

        if (a == 1) {
            std::cout << "one\n";
        } else if (a == 2) {
            std::cout << "two\n";
        } else if (a == 3) {
            std::cout << "three\n";
        } else if (a == 4) {
            std::cout << "four\n";
        } else if (a == 5) {
            std::cout << "five\n";
        } else if (a == 6) {
            std::cout << "six\n";
        } else if (a == 7) {
            std::cout << "seven\n";
        } else if (a == 8) {
            std::cout << "eight\n";
        } else if (a == 9) {
            std::cout << "nine\n";
        } else if (a % 2 == 0) {
            std::cout << "even\n";
        } else {
            std::cout << "odd\n";
        }

        a++;
    }

    return 0;
}