// ============================================================================
//  Lab 40 · Hash functions and separate chaining                    DO NOT EDIT
//  Slides 29-31 (string hash functions), 26-27 (separate chaining),
//  2021 Assignment 5 (ints and short strings in one chained table).
// ============================================================================
#pragma once

#include <list>
#include <string>
#include <utility>
#include <vector>

// L40-A · Warm-up · slide 29 "Hash Function 1": the sum of the character codes % tableSize.
int hashSum(const std::string& key, int tableSize);

// L40-B · Warm-up · slide 30 "Hash Function 2": h = 37 * h + key[i] for every character,
// then % tableSize. Compute h as `unsigned int` (wrap-around is defined for unsigned).
// hash37("ali", 10007) == 6803 (slide 31 says 8172: it uses 98 for 'a', which is 97).
int hash37(const std::string& key, int tableSize);

// L40-M1 · Main · a chained hash table of ints (slides 26-27). bucket(x) = x mod size,
// made non-negative ((x % size) + size) % size. New keys go to the END of their chain;
// a key is stored at most once.
class ChainTable {
public:
    explicit ChainTable(int size);
    bool insert(int key);                   // false if already there
    bool contains(int key) const;
    bool remove(int key);                   // false if not there
    int size() const;                       // number of keys
    std::vector<int> bucket(int b) const;   // the chain of bucket b, front to back
    int longestChain() const;               // L40-V · optional
private:
    std::vector<std::list<int>> table;
    int count;
    int indexOf(int key) const;
};

// L40-M2 · Main (2021 Assignment 5) · a string of 1..4 characters with codes 48..90
// ('0'-'9', ':'-'@', 'A'-'Z') becomes two decimal digits per character: "AAA" -> 656565.
// Anything else -> -1.
int encodeString(const std::string& s);

// L40-M3 · Main (2021 Assignment 5) · ints and short strings in ONE chained table of 10
// buckets. Every entry remembers its type, so the int 656565 and the string "AAA" (code
// 656565) are different entries. Strings that cannot be encoded are rejected.
class MixedTable {
public:
    MixedTable();
    bool insertInt(int x);                  // false if this int is already there
    bool insertString(const std::string& s);   // false if already there or not encodable
    bool containsInt(int x) const;
    bool containsString(const std::string& s) const;
private:
    std::vector<std::list<std::pair<int, bool>>> table;   // (code, isString)
    bool add(int code, bool isString);
    bool has(int code, bool isString) const;
};

// L40-X · Optional · LeetCode 1: indices i < j with nums[i] + nums[j] == target
// (exactly one answer). One pass with std::unordered_map.
std::pair<int, int> twoSum(const std::vector<int>& nums, int target);
