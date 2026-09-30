#include <iostream>
#include <iterator>

int main() {

    int scores[] {5, 10, 20, 30};

    int sum = 0;

    for (int num : scores) {
        sum += num;
    }

    std::cout << "size: " << std::size(scores) << std::endl;
    


}