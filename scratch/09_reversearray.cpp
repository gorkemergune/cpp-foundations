#include <iostream>

int main() {

    int a, b;
    std::cin >> a;

    int arr[1000];

    for (int i = 0; i < a; i++) {
        std::cin >> b;
        arr[i] = b;
    }

    for (int i = a - 1; i >= 0; i--) {
        std::cout << arr[i] << " ";
    }

    return 0;
}


/*

use arr[SIZE] --> we should use vector

#include <iostream>
#include <vector>

int main() {

    int a, b;
    std::cin >> a;

    std::vector<int> arr(a);

    for (int i = 0; i < a; i++) {
        std::cin >> b;
        arr[i] = b;
    }

    for (int i = a - 1; i >= 0; i--) {
        std::cout << arr[i] << " ";
    }

    return 0;
}

*/