// Challenge 12 tests.
#include <algorithm>
#include <map>
#include <set>

#include "challenge12.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_MK_Case { std::vector<V> lists; V merged; };
struct PDF_TK_Case { V nums; int k; V top; };
#include "pdf_cases.inc"

static ListNode* make(const V& v) {
    ListNode* h = nullptr;
    for (int i = (int)v.size() - 1; i >= 0; i--) h = new ListNode(v[i], h);
    return h;
}

QUESTION("C12-A", "mergeKLists (LC 23)", "mergeKLists(") {
    auto run = [](const std::vector<V>& in, const V& want) {
        std::vector<ListNode*> lists;
        std::set<ListNode*> nodes;
        for (auto& v : in) {
            lists.push_back(make(v));
            for (ListNode* p = lists.back(); p; p = p->next) nodes.insert(p);
        }
        ListNode* m = mergeKLists(lists);
        V got;
        bool reused = true;
        for (ListNode* p = m; p && got.size() < 500; p = p->next) {
            got.push_back(p->val);
            reused = reused && nodes.count(p);
        }
        check("lists " + show(in), want, got);
        checkTrue("lists " + show(in) + " (nodes relinked)", reused, "a new node was created");
        for (ListNode* p : nodes) delete p;
    };
    for (auto& c : PDF_MK) run(c.lists, c.merged);
    for (int t = 0; t < RANDOM_CASES; t++) {
        std::vector<V> in;
        V all;
        for (int k = randInt(0, 5); k > 0; k--) {
            V v = randVec(6, -9, 9);
            std::sort(v.begin(), v.end());
            in.push_back(v);
            all.insert(all.end(), v.begin(), v.end());
        }
        std::sort(all.begin(), all.end());
        run(in, all);
    }
}

QUESTION("C12-B", "MedianFinder (LC 295)", "MedianFinder::") {
    MedianFinder m;
    m.addNum(1);
    m.addNum(2);
    check("1 2", 1.5 == m.findMedian(), true);
    m.addNum(3);
    check("1 2 3", 2.0 == m.findMedian(), true);
    for (int t = 0; t < RANDOM_CASES; t++) {
        MedianFinder f;
        V seen;
        bool ok = true;
        for (int k = randInt(1, 15); k > 0 && ok; k--) {
            int x = randInt(-20, 20);
            f.addNum(x);
            seen.push_back(x);
            V s = seen;
            std::sort(s.begin(), s.end());
            double want = s.size() % 2 ? s[s.size() / 2] : (s[s.size() / 2 - 1] + (double)s[s.size() / 2]) / 2;
            ok = want == f.findMedian();
        }
        checkTrue("stream " + show(seen), ok, "wrong median at some point");
    }
}

QUESTION("C12-C", "topKFrequent (LC 347)", "topKFrequent(") {
    auto sorted = [](V v) { std::sort(v.begin(), v.end()); return v; };
    for (auto& c : PDF_TK) check("nums " + show(c.nums) + ", k=" + std::to_string(c.k), sorted(c.top), sorted(topKFrequent(c.nums, c.k)));
    for (int t = 0; t < RANDOM_CASES; t++) {
        V v;
        int distinct = randInt(1, 5);
        for (int d = 0; d < distinct; d++)              // value d appears 2^d .. times: unique answer
            for (int r = 0; r < (1 << d); r++) v.push_back(d * 7 - 10);
        std::shuffle(v.begin(), v.end(), rng());
        int k = randInt(1, distinct);
        V want;
        for (int d = distinct - 1; d >= distinct - k; d--) want.push_back(d * 7 - 10);
        check("nums " + show(v) + ", k=" + std::to_string(k), sorted(want), sorted(topKFrequent(v, k)));
    }
}
