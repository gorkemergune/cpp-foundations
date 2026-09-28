#include "iostream"

int sum_two_nums(int a, int b) {
    return a + b;
}


int main() {

    int firstNum = 12;
    int secondNum = 9;

    int sum = firstNum + secondNum;

    std::cout << "The sum of " << firstNum << " and " << secondNum << " is " << sum << std::endl;

    std::cout << "The sum of 34 and 8 is: " << sum_two_nums(34, 8) << std::endl;

    return 0;
}