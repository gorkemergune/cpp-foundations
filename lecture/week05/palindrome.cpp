#include <iostream>
#include <stack>
#include <queue>

int main() {

    std::string input;
    std::cout << "Enter a string: ";
    std::getline(std::cin, input);

    std::stack<char> charStack;
    std::queue<char> charQueue;

    for (char c : input) {
        if (std::isalpha(c)) {
            charStack.push(std::tolower(c));
            charQueue.push(std::tolower(c));
        }
    }

    bool isPalindrome = true;
    while (!charStack.empty() && !charQueue.empty()) {
        if (charStack.top() != charQueue.front()) {
            isPalindrome = false;
            break;
        }
        charStack.pop();
        charQueue.pop();
    }

    if (isPalindrome) {
        std::cout << "The string is a palindrome." << std::endl;
    } else {
        std::cout << "The string is not a palindrome." << std::endl;
    }

    return 0;


}