// Labwork 1 tests: contents are read through printAll(); addToTail() after each
// operation proves that tail still points to the real last node.
#include <initializer_list>

#include "check.h"
#include "intSLList.h"

static void fill(IntSLList& l, std::initializer_list<int> v) {
    for (int x : v) l.addToTail(x);
}
static std::string dump(IntSLList& l) { return captured([&] { l.printAll(); }); }

int main() {
    {  // example from the PDF figure + the example main
        IntSLList l;
        fill(l, {2, 6, 5, 8, 5, 4});
        l.remove_even();
        CHECK_EQ(dump(l), std::string("5 5 \n"));
        l.duplicate_fives();
        CHECK_EQ(dump(l), std::string("5 5 5 5 \n"));
        l.addToTail(8);
        CHECK_EQ(dump(l), std::string("5 5 5 5 8 \n"));
    }
    {  // head and tail are even, negatives and zero
        IntSLList l;
        fill(l, {4, 7, -2, 0, 9, 10});
        l.remove_even();
        CHECK_EQ(dump(l), std::string("7 9 \n"));
        l.addToTail(1);
        CHECK_EQ(dump(l), std::string("7 9 1 \n"));
    }
    {  // all even -> empty list, then it must still work
        IntSLList l;
        fill(l, {2, 4, 6});
        l.remove_even();
        CHECK_EQ(dump(l), std::string("\n"));
        CHECK(l.isEmpty());
        l.addToTail(3);
        CHECK_EQ(dump(l), std::string("3 \n"));
    }
    {  // empty list
        IntSLList l;
        l.remove_even();
        l.duplicate_fives();
        CHECK(l.isEmpty());
    }
    {  // 5 in the middle must NOT move tail (bug in the archive solution)
        IntSLList l;
        fill(l, {5, 7});
        l.duplicate_fives();
        l.addToTail(8);
        CHECK_EQ(dump(l), std::string("5 5 7 8 \n"));
    }
    {  // consecutive fives and five at the tail
        IntSLList l;
        fill(l, {5, 5, 1, 5});
        l.duplicate_fives();
        CHECK_EQ(dump(l), std::string("5 5 5 5 1 5 5 \n"));
        CHECK_EQ(l.deleteFromTail(), 5);
        CHECK_EQ(l.deleteFromTail(), 5);
        CHECK_EQ(l.deleteFromTail(), 1);
    }
    return check_summary("lw1 remove_even / duplicate_fives");
}
