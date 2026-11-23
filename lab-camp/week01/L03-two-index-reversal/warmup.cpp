// Lab 03 · Warm-up. Predict every output line on paper first, then compile:
//   g++ -std=c++17 -Wall warmup.cpp -o warmup.exe
//   .\warmup.exe
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int main() {
    vector<int> e;                                  // empty
    cout << "1) e.size() - 1      = " << e.size() - 1 << "\n";
    cout << "2) (int)e.size() - 1 = " << (int)e.size() - 1 << "\n";

    int a = 3, b = 8;
    swap(a, b);                                     // std::swap exchanges two values
    cout << "3) a=" << a << " b=" << b << "\n";

    vector<int> v = {1, 2, 3, 4, 5};
    swap(v[0], v[4]);                               // works on elements too
    cout << "4)";
    for (int x : v) cout << " " << x;
    cout << "\n";

    int lo = 1, hi = 3;
    while (lo < hi) {                               // two indexes walk toward each other
        swap(v[lo], v[hi]);
        lo++;
        hi--;
    }
    cout << "5)";
    for (int x : v) cout << " " << x;
    cout << "  lo=" << lo << " hi=" << hi << "\n";
    return 0;
}
