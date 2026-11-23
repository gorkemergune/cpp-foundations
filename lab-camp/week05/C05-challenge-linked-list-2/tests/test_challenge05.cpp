// Challenge 05 tests.
#include <algorithm>
#include <map>

#include "challenge05.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_CYC_Case { V list; int pos; };
struct PDF_KG_Case { V list; int k; V after; };
#include "pdf_cases.inc"

static std::vector<ListNode*> buildNodes(const V& v) {
    std::vector<ListNode*> ns;
    for (int x : v) ns.push_back(new ListNode(x));
    for (size_t i = 0; i + 1 < ns.size(); i++) ns[i]->next = ns[i + 1];
    return ns;
}
static V values(ListNode* h) {
    V r;
    for (int g = 0; h && g < 1000; h = h->next, g++) r.push_back(h->val);
    return r;
}

QUESTION("C05-A", "detectCycle (LC 142)", "detectCycle(") {
    auto run = [](const V& v, int pos) {
        auto ns = buildNodes(v);
        if (!ns.empty() && pos >= 0) ns.back()->next = ns[pos];
        ListNode* got = detectCycle(ns.empty() ? nullptr : ns[0]);
        ListNode* want = pos >= 0 ? ns[pos] : nullptr;
        checkTrue(show(v) + ", pos=" + std::to_string(pos), got == want,
                  pos >= 0 ? "expected the node at index " + std::to_string(pos) : "expected nullptr");
        for (ListNode* n : ns) delete n;
    };
    for (auto& c : PDF_CYC) run(c.list, c.pos);
    for (int t = 0; t < RANDOM_CASES; t++) {
        V v = randVec(15, 0, 9, 1);
        run(v, randInt(-1, (int)v.size() - 1));
    }
}

QUESTION("C05-B", "reverseKGroup (LC 25)", "reverseKGroup(") {
    auto run = [](const V& v, int k, const V& want) {
        auto ns = buildNodes(v);
        int alive = ListNode::alive;
        ListNode* h = reverseKGroup(ns.empty() ? nullptr : ns[0], k);
        check(show(v) + ", k=" + std::to_string(k), want, values(h));
        check(show(v) + " (no new nodes)", alive, ListNode::alive);
        for (ListNode* n : ns) delete n;
    };
    for (auto& c : PDF_KG) run(c.list, c.k, c.after);
    for (int t = 0; t < RANDOM_CASES; t++) {
        V v = randVec(12, 0, 9);
        int k = randInt(1, 5);
        V w = v;
        for (size_t s = 0; s + k <= w.size(); s += k) std::reverse(w.begin() + s, w.begin() + s + k);
        run(v, k, w);
    }
}

QUESTION("C05-C", "copyRandomList (LC 138)", "copyRandomList(") {
    for (int t = 0; t < RANDOM_CASES; t++) {
        int n = randInt(0, 8);
        std::vector<RNode*> ns;
        for (int i = 0; i < n; i++) ns.push_back(new RNode(randInt(0, 9)));
        std::vector<int> rnd(n);
        for (int i = 0; i < n; i++) {
            if (i + 1 < n) ns[i]->next = ns[i + 1];
            rnd[i] = randInt(-1, n - 1);
            ns[i]->random = rnd[i] >= 0 ? ns[rnd[i]] : nullptr;
        }
        int alive = RNode::alive;
        RNode* c = copyRandomList(n ? ns[0] : nullptr);
        std::vector<RNode*> cs;
        for (RNode* p = c; p && cs.size() < 100; p = p->next) cs.push_back(p);
        bool ok = (int)cs.size() == n && RNode::alive == alive + n;
        std::map<RNode*, int> idx;
        for (int i = 0; i < (int)cs.size(); i++) idx[cs[i]] = i;
        for (int i = 0; ok && i < n; i++) {
            ok = cs[i] != ns[i] && cs[i]->val == ns[i]->val;
            if (rnd[i] < 0) ok = ok && cs[i]->random == nullptr;
            else ok = ok && idx.count(cs[i]->random) && idx[cs[i]->random] == rnd[i];
            ok = ok && (i + 1 < n ? ns[i]->next == ns[i + 1] : ns[i]->next == nullptr);   // original restored
            ok = ok && ns[i]->random == (rnd[i] >= 0 ? ns[rnd[i]] : nullptr);
        }
        checkTrue("random list of " + std::to_string(n) + " nodes", ok,
                  "copy wrong, random points into the original, or the original was not restored");
        for (RNode* p : cs) delete p;
        for (RNode* p : ns) delete p;
    }
}
