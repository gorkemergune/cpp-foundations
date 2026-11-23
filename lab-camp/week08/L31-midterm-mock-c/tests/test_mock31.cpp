// Mock C tests.
#include <algorithm>

#include "mock31.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_BL_Case { V circle; bool ret; V after; };
struct PDF_TRI_Case { V q; V after; };
struct PDF_MQ_Case { V list; V after; };
#include "pdf_cases.inc"

static Node* circle(const V& v) {
    if (v.empty()) return nullptr;
    Node* first = new Node(v[0]);
    Node* last = first;
    for (size_t i = 1; i < v.size(); i++) last = last->next = new Node(v[i]);
    last->next = first;
    return last;
}
static V readCircle(Node* last) {
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
static void freeCircle(Node* last) {
    if (!last) return;
    Node* p = last->next;
    last->next = nullptr;
    while (p) {
        Node* n = p->next;
        delete p;
        p = n;
    }
}

QUESTION("L31-A", "deleteBeforeLast (circular)", "deleteBeforeLast(") {
    for (auto& c : PDF_BL) {
        Node* last = circle(c.circle);
        Node* oldLast = last;
        int alive = Node::alive;
        std::string d = "circle " + show(c.circle);
        check(d + " (return)", c.ret, deleteBeforeLast(last));
        check(d + " (after)", c.after, readCircle(last));
        checkTrue(d + " (last is the same node)", last == oldLast, "last must not move");
        check(d + " (deleted)", c.ret ? 1 : 0, alive - Node::alive);
        freeCircle(last);
    }
}

QUESTION("L31-B", "reverseAlternateTriplesLL (LLQueue + LLStack)", "reverseAlternateTriplesLL(") {
    auto run = [](const V& v, const V& want) {
        LLQueue<int> q;
        for (int x : v) q.enqueue(x);
        reverseAlternateTriplesLL(q);
        check("queue " + show(v), want, q.toVector());
    };
    for (auto& c : PDF_TRI) run(c.q, c.after);
    for (int t = 0; t < RANDOM_CASES; t++) {
        V v = randVec(15, 0, 9), w = v;
        for (size_t s = 0; s + 3 <= w.size(); s += 6) std::reverse(w.begin() + s, w.begin() + s + 3);
        run(v, w);
    }
}

QUESTION("L31-C", "deleteMiddleToLLQueue", "deleteMiddleToLLQueue(") {
    for (auto& c : PDF_MQ) {
        Node* head = nullptr;
        for (int i = (int)c.list.size() - 1; i >= 0; i--) head = new Node(c.list[i], head);
        LLQueue<int> out;
        deleteMiddleToLLQueue(head, out);
        V rest;
        for (Node* p = head; p; p = p->next) rest.push_back(p->data);
        check("list " + show(c.list) + " (list after)", c.after, rest);
        check("list " + show(c.list) + " (queue)", c.after, out.toVector());
        while (head) {
            Node* n = head->next;
            delete head;
            head = n;
        }
    }
    check("no leaked nodes", 0, Node::alive);
}
