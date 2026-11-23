// Lab 13 tests. Node::alive counts live nodes, so leaks and double deletes are visible.
#include "lab13.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_MAKE_Case { V values; };
struct PDF_BIN_Case { V bits; int ret; };
#include "pdf_cases.inc"

static void destroy(Node* h) {
    while (h) {
        Node* n = h->next;
        delete h;
        h = n;
    }
}

QUESTION("L13-A", "makeList", "makeList(") {
    for (auto& c : PDF_MAKE) {
        int before = Node::alive;
        Node* h = makeList(c.values);
        V got;
        int guard = 0;
        for (Node* p = h; p && guard < 1000; p = p->next, guard++) got.push_back(p->value);
        check("makeList(" + show(c.values) + ")", c.values, got);
        check("makeList(" + show(c.values) + ") -> nodes created", (int)c.values.size(), Node::alive - before);
        destroy(h);
    }
}

QUESTION("L13-B", "toVector", "toVector(") {
    for (auto& c : PDF_MAKE) {
        Node* h = nullptr;
        for (int i = (int)c.values.size() - 1; i >= 0; i--) h = new Node(c.values[i], h);
        check("toVector of " + show(c.values), c.values, toVector(h));
        destroy(h);
    }
}

QUESTION("L13-M1", "freeList", "freeList(") {
    for (auto& c : PDF_MAKE) {
        Node* h = nullptr;
        for (int i = (int)c.values.size() - 1; i >= 0; i--) h = new Node(c.values[i], h);
        int before = Node::alive;
        freeList(h);
        check("freeList on " + show(c.values) + " -> nodes deleted", (int)c.values.size(), before - Node::alive);
        checkTrue("freeList on " + show(c.values) + " -> head", h == nullptr, "the caller's head must be nullptr");
    }
}

QUESTION("L13-M2", "countNodes", "countNodes(") {
    for (auto& c : PDF_MAKE) {
        Node* h = nullptr;
        for (int i = (int)c.values.size() - 1; i >= 0; i--) h = new Node(c.values[i], h);
        check("countNodes of " + show(c.values), (int)c.values.size(), countNodes(h));
        destroy(h);
    }
    for (int i = 0; i < RANDOM_CASES; i++) {
        V v = randVec(30, 0, 9);
        Node* h = nullptr;
        for (int k = (int)v.size() - 1; k >= 0; k--) h = new Node(v[k], h);
        check("random list of length " + std::to_string(v.size()), (int)v.size(), countNodes(h));
        destroy(h);
    }
}

OPTIONAL_QUESTION("L13-X", "getDecimalValue (LC 1290)", "getDecimalValue(") {
    for (auto& c : PDF_BIN) {
        Node* h = nullptr;
        for (int i = (int)c.bits.size() - 1; i >= 0; i--) h = new Node(c.bits[i], h);
        check("bits " + show(c.bits), c.ret, getDecimalValue(h));
        destroy(h);
    }
}

OPTIONAL_QUESTION("L13-V", "copyList (deep copy)", "copyList(") {
    for (auto& c : PDF_MAKE) {
        Node* h = nullptr;
        for (int i = (int)c.values.size() - 1; i >= 0; i--) h = new Node(c.values[i], h);
        int before = Node::alive;
        Node* cp = copyList(h);
        check("copy of " + show(c.values), c.values, toVector(cp));
        check("copy of " + show(c.values) + " -> new nodes", (int)c.values.size(), Node::alive - before);
        if (h && cp) {
            cp->value = -1;
            check("changing the copy leaves the original", c.values[0], h->value);
        }
        destroy(h);
        destroy(cp);
    }
}
