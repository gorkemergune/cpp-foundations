// Lab 02 · Alternative solutions shown in the PDF. Standalone program.
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

// @begin stl
bool removeAtSTL(vector<int>& v, int index) {
    if (index < 0 || index >= (int)v.size()) return false;
    v.erase(v.begin() + index);           // not allowed in this lab
    return true;
}
bool insertAtSTL(vector<int>& v, int index, int value) {
    if (index < 0 || index > (int)v.size()) return false;
    v.insert(v.begin() + index, value);   // not allowed in this lab
    return true;
}
// @end stl

// @begin wrongShift
// WRONG direction: walking forward overwrites values before they are copied.
void shiftRightWrong(vector<int>& v, int index) {
    for (int i = index + 1; i < (int)v.size(); i++) {
        v[i] = v[i - 1];
    }
}
// @end wrongShift

int main() {
    vector<int> v = {4, 7, 2, 9};
    assert(removeAtSTL(v, 1) && (v == vector<int>{4, 2, 9}));
    assert(insertAtSTL(v, 1, 7) && (v == vector<int>{4, 7, 2, 9}));
    assert(!removeAtSTL(v, 4) && !insertAtSTL(v, 5, 1));
    vector<int> w = {4, 2, 9, 9};
    shiftRightWrong(w, 1);
    assert((w == vector<int>{4, 2, 2, 2}));   // the bug shown in the PDF
    cout << "alternatives OK\n";
    return 0;
}
