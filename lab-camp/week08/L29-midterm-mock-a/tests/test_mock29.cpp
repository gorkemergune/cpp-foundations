// Mock A tests.
#include <vector>

#include "mock29.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_CA_Case { V st; int x; int ret; };
struct PDF_DM_Case { V list; bool ret; V after; };
#include "pdf_cases.inc"

static void fill(Stack& s, const V& topFirst) {
    for (int i = (int)topFirst.size() - 1; i >= 0; i--) s.push(topFirst[i]);
}
static V drain(Stack& s) {
    V r;
    StackItemType x;
    while (s.pop(x)) r.push_back(x);
    return r;
}

QUESTION("L29-A", "moveTopSlides (two stacks)", "moveTopSlides(") {
    Stack a, b;
    fill(a, {9, 4});
    fill(b, {7});
    check("move 9 onto 7", true, moveTopSlides(a, b));
    Stack e, f;
    fill(f, {1});
    check("empty source", false, moveTopSlides(e, f));
    Stack full, src;
    for (int i = 0; i < MAX_STACK; i++) full.push(i);
    fill(src, {5});
    check("target full", false, moveTopSlides(src, full));
    check("a after", V{4}, drain(a));
    check("b after", V{9, 7}, drain(b));
    check("f unchanged", V{1}, drain(f));
    check("source unchanged when the target is full", V{5}, drain(src));
}

QUESTION("L29-B", "countAbove (empty / !empty)", "countAbove(") {
    for (auto& c : PDF_CA) {
        std::stack<int> st;
        for (int i = (int)c.st.size() - 1; i >= 0; i--) st.push(c.st[i]);
        check("stack " + show(c.st) + ", x=" + std::to_string(c.x), c.ret, countAbove(st, c.x));
        check("stack " + show(c.st) + " unchanged (passed by value)", (int)c.st.size(), (int)st.size());
    }
}

QUESTION("L29-C", "deleteMiddleDLL", "deleteMiddleDLL(") {
    for (auto& c : PDF_DM) {
        DNode *head = nullptr, *tail = nullptr;
        for (int x : c.list) {
            DNode* n = new DNode(x);
            n->prev = tail;
            if (tail) tail->next = n;
            else head = n;
            tail = n;
        }
        int alive = DNode::alive;
        std::string d = "list " + show(c.list);
        check(d + " (return)", c.ret, deleteMiddleDLL(head, tail));
        V fwd, bwd;
        for (DNode* p = head; p && fwd.size() < 100; p = p->next) fwd.push_back(p->data);
        for (DNode* p = tail; p && bwd.size() < 100; p = p->prev) bwd.push_back(p->data);
        check(d + " (forward)", c.after, fwd);
        check(d + " (backward through prev)", V(c.after.rbegin(), c.after.rend()), bwd);
        checkTrue(d + " (ends)", (head == nullptr) == (tail == nullptr) && (!head || (!head->prev && !tail->next)),
                  "head/tail are wrong");
        check(d + " (deleted)", c.ret ? 1 : 0, alive - DNode::alive);
        while (head) {
            DNode* n = head->next;
            delete head;
            head = n;
        }
    }
}
