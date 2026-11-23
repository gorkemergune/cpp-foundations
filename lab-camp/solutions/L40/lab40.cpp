// ============================================================================
//  Lab 40 · Hash functions and chaining · YOU WORK HERE
//  Reference solution. @solution-note
//  Test everything:      .\run.ps1 L40
// ============================================================================
#include "lab40.h"

#include <unordered_map>

#include "todo.h"

using namespace std;

// L40-A · Example: "ali", 10  =>  (97 + 108 + 105) % 10 = 0
// @begin hashSum
int hashSum(const string& key, int tableSize) {
    int h = 0;
    for (char c : key) h += (unsigned char)c;
    return h % tableSize;
}
// @end hashSum

// L40-B · Example: "ali", 10007  =>  (97*37*37 + 108*37 + 105) % 10007 = 6803
// @begin hash37
int hash37(const string& key, int tableSize) {
    unsigned int h = 0;
    for (char c : key) h = 37 * h + (unsigned char)c;   // Horner: ((k0*37 + k1)*37 + k2)
    return (int)(h % (unsigned int)tableSize);
}
// @end hash37

// L40-M1 · Example: size 10, insert 12, 22, -3  =>  bucket 2: 12 22, bucket 7: -3
// @begin ChainTable
ChainTable::ChainTable(int size)
    : table(size), count(0) {
}
// @end ChainTable

// @begin indexOf
int ChainTable::indexOf(int key) const {
    int n = table.size();
    return ((key % n) + n) % n;             // -3 % 10 is -3 in C++
}
// @end indexOf

// @begin insert
bool ChainTable::insert(int key) {
    if (contains(key)) return false;
    table[indexOf(key)].push_back(key);
    count++;
    return true;
}
// @end insert

// @begin contains
bool ChainTable::contains(int key) const {
    for (int x : table[indexOf(key)])       // only ONE chain is searched
        if (x == key) return true;
    return false;
}
// @end contains

// @begin remove
bool ChainTable::remove(int key) {
    list<int>& chain = table[indexOf(key)];
    for (auto it = chain.begin(); it != chain.end(); ++it)
        if (*it == key) {
            chain.erase(it);                // it is invalid now: return at once
            count--;
            return true;
        }
    return false;
}
// @end remove

// @begin size
int ChainTable::size() const {
    return count;
}
// @end size

// @begin bucket
vector<int> ChainTable::bucket(int b) const {
    return vector<int>(table[b].begin(), table[b].end());
}
// @end bucket

// @begin longestChain
int ChainTable::longestChain() const {
    int best = 0;
    for (const auto& chain : table)
        if ((int)chain.size() > best) best = chain.size();
    return best;
}
// @end longestChain

// L40-M2 · Example: "AAA"  =>  656565;  "a"  =>  -1
// @begin encodeString
int encodeString(const string& s) {
    if (s.empty() || s.size() > 4) return -1;
    int code = 0;
    for (char c : s) {
        if (c < 48 || c > 90) return -1;    // two decimal digits per character
        code = code * 100 + c;
    }
    return code;
}
// @end encodeString

// L40-M3 · Example: insertInt(656565), then insertString("AAA")  =>  true (a different entry)
// @begin MixedTable
MixedTable::MixedTable()
    : table(10) {
}
// @end MixedTable

// @begin has
bool MixedTable::has(int code, bool isString) const {
    for (const auto& e : table[((code % 10) + 10) % 10])
        if (e.first == code && e.second == isString) return true;   // the type must match too
    return false;
}
// @end has

// @begin add
bool MixedTable::add(int code, bool isString) {
    if (has(code, isString)) return false;
    table[((code % 10) + 10) % 10].push_back({code, isString});
    return true;
}
// @end add

// @begin insertInt
bool MixedTable::insertInt(int x) {
    return add(x, false);
}
// @end insertInt

// @begin insertString
bool MixedTable::insertString(const string& s) {
    int code = encodeString(s);
    return code != -1 && add(code, true);
}
// @end insertString

// @begin containsInt
bool MixedTable::containsInt(int x) const {
    return has(x, false);
}
// @end containsInt

// @begin containsString
bool MixedTable::containsString(const string& s) const {
    int code = encodeString(s);
    return code != -1 && has(code, true);
}
// @end containsString

// L40-X · Example: {2, 7, 11, 15}, 9  =>  (0, 1)
// @begin twoSum
pair<int, int> twoSum(const vector<int>& nums, int target) {
    unordered_map<int, int> where;          // value -> index, for the values seen so far
    for (int j = 0; j < (int)nums.size(); j++) {
        auto it = where.find(target - nums[j]);
        if (it != where.end()) return {it->second, j};
        where[nums[j]] = j;
    }
    return {-1, -1};
}
// @end twoSum
