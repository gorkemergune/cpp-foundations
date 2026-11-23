#include <initializer_list>

#include "check.h"
#include "intSLList.h"

static void fill(IntSLList& l, std::initializer_list<int> v) {
    for (int x : v) l.addToTail(x);
}
static std::string dump(const IntSLList& l) { return captured([&] { l.printAll(); }); }

int main() {
    IntSLList list, list2;
    for (int i = 0; i < 6; i++) list.addToHead(i);
    CHECK_EQ(dump(list), std::string("5 4 3 2 1 0 \n"));
    CHECK_EQ(list.find_min(), 0);
    list2 = list.sort_list();                       // copy assignment from a temporary
    CHECK_EQ(dump(list2), std::string("0 1 2 3 4 5 \n"));
    CHECK_EQ(dump(list), std::string("5 4 3 2 1 0 \n"));   // original unchanged
    list2.swap_nodes(4);
    CHECK_EQ(dump(list2), std::string("4 1 2 3 0 5 \n"));

    IntSLList a;
    fill(a, {0, 1, 2, 3, 4});
    a.swap_nodes(2);                                // PDF example
    CHECK_EQ(dump(a), std::string("2 1 0 3 4 \n"));
    a.swap_nodes(1);                                // second node
    CHECK_EQ(dump(a), std::string("1 2 0 3 4 \n"));
    a.swap_nodes(4);                                // tail: the old head becomes tail
    CHECK_EQ(dump(a), std::string("4 2 0 3 1 \n"));
    a.addToTail(9);
    CHECK_EQ(dump(a), std::string("4 2 0 3 1 9 \n"));
    a.swap_nodes(4);                                // already the head
    a.swap_nodes(77);                               // not in the list
    CHECK_EQ(dump(a), std::string("4 2 0 3 1 9 \n"));

    IntSLList two;
    fill(two, {8, 3});
    two.swap_nodes(3);
    CHECK_EQ(dump(two), std::string("3 8 \n"));
    CHECK_EQ(two.deleteFromTail(), 8);              // tail moved correctly
    IntSLList dups;
    fill(dups, {3, 1, 3, 1, 2});
    CHECK_EQ(dump(dups.sort_list()), std::string("1 1 2 3 3 \n"));
    IntSLList empty;
    CHECK(empty.sort_list().isEmpty());
    IntSLList copy(dups);
    copy.addToTail(100);
    CHECK_EQ(dump(dups), std::string("3 1 3 1 2 \n"));   // deep copy
    dups = dups;                                    // self-assignment
    CHECK_EQ(dump(dups), std::string("3 1 3 1 2 \n"));
    return check_summary("2021 a1 find_min / sort_list / swap_nodes");
}
