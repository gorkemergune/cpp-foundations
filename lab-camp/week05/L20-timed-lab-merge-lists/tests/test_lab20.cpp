// Lab 20 tests.
#include <algorithm>
#include <set>

#include "lab20.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_DD_Case { V list; V after; };
struct PDF_MERGE_Case { V a; V b; V out; };
struct PDF_CYCLE_Case { V list; int pos; bool ret; };
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
static V sortedRand(int maxLen) {
    V v = randVec(maxLen, 0, 6);
    std::sort(v.begin(), v.end());
    return v;
}

QUESTION("L20-A", "deleteDuplicates (LC 83)", "deleteDuplicates(") {
    auto run = [](const V& v, const V& want) {
        ListNode* h = build(v);
        int alive = ListNode::alive;
        h = deleteDuplicates(h);
        check(show(v), want, values(h));
        check(show(v) + " (deleted nodes)", (int)(v.size() - want.size()), alive - ListNode::alive);
        destroy(h);
    };
    for (auto& c : PDF_DD) run(c.list, c.after);
    for (int t = 0; t < RANDOM_CASES; t++) {
        V v = sortedRand(10), w = v;
        w.erase(std::unique(w.begin(), w.end()), w.end());
        run(v, w);
    }
}

QUESTION("L20-B", "mergeTwoLists (LC 21)", "mergeTwoLists(") {
    auto run = [](const V& a, const V& b, const V& want) {
        ListNode *x = build(a), *y = build(b);
        std::set<ListNode*> before;
        for (ListNode* p = x; p; p = p->next) before.insert(p);
        for (ListNode* p = y; p; p = p->next) before.insert(p);
        int alive = ListNode::alive;
        ListNode* m = mergeTwoLists(x, y);
        check(show(a) + " + " + show(b), want, values(m));
        bool same = ListNode::alive == alive;
        for (ListNode* p = m; p; p = p->next) same = same && before.count(p);
        checkTrue(show(a) + " + " + show(b) + " (relinked, no new nodes)", same, "nodes were created or copied");
        destroy(m);
    };
    for (auto& c : PDF_MERGE) run(c.a, c.b, c.out);
    for (int t = 0; t < RANDOM_CASES; t++) {
        V a = sortedRand(8), b = sortedRand(8), w;
        std::merge(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(w));
        run(a, b, w);
    }
}

QUESTION("L20-C", "hasCycle (LC 141)", "hasCycle(") {
    auto run = [](const V& v, int pos, bool want) {
        ListNode* h = build(v);
        ListNode* last = h;
        ListNode* target = nullptr;
        for (int i = 0; last && last->next; i++, last = last->next)
            if (i == pos) target = last;
        if (last && pos == (int)v.size() - 1) target = last;
        if (last && pos >= 0) last->next = target;
        check(show(v) + ", pos=" + std::to_string(pos), want, hasCycle(h));
        if (last) last->next = nullptr;      // break the cycle before freeing
        destroy(h);
    };
    for (auto& c : PDF_CYCLE) run(c.list, c.pos, c.ret);
    for (int t = 0; t < RANDOM_CASES; t++) {
        V v = randVec(12, 0, 9, 1);
        int pos = randInt(-1, (int)v.size() - 1);
        run(v, pos, pos >= 0);
    }
}

OPTIONAL_QUESTION("L20-X", "getIntersectionNode (LC 160)", "getIntersectionNode(") {
    ListNode* shared = build({8, 4, 5});
    ListNode* a = new ListNode(4, new ListNode(1, shared));
    ListNode* b = new ListNode(5, new ListNode(6, new ListNode(1, shared)));
    checkTrue("LeetCode example 1", getIntersectionNode(a, b) == shared, "expected the node 8");
    ListNode* c = build({2, 6, 4});
    ListNode* d = build({1, 5});
    checkTrue("no intersection", getIntersectionNode(c, d) == nullptr, "expected nullptr");
    destroy(c);
    destroy(d);
    delete a->next; delete a;
    delete b->next->next; delete b->next; delete b;
    destroy(shared);
}

OPTIONAL_QUESTION("L20-V", "removeElements (LC 203)", "removeElements(") {
    ListNode* h = removeElements(build({1, 2, 6, 3, 4, 5, 6}), 6);
    check("[1,2,6,3,4,5,6], 6", V{1, 2, 3, 4, 5}, values(h));
    destroy(h);
    h = removeElements(build({7, 7, 7, 7}), 7);
    checkTrue("[7,7,7,7], 7 -> empty", h == nullptr, "expected nullptr");
    check("no leaked nodes", 0, ListNode::alive);
}
