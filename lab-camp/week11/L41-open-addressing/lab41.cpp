// ============================================================================
//  Lab 41 · Open addressing · YOU WORK HERE
//  Test everything:      .\run.ps1 L41
// ============================================================================
#include "lab41.h"

#include "todo.h"

using namespace std;

OpenTable::OpenTable(int size, Probing mode) {
    TODO();
}

// L41-A · Example: size 11, key 24, quadratic: i = 0, 1, 2  =>  2, 3, 6
int OpenTable::probe(int key, int i) const {
    TODO();
}

// L41-B · Example: an empty table of size 3  =>  "_ _ _"
string OpenTable::layout() const {
    TODO();
}

// L41-M1 · Example: linear, size 11: 20 30 2 13 25 24  =>  24 lands in slot 5
int OpenTable::insert(int key) {
    TODO();
}

// L41-M2 · Example: after removing 13 (slot 3), find 24  =>  5 (passes the DELETED slot)
int OpenTable::find(int key) const {
    TODO();
}

// L41-M3 · Example: remove 13  =>  true, its slot shows "x"
bool OpenTable::remove(int key) {
    TODO();
}

// L41-X · Example: size 5 with 1 6  =>  size 11 (first prime >= 10), keys 1 6
void OpenTable::rehash() {
    TODO();
}

// L41-V · Example: "9 _ 2 13 25 24 _ _ 30 20 10"  =>  4
int OpenTable::longestCluster() const {
    TODO();
}
