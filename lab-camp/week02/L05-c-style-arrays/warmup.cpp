// Lab 05 · Warm-up. Predict every output line on paper first, then compile:
//   g++ -std=c++17 -Wall warmup.cpp -o warmup.exe
//   .\warmup.exe
#include <iostream>
using namespace std;

void inside(int a[]) {   // a is a pointer here (expected warning with -Wall)
    cout << "3) sizeof(a) in the function = " << sizeof(a) << "\n";
    a[0] = 99;           // writes into the caller's array: no copy was made
}

int main() {
    int a[5] = {10, 20, 30};             // missing elements become 0
    cout << "1) sizeof(a) = " << sizeof(a) << ", count = " << sizeof(a) / sizeof(a[0]) << "\n";
    cout << "2) a[3] = " << a[3] << ", a[4] = " << a[4] << "\n";
    inside(a);
    cout << "4) a[0] after the call = " << a[0] << "\n";
    int* p = a;                          // the array name turns into &a[0]
    cout << "5) *p = " << *p << ", p[2] = " << p[2] << ", *(p + 1) = " << *(p + 1) << "\n";
    const int N = 3;
    int b[N];                            // size must be a constant; contents are garbage
    for (int i = 0; i < N; i++) b[i] = a[i] + 1;
    cout << "6) b = " << b[0] << " " << b[1] << " " << b[2] << "\n";
    return 0;
}
