// Lab 02 · Warm-up. Predict every output line on paper first, then compile:
//   g++ -std=c++17 -Wall warmup.cpp -o warmup.exe
//   .\warmup.exe
#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

void byValue(vector<int> v) { v[0] = 100; }        // changes a copy
void byRef(vector<int>& v) { v[0] = 100; }         // changes the caller's vector
int firstOf(const vector<int>& v) { return v[0]; } // v[0] = 1; would not compile

int main() {
    vector<int> a = {1, 2, 3};
    byValue(a);
    cout << "1) a[0]=" << a[0] << "\n";
    byRef(a);
    cout << "2) a[0]=" << a[0] << " first=" << firstOf(a) << "\n";

    for (int x : a) x = 0;              // x is a copy (expected warning with -Wall)
    cout << "3) " << a[0] << " " << a[1] << " " << a[2] << "\n";
    for (int& x : a) x = x + 1;         // x is another name for each element
    cout << "4) " << a[0] << " " << a[1] << " " << a[2] << "\n";

    vector<int> b;
    b.reserve(10);                      // room for 10, but still no elements
    cout << "5) size=" << b.size() << " capacity=" << b.capacity() << "\n";
    b.resize(3);                        // now 3 elements, all 0
    cout << "6) size=" << b.size() << " capacity=" << b.capacity() << " b[2]=" << b[2] << "\n";
    b.resize(1);
    cout << "7) size=" << b.size() << " capacity=" << b.capacity() << "\n";

    cout << "8) a.at(1)=" << a.at(1) << "\n";
    try {
        cout << a.at(5) << "\n";        // at() checks the index, [] does not
    } catch (const out_of_range&) {
        cout << "9) a.at(5) threw out_of_range\n";
    }
    return 0;
}
