// Lab 21 · Warm-up: empty() and !empty(). Predict every line, then compile:
//   g++ -std=c++17 -Wall warmup.cpp -o warmup.exe
#include <iostream>
#include <stack>
using namespace std;

int main() {
    stack<int> st;
    cout << "1) empty=" << st.empty() << " !empty=" << !st.empty() << "\n";
    st.push(1);
    st.push(2);
    st.push(3);
    cout << "2) empty=" << st.empty() << " !empty=" << !st.empty() << " top=" << st.top() << "\n";

    int rounds = 0;
    while (st.empty()) rounds++;          // WRONG condition: the body never runs here
    cout << "3) rounds with while(empty) = " << rounds << "\n";

    cout << "4) popping:";
    while (!st.empty()) {                 // RIGHT: run while something is left
        cout << " " << st.top();
        st.pop();
    }
    cout << "\n";
    if (!st.empty()) cout << st.top();    // guard: top() on an empty stack is undefined
    else cout << "5) empty again, top() not called\n";
    return 0;
}
