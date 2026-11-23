// Lab 06 · Warm-up. Predict every output line on paper first, then compile:
//   g++ -std=c++17 -Wall warmup.cpp -o warmup.exe
#include <array>
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

template <typename T>
T bigger(T a, T b) {                       // one definition, many types
    return a < b ? b : a;
}

int main() {
    array<int, 4> a = {5, 1, 4};           // the missing element becomes 0
    cout << "1) size=" << a.size() << " last=" << a[3] << "\n";
    array<int, 4> b = a;                   // a std::array is COPIED (a C array cannot be)
    b[0] = 100;
    cout << "2) a[0]=" << a[0] << " b[0]=" << b[0] << "\n";
    cout << "3) " << bigger(3, 8) << " " << bigger(2.5, 1.5) << " ";
    cout << bigger<string>("pear", "apple") << "\n";
    try {
        cout << a.at(4) << "\n";           // at() checks the index
    } catch (const out_of_range&) {
        cout << "4) at(4) threw out_of_range\n";
    }
    int sum = 0;
    for (int x : a) sum += x;              // range-for knows the length
    cout << "5) sum=" << sum << "\n";
    return 0;
}
