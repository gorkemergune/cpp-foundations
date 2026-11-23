// Lab 15 tests. Every check also looks at tail (tailOk) and at leaked nodes.
#include <algorithm>

#include "intSLList.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_DEL_Case { V list; int el; V after; };
#include "pdf_cases.inc"

static void fill(IntSLList& l, const V& v) {
    for (int x : v) l.addToTail(x);
}

QUESTION("L15-A", "addToHead / addToTail", "IntSLList::addToTail(") {
    IntSLList l;
    l.addToTail(2);
    checkTrue("addToTail(2) on empty: tail", l.tailOk(), "tail is not the last node");
    l.addToTail(3);
    l.addToHead(1);
    check("addToTail 2, 3, addToHead 1", V{1, 2, 3}, l.toVector());
    checkTrue("tail after addToHead", l.tailOk(), "tail is not the last node");
    IntSLList h;
    h.addToHead(5);
    checkTrue("addToHead(5) on empty: tail", h.tailOk(), "tail must also point at the only node");
    h.addToTail(6);
    check("addToHead 5 then addToTail 6", V{5, 6}, h.toVector());
}

QUESTION("L15-B", "deleteFromHead / deleteFromTail", "IntSLList::deleteFromTail(") {
    IntSLList l;
    fill(l, {1, 2, 3});
    check("deleteFromTail on 1 2 3", 3, l.deleteFromTail());
    checkTrue("tail after deleteFromTail", l.tailOk(), "tail is not the last node");
    check("deleteFromHead on 1 2", 1, l.deleteFromHead());
    check("deleteFromTail on 2 (single node)", 2, l.deleteFromTail());
    checkTrue("empty again", l.isEmpty() && l.tailOk(), "head and tail must both be 0");
    l.addToTail(9);
    check("addToTail after emptying", V{9}, l.toVector());
    check("deleteFromHead on the single node 9", 9, l.deleteFromHead());
    checkTrue("empty again (head)", l.isEmpty() && l.tailOk(), "head and tail must both be 0");
}

QUESTION("L15-M1", "deleteNode / isInList", "IntSLList::deleteNode(") {
    for (auto& c : PDF_DEL) {
        IntSLList l;
        fill(l, c.list);
        int before = IntSLLNode::alive;
        std::string d = "list=" + show(c.list) + ", deleteNode(" + std::to_string(c.el) + ")";
        l.deleteNode(c.el);
        check(d, c.after, l.toVector());
        checkTrue(d + " (tail)", l.tailOk(), "tail is not the last node");
        check(d + " (deleted nodes)", (int)(c.list.size() - c.after.size()), before - IntSLLNode::alive);
        l.addToTail(100);
        checkTrue(d + " then addToTail(100)", l.toVector().back() == 100, "100 is not at the end");
    }
    IntSLList l;
    fill(l, {1, 3});
    check("isInList(3)", true, l.isInList(3));
    check("isInList(2)", false, l.isInList(2));
    IntSLList e;
    check("isInList on empty", false, e.isInList(1));
}

QUESTION("L15-M2", "destructor frees every node", "IntSLList::~IntSLList(") {
    int before = IntSLLNode::alive;
    {
        IntSLList l;
        fill(l, {1, 2, 3, 4});
        check("4 nodes exist inside the block", before + 4, IntSLLNode::alive);
    }
    check("after the list went out of scope", before, IntSLLNode::alive);
}

OPTIONAL_QUESTION("L15-X", "removeAll (LC 203 on IntSLList)", "IntSLList::removeAll(") {
    for (int t = 0; t < RANDOM_CASES; t++) {
        V v = randVec(10, 0, 3);
        int el = randInt(0, 3);
        V want = v;
        want.erase(std::remove(want.begin(), want.end(), el), want.end());
        IntSLList l;
        fill(l, v);
        std::string d = "list=" + show(v) + ", removeAll(" + std::to_string(el) + ")";
        check(d + " (return)", (int)(v.size() - want.size()), l.removeAll(el));
        check(d, want, l.toVector());
        checkTrue(d + " (tail)", l.tailOk(), "tail is not the last node");
    }
}

OPTIONAL_QUESTION("L15-V", "insertSorted", "IntSLList::insertSorted(") {
    for (int t = 0; t < RANDOM_CASES; t++) {
        V v = randVec(10, 0, 9);
        IntSLList l;
        for (int x : v) l.insertSorted(x);
        V want = v;
        std::sort(want.begin(), want.end());
        check("insertSorted " + show(v), want, l.toVector());
        checkTrue("insertSorted " + show(v) + " (tail)", l.tailOk(), "tail is not the last node");
    }
}
