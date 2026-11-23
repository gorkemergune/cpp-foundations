// ============================================================================
//  Lab 40 · Hash functions and chaining · YOU WORK HERE
//  Test everything:      .\run.ps1 L40
// ============================================================================
#include "lab40.h"

#include <unordered_map>

#include "todo.h"

using namespace std;

// L40-A · Example: "ali", 10  =>  (97 + 108 + 105) % 10 = 0
int hashSum(const string& key, int tableSize) {
    TODO();
}

// L40-B · Example: "ali", 10007  =>  (97*37*37 + 108*37 + 105) % 10007 = 6803
int hash37(const string& key, int tableSize) {
    TODO();
}

// L40-M1 · Example: size 10, insert 12, 22, -3  =>  bucket 2: 12 22, bucket 7: -3
ChainTable::ChainTable(int size) {
    TODO();
}

int ChainTable::indexOf(int key) const {
    TODO();
}

bool ChainTable::insert(int key) {
    TODO();
}

bool ChainTable::contains(int key) const {
    TODO();
}

bool ChainTable::remove(int key) {
    TODO();
}

int ChainTable::size() const {
    TODO();
}

vector<int> ChainTable::bucket(int b) const {
    TODO();
}

int ChainTable::longestChain() const {
    TODO();
}

// L40-M2 · Example: "AAA"  =>  656565;  "a"  =>  -1
int encodeString(const string& s) {
    TODO();
}

// L40-M3 · Example: insertInt(656565), then insertString("AAA")  =>  true (a different entry)
MixedTable::MixedTable() {
    TODO();
}

bool MixedTable::has(int code, bool isString) const {
    TODO();
}

bool MixedTable::add(int code, bool isString) {
    TODO();
}

bool MixedTable::insertInt(int x) {
    TODO();
}

bool MixedTable::insertString(const string& s) {
    TODO();
}

bool MixedTable::containsInt(int x) const {
    TODO();
}

bool MixedTable::containsString(const string& s) const {
    TODO();
}

// L40-X · Example: {2, 7, 11, 15}, 9  =>  (0, 1)
pair<int, int> twoSum(const vector<int>& nums, int target) {
    TODO();
}
