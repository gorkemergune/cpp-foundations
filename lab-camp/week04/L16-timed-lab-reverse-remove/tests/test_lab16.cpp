// Lab 16 tests. Node addresses prove "in place"; Node::alive catches leaks.
#include <algorithm>

#include "lab16.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_REV_Case { V list; V after; };
struct PDF_RF_Case { V list; int v; bool ret; V after; };
struct PDF_MID_Case { V list; int middleIndex; };
struct PDF_PAL_Case { V list; bool ret; };
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
static std::vector<Node*> nodes(Node* h) {
    std::vector<Node*> r;
    for (int g = 0; h && g < 1000; h = h->next, g++) r.push_back(h);
    return r;
}
static void destroy(Node* h) {
    int g = 0;
    while (h && g++ < 1000) {
        Node* n = h->next;
        delete h;
        h = n;
    }
}

QUESTION("L16-A", "reverseList (LC 206)", "reverseList(") {
    auto run = [](const V& v, const V& want) {
        Node* h = build(v);
        std::vector<Node*> before = nodes(h);
        int alive = Node::alive;
        Node* r = reverseList(h);
        check("reverse " + show(v), want, values(r));
        std::vector<Node*> after = nodes(r);
        std::reverse(before.begin(), before.end());
        checkTrue("reverse " + show(v) + " (same nodes)", before == after && Node::alive == alive,
                  "new nodes were created or nodes were lost: relink, do not copy");
        destroy(r);
    };
    for (auto& c : PDF_REV) run(c.list, c.after);
    for (int i = 0; i < RANDOM_CASES; i++) {
        V v = randVec(20, 0, 9), w = v;
        std::reverse(w.begin(), w.end());
        run(v, w);
    }
}

QUESTION("L16-B", "removeFirst", "removeFirst(") {
    auto run = [](const V& v, int x, bool ret, const V& want) {
        Node* h = build(v);
        int alive = Node::alive;
        std::string d = "list=" + show(v) + ", v=" + std::to_string(x);
        bool got = removeFirst(h, x);
        check(d + " (return)", ret, got);
        check(d + " (list after)", want, values(h));
        check(d + " (nodes deleted)", ret ? 1 : 0, alive - Node::alive);
        destroy(h);
    };
    for (auto& c : PDF_RF) run(c.list, c.v, c.ret, c.after);
    for (int i = 0; i < RANDOM_CASES; i++) {
        V v = randVec(10, 0, 4), w = v;
        int x = randInt(0, 5);
        auto it = std::find(w.begin(), w.end(), x);
        bool found = it != w.end();
        if (found) w.erase(it);
        run(v, x, found, w);
    }
}

QUESTION("L16-C", "middleNode (LC 876)", "middleNode(") {
    for (auto& c : PDF_MID) {
        Node* h = build(c.list);
        std::vector<Node*> ns = nodes(h);
        Node* got = middleNode(h);
        Node* want = c.middleIndex < 0 ? nullptr : ns[c.middleIndex];
        checkTrue("middleNode of " + show(c.list), got == want,
                  "expected the node at index " + std::to_string(c.middleIndex));
        destroy(h);
    }
    for (int i = 0; i < RANDOM_CASES; i++) {
        V v = randVec(15, 0, 9, 1);
        Node* h = build(v);
        checkTrue("middleNode of a list of length " + std::to_string(v.size()), middleNode(h) == nodes(h)[v.size() / 2],
                  "wrong node");
        destroy(h);
    }
}

OPTIONAL_QUESTION("L16-X", "isPalindrome (LC 234)", "isPalindrome(") {
    for (auto& c : PDF_PAL) {
        Node* h = build(c.list);
        check("list=" + show(c.list), c.ret, isPalindrome(h));
        check("list=" + show(c.list) + " (unchanged afterwards)", c.list, values(h));
        destroy(h);
    }
}

OPTIONAL_QUESTION("L16-V", "countValue", "countValue(") {
    Node* h = build({4, 1, 4});
    check("4 -> 1 -> 4, v = 4", 2, countValue(h, 4));
    check("4 -> 1 -> 4, v = 9", 0, countValue(h, 9));
    check("empty", 0, countValue(nullptr, 1));
    destroy(h);
}
