#include "iostream"
#include "stack"
using namespace std;

bool is_balanced(std::string s) {
    stack<char> stack;
    for (char c : s) {
        if (c == '{') {
            stack.push(c);
        } else if (c == '}') {
            if (stack.empty()) {
                return false;
            }
            stack.pop();
        }
    }
    return stack.empty();
}


int main() {

    // abc{df}g{l} --> balanced eşit sayıda { }
    // a{bc{df}g{l --> unbalanced eşit sayıda deil { }

    // string ile çözersek
    /*
    while (string) {
        int l = 0, r = 0;
        if (s[i] == '{') {
            l++;
        } else if (s[i] == '}') {
            r++;
        }
        if (l == r) {
            return true;
        } else {
            return false;
        }
    }
    */

    // stack ile çözersek


}