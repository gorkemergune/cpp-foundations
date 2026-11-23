// Lab 14 tests. Node::alive catches leaks; node addresses catch "rebuilt" lists.
#include "lab14.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_INS_Case { V list; int index; int value; bool ret; V after; };
struct PDF_REM_Case { V list; int index; bool ret; V after; };
#include "pdf_cases.inc"

static Node* build(const V& v) {
    Node* h = nullptr;
    for (int i = (int)v.size() - 1; i >= 0; i--) h = new Node(v[i], h);
    return h;
}
static V values(Node* h) {
    V r;
    for (int g = 0; h && g < 1000; h = h->next, g++) r.push_back(h->data);
    return r;
}
static void destroy(Node* h) {
    while (h) {
        Node* n = h->next;
        delete h;
        h = n;
    }
}

QUESTION("L14-A", "pushFront", "pushFront(") {
    Node* h = nullptr;
    pushFront(h, 3);
    pushFront(h, 2);
    pushFront(h, 1);
    check("pushFront 3, 2, 1 on an empty list", V{1, 2, 3}, values(h));
    destroy(h);
}

QUESTION("L14-B", "pushBack (Practice Lab 2)", "pushBack(") {
    Node* h = nullptr;
    pushBack(h, 1);
    checkTrue("pushBack on an empty list changes the caller's head", h != nullptr, "head is still nullptr");
    pushBack(h, 2);
    pushBack(h, 3);
    check("pushBack 1, 2, 3", V{1, 2, 3}, values(h));
    destroy(h);
    check("no leaked nodes", 0, Node::alive);
}

QUESTION("L14-M1", "insertAt", "insertAt(") {
    for (auto& c : PDF_INS) {
        Node* h = build(c.list);
        Node* oldFirst = h;
        std::string d = "list=" + show(c.list) + ", index=" + std::to_string(c.index) + ", value=" + std::to_string(c.value);
        bool got = insertAt(h, c.index, c.value);
        check(d + " (return)", c.ret, got);
        check(d + " (list after)", c.after, values(h));
        if (c.index != 0 && !c.list.empty()) checkTrue(d + " (old nodes kept)", h == oldFirst, "the list was rebuilt instead of relinked");
        destroy(h);
    }
    check("no leaked nodes", 0, Node::alive);
}

QUESTION("L14-M2", "removeAt", "removeAt(") {
    for (auto& c : PDF_REM) {
        Node* h = build(c.list);
        int before = Node::alive;
        std::string d = "list=" + show(c.list) + ", index=" + std::to_string(c.index);
        bool got = removeAt(h, c.index);
        check(d + " (return)", c.ret, got);
        check(d + " (list after)", c.after, values(h));
        check(d + " (nodes deleted)", c.ret ? 1 : 0, before - Node::alive);
        destroy(h);
    }
}

OPTIONAL_QUESTION("L14-X", "insertAtEnd (GfG, returns the head)", "insertAtEnd(") {
    Node* h = insertAtEnd(nullptr, 5);
    h = insertAtEnd(h, 6);
    check("insertAtEnd(nullptr, 5) then 6", V{5, 6}, values(h));
    destroy(h);
}

OPTIONAL_QUESTION("L14-V", "pushToBack (practice signature, O(1))", "pushToBack(") {
    Node* h = nullptr;
    Node* t = nullptr;
    for (int i = 1; i <= 4; i++) pushToBack(h, t, i);
    check("pushToBack 1..4", V{1, 2, 3, 4}, values(h));
    checkTrue("tail points at the last node", t && t->data == 4 && t->next == nullptr, "tail is wrong");
    destroy(h);
}
