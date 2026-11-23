#include <iostream>

int find_max(int a, int b, int c) {
    int max = a;
    if (b > max) {
        max = b;
    }
    if (c > max) {
        max = c;
    }
    return max;
}

int main () {
    int a, b, c;
    std::cout << "Enter three integers: ";
    std::cin >> a >> b >> c;
    int max = find_max(a, b, c);
    std::cout << "The maximum value is: " << max << std::endl;
    return 0;
}