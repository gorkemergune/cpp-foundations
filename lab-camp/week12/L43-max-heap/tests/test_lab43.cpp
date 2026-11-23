// Lab 43 tests. Random cases are compared with a small copy of the slides' code.
#include <algorithm>

#include "lab43.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_INS_Case { V keys; V heap; };
struct PDF_BUILD_Case { V array; V heap; };
#include "pdf_cases.inc"

static void rIns(V& a, int x) {
    a.push_back(x);
    int p = a.size() - 1;
    while (p > 0 && a[p] > a[(p - 1) / 2]) { std::swap(a[p], a[(p - 1) / 2]); p = (p - 1) / 2; }
}
static void rReb(V& a, int r, int n) {
    int c = 2 * r + 1;
    if (c >= n) return;
    if (c + 1 < n && a[c + 1] > a[c]) c++;
    if (a[r] < a[c]) { std::swap(a[r], a[c]); rReb(a, c, n); }
}
static V rBuild(V a) {
    for (int i = (int)a.size() / 2 - 1; i >= 0; i--) rReb(a, i, a.size());
    return a;
}

QUESTION("L43-A", "isMaxHeap", "isMaxHeap(") {
    check("{9,8,5,1,3,2}", true, isMaxHeap({9, 8, 5, 1, 3, 2}));
    check("{1,2}", false, isMaxHeap({1, 2}));
    check("{7,7,7}", true, isMaxHeap({7, 7, 7}));
    check("{9,8,5,1,3,6}: 6 > its parent 5", false, isMaxHeap({9, 8, 5, 1, 3, 6}));
    check("{}", true, isMaxHeap({}));
    for (int t = 0; t < RANDOM_CASES; t++) {
        V v = randVec(10, 0, 9);
        bool want = true;
        for (size_t i = 1; i < v.size(); i++) want = want && v[i] <= v[(i - 1) / 2];
        check(show(v), want, isMaxHeap(v));
    }
}

QUESTION("L43-B", "largerChild", "largerChild(") {
    V a = {9, 8, 5, 1, 3, 2};
    check("i=0", 1, largerChild(a, 0, 6));
    check("i=1 (children 1 and 3)", 4, largerChild(a, 1, 6));
    check("i=2 (only a left child)", 5, largerChild(a, 2, 6));
    check("i=2 with n=5 (no child)", -1, largerChild(a, 2, 5));
    check("equal children: the left one", 1, largerChild({5, 4, 4}, 0, 3));
}

QUESTION("L43-M1", "heapInsert (slide 13)", "heapInsert(") {
    for (auto& c : PDF_INS) {
        V h;
        for (int k : c.keys) heapInsert(h, k);
        check("insert " + show(c.keys), c.heap, h);
    }
    for (int t = 0; t < RANDOM_CASES; t++) {
        V keys = randVec(12, 0, 20), h, w;
        for (int k : keys) { heapInsert(h, k); rIns(w, k); }
        check("insert " + show(keys), w, h);
    }
}

QUESTION("L43-M2", "heapRebuild (slide 15)", "heapRebuild(") {
    V a = {2, 8, 5, 1, 3};
    heapRebuild(a, 0, 5);
    check("{2,8,5,1,3}, root 0", V{8, 3, 5, 1, 2}, a);
    V b = {1, 9, 8, 4, 7};
    heapRebuild(b, 0, 3);
    check("{1,9,8,4,7}, root 0, n=3 (4 and 7 are outside)", V{9, 1, 8, 4, 7}, b);
    for (int t = 0; t < RANDOM_CASES; t++) {
        V h = rBuild(randVec(12, 0, 20, 1));
        h[0] = randInt(0, 20);                // a semiheap at the root
        V w = h;
        rReb(w, 0, w.size());
        V got = h;
        heapRebuild(got, 0, got.size());
        check("semiheap " + show(h), w, got);
    }
}

QUESTION("L43-M3", "heapDelete (slide 14)", "heapDelete(") {
    V h = {9, 8, 5, 1, 3, 2};
    int x = -1;
    check("delete (return)", true, heapDelete(h, x));
    check("rootItem", 9, x);
    check("heap after", V{8, 3, 5, 1, 2}, h);
    heapDelete(h, x);
    check("second rootItem", 8, x);
    check("heap after", V{5, 3, 2, 1}, h);
    V e;
    x = 777;
    check("empty heap", false, heapDelete(e, x));
    check("rootItem unchanged", 777, x);
    for (int t = 0; t < RANDOM_CASES; t++) {
        V h2 = rBuild(randVec(12, 0, 20, 1)), s = h2, out;
        std::sort(s.rbegin(), s.rend());
        int y;
        while (heapDelete(h2, y)) out.push_back(y);
        check("delete everything from a heap of " + show(s), s, out);
    }
}

QUESTION("L43-M4", "buildHeap (slide 23)", "buildHeap(") {
    for (auto& c : PDF_BUILD) {
        V a = c.array;
        buildHeap(a);
        check("buildHeap " + show(c.array), c.heap, a);
    }
    for (int t = 0; t < RANDOM_CASES; t++) {
        V a = randVec(14, 0, 20), w = rBuild(a);
        V got = a;
        buildHeap(got);
        check("buildHeap " + show(a), w, got);
    }
}

OPTIONAL_QUESTION("L43-X", "lastStoneWeight (LC 1046)", "lastStoneWeight(") {
    check("{2,7,4,1,8,1}", 1, lastStoneWeight({2, 7, 4, 1, 8, 1}));
    check("{1}", 1, lastStoneWeight({1}));
    check("{3,3}", 0, lastStoneWeight({3, 3}));
}

OPTIONAL_QUESTION("L43-V", "topK", "topK(") {
    V h = {9, 8, 5, 1, 3, 2};
    check("k=3", V{9, 8, 5}, topK(h, 3));
    check("the heap itself is unchanged", V{9, 8, 5, 1, 3, 2}, h);
}
