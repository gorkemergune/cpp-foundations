// Lab 19 tests. The circle is checked independently of your toVector:
// from last->next, exactly n steps must come back to last->next, and last must be the n-th.
#include <algorithm>

#include "lab19.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_DL_Case { V circle; bool ret; V after; };
struct PDF_DF_Case { V circle; bool ret; V after; };
#include "pdf_cases.inc"

static Node* build(const V& v) {                 // returns last
    if (v.empty()) return nullptr;
    Node* first = new Node(v[0]);
    Node* last = first;
    for (size_t i = 1; i < v.size(); i++) last = last->next = new Node(v[i]);
    last->next = first;
    return last;
}
static V circle(Node* last) {                    // test's own reader, with a guard
    V r;
    if (!last) return r;
    Node* p = last->next;
    for (int g = 0; g < 1000; g++) {
        r.push_back(p->data);
        if (p == last) break;
        p = p->next;
    }
    return r;
}
static bool closed(Node* last, size_t n) {
    if (!last) return n == 0;
    Node* p = last->next;
    for (size_t i = 1; i < n; i++) p = p->next;
    return p == last && last->next != nullptr;
}
static void destroy(Node* last) {
    if (!last) return;
    Node* p = last->next;
    last->next = nullptr;
    while (p) {
        Node* n = p->next;
        delete p;
        p = n;
    }
}

QUESTION("L19-A", "insertAtEnd", "insertAtEnd(") {
    Node* last = nullptr;
    insertAtEnd(last, 1);
    checkTrue("one node points to itself", last && last->next == last, "last->next must be last");
    insertAtEnd(last, 2);
    insertAtEnd(last, 3);
    check("insert 1, 2, 3", V{1, 2, 3}, circle(last));
    checkTrue("closed circle, last = 3", closed(last, 3) && last->data == 3, "the circle is broken");
    destroy(last);
}

QUESTION("L19-B", "toVector (one full round)", "toVector(") {
    for (V v : {V{1, 2, 3}, V{}, V{7}, V{4, 4}}) {
        Node* last = build(v);
        check("circle " + show(v), v, toVector(last));
        destroy(last);
    }
}

QUESTION("L19-M1", "deleteLast (midterm)", "deleteLast(") {
    for (auto& c : PDF_DL) {
        Node* last = build(c.circle);
        int alive = Node::alive;
        std::string d = "circle=" + show(c.circle);
        check(d + " (return)", c.ret, deleteLast(last));
        check(d + " (after)", c.after, circle(last));
        checkTrue(d + " (closed, last is the last value)", closed(last, c.after.size()) &&
                  (c.after.empty() || last->data == c.after.back()), "last or the circle is wrong");
        check(d + " (deleted)", c.ret ? 1 : 0, alive - Node::alive);
        destroy(last);
    }
}

QUESTION("L19-M2", "deleteFirst", "deleteFirst(") {
    for (auto& c : PDF_DF) {
        Node* last = build(c.circle);
        Node* oldLast = last;
        std::string d = "circle=" + show(c.circle);
        check(d + " (return)", c.ret, deleteFirst(last));
        check(d + " (after)", c.after, circle(last));
        checkTrue(d + " (closed)", closed(last, c.after.size()), "the circle is broken");
        if (c.after.size() >= 1) checkTrue(d + " (last unchanged)", last == oldLast, "last must stay the same node");
        destroy(last);
    }
}

OPTIONAL_QUESTION("L19-X", "deleteValue", "deleteValue(") {
    for (int t = 0; t < RANDOM_CASES; t++) {
        V v = randVec(6, 0, 3), w = v;
        int x = randInt(0, 4);
        auto it = std::find(w.begin(), w.end(), x);
        bool found = it != w.end();
        if (found) w.erase(it);
        Node* last = build(v);
        std::string d = "circle=" + show(v) + ", v=" + std::to_string(x);
        check(d + " (return)", found, deleteValue(last, x));
        check(d, w, circle(last));
        checkTrue(d + " (closed)", closed(last, w.size()) && (w.empty() || last->data == w.back()), "wrong last");
        destroy(last);
    }
}

OPTIONAL_QUESTION("L19-V", "countNodes", "countNodes(") {
    for (V v : {V{1, 2, 3}, V{}, V{9}}) {
        Node* last = build(v);
        check("circle " + show(v), (int)v.size(), countNodes(last));
        destroy(last);
    }
}
