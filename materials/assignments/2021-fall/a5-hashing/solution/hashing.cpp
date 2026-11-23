// Assignment 5 (2021) · reference solution: chained hash table with 10 buckets.
// hashTable[b] holds the values, hashType[b] holds 0 (int) or 1 (string) at the same position.
#include "hashing.h"

#include <iostream>
#include <string>

#include "intSLList.h"

using namespace std;

IntSLList hashTable[10];
IntSLList hashType[10];

// Works for negative numbers too: -7 % 10 is -7 in C++, which is not a valid index.
static int bucketOf(int x) { return ((x % 10) + 10) % 10; }

// Each character (ASCII 48..90, two digits) becomes two decimal digits:
// "AAA" -> 65 65 65 -> 656565. Up to 4 characters fit in an int (max 90909090).
// Returns -1 for a string that cannot be encoded.
int encodeString(const char* input) {
    string s = input;
    if (s.empty() || s.size() > 4) return -1;
    int code = 0;
    for (char c : s) {
        if (c < 48 || c > 90) return -1;     // lower-case letters would need 3 digits
        code = code * 100 + c;               // shift two decimal places, append the char
    }
    return code;
}

// Number of nodes, using only the public list API: move everything to a temporary
// list and back (the order does not change).
static int countNodes(IntSLList& l) {
    IntSLList tmp;
    int n = 0;
    while (!l.isEmpty()) {
        tmp.addToTail(l.deleteFromHead());
        n++;
    }
    while (!tmp.isEmpty()) l.addToTail(tmp.deleteFromHead());
    return n;
}

// The two lists of a bucket are walked together: every node is taken from the head
// and put back at the tail. After `count` steps both lists are in their original order.
// The type must match too: the int 656565 and the string "AAA" have the same code.
static bool contains(int bucket, int value, int type) {
    IntSLList& vals = hashTable[bucket];
    IntSLList& types = hashType[bucket];
    int count = countNodes(vals);
    bool found = false;
    for (int i = 0; i < count; i++) {
        int v = vals.deleteFromHead();
        int t = types.deleteFromHead();
        if (v == value && t == type) found = true;
        vals.addToTail(v);
        types.addToTail(t);
    }
    return found;
}

void insertIntoHashTable(int input) {
    if (searchInHashTable(input)) return;            // no duplicates
    hashTable[bucketOf(input)].addToTail(input);
    hashType[bucketOf(input)].addToTail(0);
}

void insertIntoHashTable(const char* input) {
    int code = encodeString(input);
    if (code < 0 || searchInHashTable(input)) return;
    hashTable[bucketOf(code)].addToTail(code);
    hashType[bucketOf(code)].addToTail(1);
}

bool searchInHashTable(int input) { return contains(bucketOf(input), input, 0); }

bool searchInHashTable(const char* input) {
    int code = encodeString(input);
    return code >= 0 && contains(bucketOf(code), code, 1);
}

void printHashTable() {
    for (int i = 0; i < 10; i++) {
        cout << "bucket " << i << " values: ";
        hashTable[i].printAll();
        cout << "         types:  ";
        hashType[i].printAll();
    }
}

void clearHashTable() {
    for (int i = 0; i < 10; i++) {
        while (!hashTable[i].isEmpty()) hashTable[i].deleteFromHead();
        while (!hashType[i].isEmpty()) hashType[i].deleteFromHead();
    }
}
