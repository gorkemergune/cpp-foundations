#include <iostream>

int main() {

    int a, b, c, d;
    std::cin >> a >> b >> c >> d;

    int max = a;

    if (b > max) {
        max = b;
    } if (c > max) {
        max = c;
    } if (d > max) {
        max = d;
    }
    std::cout << max;

    return 0;
}