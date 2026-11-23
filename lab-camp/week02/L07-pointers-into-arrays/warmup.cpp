// Lab 07 · Paper trace. Fill the table in the PDF on paper FIRST, then compile:
//   g++ -std=c++17 -Wall warmup.cpp -o warmup.exe
#include <iostream>
using namespace std;

static void show(const char* step, const int a[5]) {
    cout << step << "  a = {" << a[0] << ", " << a[1] << ", " << a[2] << ", " << a[3] << ", "
         << a[4] << "}\n";
}

int main() {
    int a[5] = {10, 20, 30, 40, 50};
    int* p = a;                           // 1) p points at a[0]
    cout << "1) *p = " << *p << "\n";
    p += 2;                               // 2) move two ELEMENTS (not bytes)
    cout << "2) *p = " << *p << ", p - a = " << p - a << "\n";
    *p = 7;                               // 3) write through p
    show("3)", a);
    int* q = &a[4];                       // 4) q points at the last element
    cout << "4) q - p = " << q - p << ", *(p - 1) = " << *(p - 1) << "\n";
    p++;                                  // 5) p moves to a[3]
    *p += 1;
    show("5)", a);
    int* end = a + 5;                     // 6) one past the last element: never read *end
    int count = 0;
    for (int* r = a; r != end; r++) count += (*r > 25);
    cout << "6) values > 25: " << count << "\n";
    int m[2][3] = {{1, 2, 3}, {4, 5, 6}}; // 7) rows are stored one after another
    int* flat = &m[0][0];
    cout << "7) m[1][0] = " << m[1][0] << ", flat[3] = " << flat[3] << "\n";
    return 0;
}
