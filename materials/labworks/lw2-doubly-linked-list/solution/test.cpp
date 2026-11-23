// Labwork 2 tests. Lists are printed with operator<<; deleteFromDLLTail() walks the
// prev links, so emptying a list from the back proves the prev pointers are right.
#include <initializer_list>
#include <sstream>

#include "check.h"
#include "genDLList.h"

template <class T>
std::string str(const DoublyLinkedList<T>& l) {
    std::ostringstream o;
    o << l;
    return o.str();
}
static void fill(DoublyLinkedList<int>& l, std::initializer_list<int> v) {
    for (int x : v) l.addToDLLTail(x);
}
static std::string backwards(DoublyLinkedList<int>& l) {  // empties the list
    std::string s;
    while (!l.isEmpty()) s += std::to_string(l.deleteFromDLLTail()) + " ";
    return s;
}

int main() {
    {  // PDF example
        DoublyLinkedList<int> A, B;
        fill(A, {5, 8, 2, 4});
        fill(B, {6, 7, 11, 0});
        A.append(B);
        CHECK_EQ(str(A), std::string("5 8 2 4 6 7 11 0 "));
        CHECK_EQ(str(B), std::string("6 7 11 0 "));
        B.addToDLLTail(99);  // independent lists
        CHECK_EQ(str(A), std::string("5 8 2 4 6 7 11 0 "));
        A.addToDLLTail(15);
        DoublyLinkedList<int>* C = A.split();
        CHECK_EQ(str(A), std::string("5 8 2 4 6 "));
        CHECK_EQ(str(*C), std::string("7 11 0 15 "));
        CHECK_EQ(backwards(*C), std::string("15 0 11 7 "));
        CHECK_EQ(backwards(A), std::string("6 4 2 8 5 "));
        delete C;
    }
    {  // append to an empty list, append an empty list, append to itself
        DoublyLinkedList<int> A, B, E;
        fill(B, {1, 2});
        A.append(B);
        CHECK_EQ(str(A), std::string("1 2 "));
        A.append(E);
        CHECK_EQ(str(A), std::string("1 2 "));
        A.append(A);
        CHECK_EQ(str(A), std::string("1 2 1 2 "));
        CHECK_EQ(backwards(A), std::string("2 1 2 1 "));
    }
    {  // split: even, 1 element, empty
        DoublyLinkedList<int> A;
        fill(A, {1, 2, 3, 4});
        DoublyLinkedList<int>* C = A.split();
        CHECK_EQ(str(A), std::string("1 2 "));
        CHECK_EQ(str(*C), std::string("3 4 "));
        delete C;
        DoublyLinkedList<int> one;
        fill(one, {9});
        C = one.split();
        CHECK_EQ(str(one), std::string("9 "));
        CHECK(C->isEmpty());
        delete C;
        DoublyLinkedList<int> empty;
        C = empty.split();
        CHECK(C->isEmpty() && empty.isEmpty());
        delete C;
    }
    return check_summary("lw2 append / split");
}
