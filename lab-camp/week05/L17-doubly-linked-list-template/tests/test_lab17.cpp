// Lab 17 tests. Every list is read forwards AND backwards (prev links), ends are checked.
#include <algorithm>
#include <string>

#include "genDLList.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_RM_Case { V list; int el; bool ret; V after; };
#include "pdf_cases.inc"

template <class T>
static void both(const std::string& d, const std::vector<T>& want, const DoublyLinkedList<T>& l) {
    check(d + " (forward)", want, l.forward());
    std::vector<T> r(want.rbegin(), want.rend());
    check(d + " (backward through prev)", r, l.backward());
    checkTrue(d + " (ends)", l.endsOk(), "head->prev must be 0, tail->next must be 0");
}

QUESTION("L17-A", "addToDLLHead / addToDLLTail", "addToDLLTail(") {
    DoublyLinkedList<int> l;
    l.addToDLLTail(2);
    l.addToDLLTail(3);
    l.addToDLLHead(1);
    both("tail 2, tail 3, head 1", V{1, 2, 3}, l);
    DoublyLinkedList<int> h;
    h.addToDLLHead(5);
    h.addToDLLHead(4);
    both("head 5, head 4", V{4, 5}, h);
    DoublyLinkedList<std::string> s;
    s.addToDLLTail("b");
    s.addToDLLHead("a");
    both("T = std::string", std::vector<std::string>{"a", "b"}, s);
}

QUESTION("L17-B", "deleteFromDLLHead / deleteFromDLLTail / clear", "deleteFromDLLTail(") {
    DoublyLinkedList<int> l;
    for (int x : {1, 2, 3, 4}) l.addToDLLTail(x);
    check("deleteFromDLLTail on 1 2 3 4", 4, l.deleteFromDLLTail());
    check("deleteFromDLLHead on 1 2 3", 1, l.deleteFromDLLHead());
    both("after both deletions", V{2, 3}, l);
    check("deleteFromDLLTail", 3, l.deleteFromDLLTail());
    check("deleteFromDLLHead (last node)", 2, l.deleteFromDLLHead());
    checkTrue("empty again", l.isEmpty() && l.endsOk(), "head and tail must both be 0");
    l.addToDLLTail(7);
    both("reuse after emptying", V{7}, l);
    int before = DLLNode<int>::alive;
    for (int x : {8, 9}) l.addToDLLTail(x);
    l.clear();
    checkTrue("clear()", l.isEmpty() && l.endsOk() && DLLNode<int>::alive == before - 1, "every node must be deleted");
    int start = DLLNode<int>::alive;
    {
        DoublyLinkedList<int> tmp;
        for (int x : {1, 2, 3}) tmp.addToDLLTail(x);
    }
    check("destructor (calls clear) leaves no node", start, DLLNode<int>::alive);
}

QUESTION("L17-M1", "removeValue", "removeValue(") {
    for (auto& c : PDF_RM) {
        DoublyLinkedList<int> l;
        for (int x : c.list) l.addToDLLTail(x);
        int alive = DLLNode<int>::alive;
        std::string d = "list=" + show(c.list) + ", removeValue(" + std::to_string(c.el) + ")";
        check(d + " (return)", c.ret, l.removeValue(c.el));
        both(d, c.after, l);
        check(d + " (deleted)", c.ret ? 1 : 0, alive - DLLNode<int>::alive);
    }
}

QUESTION("L17-M2", "reverse (in place)", "DoublyLinkedList<T>::reverse(") {
    for (int t = 0; t < RANDOM_CASES; t++) {
        V v = randVec(10, 0, 9), w = v;
        std::reverse(w.begin(), w.end());
        DoublyLinkedList<int> l;
        for (int x : v) l.addToDLLTail(x);
        int alive = DLLNode<int>::alive;
        l.reverse();
        both("reverse " + show(v), w, l);
        check("reverse " + show(v) + " (no new nodes)", alive, DLLNode<int>::alive);
        l.addToDLLTail(99);
        checkTrue("reverse " + show(v) + " then addToDLLTail(99)", l.forward().back() == 99 && l.endsOk(), "tail is wrong");
    }
}

OPTIONAL_QUESTION("L17-X", "append (Labwork 2 Q1)", "append(") {
    DoublyLinkedList<int> a, b;
    for (int x : {5, 8}) a.addToDLLTail(x);
    for (int x : {6, 7}) b.addToDLLTail(x);
    a.append(b);
    both("A.append(B)", V{5, 8, 6, 7}, a);
    both("B unchanged", V{6, 7}, b);
    a.append(a);
    both("A.append(A)", V{5, 8, 6, 7, 5, 8, 6, 7}, a);
    DoublyLinkedList<int> e;
    e.append(b);
    both("empty.append(B)", V{6, 7}, e);
}

OPTIONAL_QUESTION("L17-V", "find", "DoublyLinkedList<T>::find(") {
    DoublyLinkedList<int> l;
    for (int x : {1, 3, 3}) l.addToDLLTail(x);
    int* p = l.find(3);
    checkTrue("find(3) returns a pointer", p != nullptr && *p == 3, "expected a pointer to 3");
    if (p) *p = 30;
    both("changing *find(3) changes the first 3", V{1, 30, 3}, l);
    checkTrue("find(9)", l.find(9) == nullptr, "expected 0");
}
