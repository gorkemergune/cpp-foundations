// Lab 40 tests.
#include <algorithm>
#include <set>

#include "lab40.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_HASH_Case { std::string key; int size; int sum; int h37; };
struct PDF_ENC_Case { std::string s; int code; };
#include "pdf_cases.inc"

QUESTION("L40-A", "hashSum (slide 29)", "hashSum(") {
    for (auto& c : PDF_HASH) check("hashSum(" + show(c.key) + ", " + std::to_string(c.size) + ")", c.sum, hashSum(c.key, c.size));
}

QUESTION("L40-B", "hash37 (slide 30)", "hash37(") {
    for (auto& c : PDF_HASH) check("hash37(" + show(c.key) + ", " + std::to_string(c.size) + ")", c.h37, hash37(c.key, c.size));
    for (int t = 0; t < RANDOM_CASES; t++) {
        std::string s;
        for (int k = randInt(0, 12); k > 0; k--) s += (char)randInt('a', 'z');
        int size = randInt(1, 20000);
        unsigned int h = 0;
        for (char c : s) h = 37 * h + (unsigned char)c;
        check("hash37(" + show(s) + ", " + std::to_string(size) + ")", (int)(h % size), hash37(s, size));
    }
}

QUESTION("L40-M1", "ChainTable (separate chaining)", "ChainTable::") {
    ChainTable t(10);
    for (int x : {12, 22, -3, 7, 2}) check("insert " + std::to_string(x), true, t.insert(x));
    check("insert 22 again", false, t.insert(22));
    check("bucket 2 (insertion order)", V{12, 22, 2}, t.bucket(2));
    check("bucket 7: -3 goes to 7", V{-3, 7}, t.bucket(7));
    check("bucket 0", V{}, t.bucket(0));
    check("size", 5, t.size());
    check("contains -3", true, t.contains(-3));
    check("contains 32", false, t.contains(32));
    check("remove 22", true, t.remove(22));
    check("remove 22 again", false, t.remove(22));
    check("bucket 2 after removing 22", V{12, 2}, t.bucket(2));
    check("size", 4, t.size());
    for (int r = 0; r < RANDOM_CASES; r++) {
        int n = randInt(1, 13);
        ChainTable h(n);
        std::set<int> ref;
        bool ok = true;
        for (int s = 0; s < 40 && ok; s++) {
            int x = randInt(-30, 30), op = randInt(0, 2);
            if (op == 0) ok = h.insert(x) == ref.insert(x).second;
            if (op == 1) ok = h.remove(x) == (ref.erase(x) == 1);
            if (op == 2) ok = h.contains(x) == (ref.count(x) == 1);
        }
        int total = 0;
        for (int b = 0; b < n && ok; b++)
            for (int x : h.bucket(b)) { total++; ok = ok && ((x % n) + n) % n == b && ref.count(x); }
        checkTrue("random operations, " + std::to_string(n) + " buckets", ok && total == (int)ref.size() && h.size() == total,
                  "wrong answer, wrong bucket or wrong size");
    }
}

QUESTION("L40-M2", "encodeString (Assignment 5)", "encodeString(") {
    for (auto& c : PDF_ENC) check("encodeString(" + show(c.s) + ")", c.code, encodeString(c.s));
}

QUESTION("L40-M3", "MixedTable (Assignment 5)", "MixedTable::") {
    MixedTable m;
    check("insertInt(656565)", true, m.insertInt(656565));
    check("containsString(\"AAA\") before inserting it", false, m.containsString("AAA"));
    check("insertString(\"AAA\"): same code, other type", true, m.insertString("AAA"));
    check("insertString(\"AAA\") again", false, m.insertString("AAA"));
    check("insertInt(656565) again", false, m.insertInt(656565));
    check("insertString(\"abc\"): cannot be encoded", false, m.insertString("abc"));
    check("insertInt(-7)", true, m.insertInt(-7));
    check("containsInt(-7)", true, m.containsInt(-7));
    check("containsInt(3)", false, m.containsInt(3));
    check("containsString(\"A1\")", false, m.containsString("A1"));
    check("insertString(\"A1\")", true, m.insertString("A1"));
    check("containsString(\"A1\")", true, m.containsString("A1"));
    check("containsInt(6549): the code of \"A1\" as an int", false, m.containsInt(6549));
}

OPTIONAL_QUESTION("L40-X", "twoSum (LC 1)", "twoSum(") {
    check("{2,7,11,15}, 9", std::make_pair(0, 1), twoSum({2, 7, 11, 15}, 9));
    check("{3,2,4}, 6", std::make_pair(1, 2), twoSum({3, 2, 4}, 6));
    check("{3,3}, 6", std::make_pair(0, 1), twoSum({3, 3}, 6));
}

OPTIONAL_QUESTION("L40-V", "longestChain", "longestChain(") {
    ChainTable t(5);
    check("empty", 0, t.longestChain());
    for (int x : {0, 5, 10, 1, 6}) t.insert(x);
    check("0 5 10 | 1 6", 3, t.longestChain());
}
