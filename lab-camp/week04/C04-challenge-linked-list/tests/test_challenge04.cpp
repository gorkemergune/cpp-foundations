// Challenge 04 tests: PDF rows + random lists against simple vector versions.
#include "challenge04.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_ADD_Case { V l1; V l2; V sum; };
struct PDF_NTH_Case { V list; int n; V after; };
struct PDF_REORDER_Case { V list; V after; };
#include "pdf_cases.inc"

static ListNode* build(const V& v) {
    ListNode* h = nullptr;
    for (int i = (int)v.size() - 1; i >= 0; i--) h = new ListNode(v[i], h);
    return h;
}
static V values(ListNode* h) {
    V r;
    for (int g = 0; h && g < 1000; h = h->next, g++) r.push_back(h->val);
    return r;
}
static void destroy(ListNode* h) {
    int g = 0;
    while (h && g++ < 1000) {
        ListNode* n = h->next;
        delete h;
        h = n;
    }
}

QUESTION("C04-A", "addTwoNumbers (LC 2)", "addTwoNumbers(") {
    auto run = [](const V& a, const V& b, const V& want) {
        ListNode *x = build(a), *y = build(b);
        ListNode* s = addTwoNumbers(x, y);
        check(show(a) + " + " + show(b), want, values(s));
        check(show(a) + " + " + show(b) + " (inputs unchanged)", a, values(x));
        destroy(x);
        destroy(y);
        destroy(s);
    };
    for (auto& c : PDF_ADD) run(c.l1, c.l2, c.sum);
    for (int t = 0; t < RANDOM_CASES; t++) {
        V a = randVec(6, 0, 9, 1), b = randVec(6, 0, 9, 1), w;
        int carry = 0;
        for (size_t i = 0; i < std::max(a.size(), b.size()) || carry; i++) {
            int s = carry + (i < a.size() ? a[i] : 0) + (i < b.size() ? b[i] : 0);
            w.push_back(s % 10);
            carry = s / 10;
        }
        run(a, b, w);
    }
    check("no leaked nodes", 0, ListNode::alive);
}

QUESTION("C04-B", "removeNthFromEnd (LC 19)", "removeNthFromEnd(") {
    auto run = [](const V& v, int n, const V& want) {
        ListNode* h = build(v);
        int alive = ListNode::alive;
        h = removeNthFromEnd(h, n);
        check(show(v) + ", n=" + std::to_string(n), want, values(h));
        check(show(v) + ", n=" + std::to_string(n) + " (deleted)", 1, alive - ListNode::alive);
        destroy(h);
    };
    for (auto& c : PDF_NTH) run(c.list, c.n, c.after);
    for (int t = 0; t < RANDOM_CASES; t++) {
        V v = randVec(10, 0, 9, 1), w = v;
        int n = randInt(1, (int)v.size());
        w.erase(w.end() - n);
        run(v, n, w);
    }
}

QUESTION("C04-C", "reorderList (LC 143)", "reorderList(") {
    auto run = [](const V& v, const V& want) {
        ListNode* h = build(v);
        int alive = ListNode::alive;
        reorderList(h);
        check(show(v), want, values(h));
        check(show(v) + " (no new nodes)", alive, ListNode::alive);
        destroy(h);
    };
    for (auto& c : PDF_REORDER) run(c.list, c.after);
    for (int t = 0; t < RANDOM_CASES; t++) {
        V v = randVec(12, 0, 9), w;
        for (int i = 0, j = (int)v.size() - 1; i <= j; i++, j--) {
            w.push_back(v[i]);
            if (i != j) w.push_back(v[j]);
        }
        run(v, w);
    }
}
