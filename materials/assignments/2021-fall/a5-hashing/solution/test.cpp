#include "check.h"
#include "hashing.h"

int main() {
    CHECK_EQ(encodeString("AAA"), 656565);
    CHECK_EQ(encodeString("Y"), 89);
    CHECK_EQ(encodeString("30E"), 514869);
    CHECK_EQ(encodeString("ZZZZ"), 90909090);
    CHECK_EQ(encodeString("ABCDE"), -1);       // too long
    CHECK_EQ(encodeString("ab"), -1);          // lower case does not fit in 2 digits
    for (int x : {1, 11, 6, 121}) insertIntoHashTable(x);
    for (const char* s : {"AAA", "Y", "30E"}) insertIntoHashTable(s);
    CHECK(searchInHashTable(11));              // example main of the assignment: 1 0 0 1 0
    CHECK(!searchInHashTable(10));
    CHECK(!searchInHashTable(66));
    CHECK(searchInHashTable("AAA"));
    CHECK(!searchInHashTable("AA"));
    CHECK(!searchInHashTable(656565));         // same code as "AAA" but a different type
    insertIntoHashTable(656565);
    CHECK(searchInHashTable(656565));
    CHECK(searchInHashTable("AAA"));
    insertIntoHashTable(-7);                   // negative keys go to bucket 3
    CHECK(searchInHashTable(-7));
    CHECK(!searchInHashTable(7));
    std::string before = captured([] { printHashTable(); });
    insertIntoHashTable(11);                   // duplicate: no change
    insertIntoHashTable("Y");
    CHECK_EQ(captured([] { printHashTable(); }), before);
    CHECK(before.find("bucket 1 values: 1 11 121 \n") != std::string::npos);
    clearHashTable();
    CHECK(!searchInHashTable(11));
    return check_summary("2021 a5 hashing");
}
