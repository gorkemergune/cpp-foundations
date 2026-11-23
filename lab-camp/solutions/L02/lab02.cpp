// Lab 02 · Reference solution. Look at it only after you tried yourself.
#include "lab02.h"

using namespace std;

// @begin addToEach
void addToEach(vector<int>& v, int d) {
    for (int& x : v) {      // int& : x IS the element, not a copy
        x += d;
    }
}
// @end addToEach

// @begin indexOf
int indexOf(const vector<int>& v, int x) {
    for (int i = 0; i < (int)v.size(); i++) {
        if (v[i] == x) return i;    // first match wins
    }
    return -1;
}
// @end indexOf

// @begin removeAt
bool removeAt(vector<int>& v, int index) {
    int n = v.size();
    if (index < 0 || index >= n) return false;  // nothing to remove: v untouched

    for (int i = index; i < n - 1; i++) {
        v[i] = v[i + 1];                        // shift LEFT, walking forward
    }
    v.pop_back();                               // last slot is now a duplicate
    return true;
}
// @end removeAt

// @begin insertAt
bool insertAt(vector<int>& v, int index, int value) {
    int n = v.size();
    if (index < 0 || index > n) return false;   // index == n is allowed (append)

    v.push_back(value);                         // size n+1: one more slot at the end
    for (int i = n; i > index; i--) {
        v[i] = v[i - 1];                        // shift RIGHT, walking backward
    }
    v[index] = value;
    return true;
}
// @end insertAt

// @begin removeElement
int removeElement(vector<int>& nums, int val) {
    int k = 0;                                  // next free position of the kept part
    for (int i = 0; i < (int)nums.size(); i++) {
        if (nums[i] != val) {
            nums[k] = nums[i];
            k++;
        }
    }
    return k;
}
// @end removeElement

// @begin moveToFront
bool moveToFront(vector<int>& v, int index) {
    if (index < 0 || index >= (int)v.size()) return false;
    int x = v[index];                           // save it before it is overwritten
    for (int i = index; i > 0; i--) {
        v[i] = v[i - 1];
    }
    v[0] = x;
    return true;
}
// @end moveToFront
