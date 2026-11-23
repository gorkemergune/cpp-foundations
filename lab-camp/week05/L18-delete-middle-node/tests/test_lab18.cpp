// Lab 18 tests: PDF rows + every length 0..12 against index arithmetic.
#include "lab18.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_DM_Case { V list; bool ret; V after; };
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
    int g = 0;
    while (h && g++ < 1000) {
        Node* n = h->next;
        delete h;
        h = n;
    }
}
static V seq(int n) {
    V v;
    for (int i = 1; i <= n; i++) v.push_back(i * 10);
    return v;
}

QUESTION("L18-A", "length", "length(") {
    for (int n = 0; n <= 6; n++) {
        Node* h = build(seq(n));
        check("length of a list of " + std::to_string(n), n, length(h));
        destroy(h);
    }
}

QUESTION("L18-B", "beforeMiddle (one pass)", "beforeMiddle(") {
    for (int n = 0; n <= 12; n++) {
        V v = seq(n);
        Node* h = build(v);
        Node* got = beforeMiddle(h);
        if (n < 2) checkTrue("n=" + std::to_string(n), got == nullptr, "expected nullptr");
        else checkTrue("n=" + std::to_string(n) + " (expected the node holding " + std::to_string(v[n / 2 - 1]) + ")",
                       got != nullptr && got->data == v[n / 2 - 1], "wrong node");
        destroy(h);
    }
}

QUESTION("L18-M", "deleteMiddle (midterm)", "deleteMiddle(") {
    auto run = [](const V& v, bool ret, const V& want) {
        Node* h = build(v);
        int alive = Node::alive;
        std::string d = "list=" + show(v);
        check(d + " (return)", ret, deleteMiddle(h));
        check(d + " (after)", want, values(h));
        check(d + " (deleted)", ret ? 1 : 0, alive - Node::alive);
        destroy(h);
    };
    for (auto& c : PDF_DM) run(c.list, c.ret, c.after);
    for (int n = 0; n <= 12; n++) {
        V v = seq(n), w = v;
        if (n) w.erase(w.begin() + n / 2);
        run(v, n > 0, w);
    }
}

OPTIONAL_QUESTION("L18-X", "deleteMiddleLC (LC 2095)", "deleteMiddleLC(") {
    Node* h = deleteMiddleLC(build({2, 1}));
    check("[2, 1] -> [2]", V{2}, values(h));
    destroy(h);
    h = deleteMiddleLC(build({5}));
    checkTrue("[5] -> empty", h == nullptr, "expected nullptr");
}

OPTIONAL_QUESTION("L18-V", "deleteLeftMiddle", "deleteLeftMiddle(") {
    for (int n = 0; n <= 12; n++) {
        V v = seq(n), w = v;
        if (n) w.erase(w.begin() + (n - 1) / 2);
        Node* h = build(v);
        check("n=" + std::to_string(n) + " (return)", n > 0, deleteLeftMiddle(h));
        check("n=" + std::to_string(n), w, values(h));
        destroy(h);
    }
}
