// Lab 01 · Warm-up. Predict every output line on paper first, then compile:
//   g++ -std=c++17 -Wall warmup.cpp -o warmup.exe
//   .\warmup.exe
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v;                       // an empty vector of int
    cout << "1) size=" << v.size() << "\n";

    v.push_back(4);                      // append at the end
    v.push_back(7);
    v.push_back(4);
    cout << "2) size=" << v.size() << " v[0]=" << v[0] << " v[2]=" << v[2] << "\n";

    vector<int> w = {5, 1, 8};           // initializer list
    w[1] = 9;                            // [] writes an existing slot
    cout << "3)";
    for (int x : w) cout << " " << x;    // range-for: x is a copy of each element
    cout << "\n";

    v.pop_back();                        // removes the last element, returns nothing
    cout << "4) size=" << v.size() << " back=" << v.back() << "\n";

    for (size_t i = 0; i < w.size(); i++) w[i] = w[i] * 2;
    cout << "5) w = {" << w[0] << ", " << w[1] << ", " << w[2] << "}\n";
    return 0;
}
