// Lab 44 tests. The 2017 Assignment 5 Q4 values come from the archive's own output.
#include <algorithm>

#include "lab44.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;

static const V AS5 = {0, 12, 28, 14, 41, 18, 67, 52, 25, 10, 11, 4, 19, 37, 7, 22};
static const V AS5_BUILT = {0, 4, 10, 7, 12, 11, 19, 14, 25, 41, 28, 18, 67, 37, 52, 22};

static void rDown(V& h, int i) {
    int n = h.size() - 1;
    while (2 * i <= n) {
        int c = 2 * i;
        if (c + 1 <= n && h[c + 1] < h[c]) c++;
        if (h[c] >= h[i]) return;
        std::swap(h[c], h[i]);
        i = c;
    }
}
static V rBuild(V h) {
    for (int i = (h.size() - 1) / 2; i >= 1; i--) rDown(h, i);
    return h;
}
static V withZero(V v) {
    v.insert(v.begin(), 0);
    return v;
}

QUESTION("L44-A", "isMinHeap (1-based)", "isMinHeap(") {
    check("{0,1,3,2}", true, isMinHeap({0, 1, 3, 2}));
    check("{0,3,1}", false, isMinHeap({0, 3, 1}));
    check("AS5 built heap", true, isMinHeap(AS5_BUILT));
    check("AS5 array before building", false, isMinHeap(AS5));
    check("{0}: empty", true, isMinHeap({0}));
    check("h[0] is ignored", true, isMinHeap({99, 1, 2}));
}

QUESTION("L44-M1", "percolateDown (Labwork 8)", "percolateDown(") {
    V h = {0, 9, 2, 3, 4, 5};
    percolateDown(h, 1);
    check("{0,9,2,3,4,5}, i=1", V{0, 2, 4, 3, 9, 5}, h);
    V e = {0, 5, 5, 5};
    percolateDown(e, 1);
    check("equal children do not move a node", V{0, 5, 5, 5}, e);
    for (int t = 0; t < RANDOM_CASES; t++) {
        V a = rBuild(withZero(randVec(12, 0, 20, 1)));
        a[1] = randInt(0, 25);
        V w = a, got = a;
        rDown(w, 1);
        percolateDown(got, 1);
        check("semiheap " + show(a), w, got);
    }
}

QUESTION("L44-M2", "buildMinHeap (AS5 Q4-a)", "buildMinHeap(") {
    V h = AS5;
    buildMinHeap(h);
    check("AS5 Q4-a", AS5_BUILT, h);
    for (int t = 0; t < RANDOM_CASES; t++) {
        V a = withZero(randVec(14, 0, 20)), got = a;
        buildMinHeap(got);
        check("build " + show(a), rBuild(a), got);
    }
}

QUESTION("L44-M3", "deleteMin (AS5 Q4-b)", "deleteMin(") {
    V h = AS5_BUILT;
    check("AS5 Q4-b: the minimum", 4, deleteMin(h));
    check("AS5 Q4-b: the heap", V{0, 7, 10, 14, 12, 11, 19, 22, 25, 41, 28, 18, 67, 37, 52}, h);
    V e = {0};
    check("empty heap", -1, deleteMin(e));
    check("empty heap unchanged", V{0}, e);
    for (int t = 0; t < RANDOM_CASES; t++) {
        V a = rBuild(withZero(randVec(12, 0, 20, 1))), s(a.begin() + 1, a.end()), out;
        std::sort(s.begin(), s.end());
        while (a.size() > 1) out.push_back(deleteMin(a));
        check("delete everything", s, out);
    }
}

QUESTION("L44-M4", "insertMin (AS5 Q4-c)", "insertMin(") {
    V h = {0, 7, 10, 14, 12, 11, 19, 22, 25, 41, 28, 18, 67, 37, 52};
    insertMin(h, 19);
    check("AS5 Q4-c: insert 19", V{0, 7, 10, 14, 12, 11, 19, 19, 25, 41, 28, 18, 67, 37, 52, 22}, h);
    V e = {0};
    insertMin(e, 5);
    insertMin(e, 3);
    insertMin(e, 4);
    check("insert 5 3 4 into an empty heap", V{0, 3, 5, 4}, e);
    for (int t = 0; t < RANDOM_CASES; t++) {
        V keys = randVec(12, 0, 20), got = {0};
        for (int k : keys) insertMin(got, k);
        checkTrue("insert " + show(keys), got.size() == keys.size() + 1 && std::is_heap(got.begin() + 1, got.end(), std::greater<int>()),
                  "not a min-heap: " + show(got));
    }
}

OPTIONAL_QUESTION("L44-X", "arrayFromPreorder (AS5 Q4-d)", "arrayFromPreorder(") {
    check("AS5 Q4-d", V{0, 21, 19, 46, 24, 10, 25, 18, 18, 62}, arrayFromPreorder({21, 19, 24, 18, 62, 10, 46, 25, 18}));
    check("three items", V{0, 1, 2, 3}, arrayFromPreorder({1, 2, 3}));
}

OPTIONAL_QUESTION("L44-V", "heapInorder (Labwork 8)", "heapInorder(") {
    check("{0,1,2,3,4}", V{4, 2, 1, 3}, heapInorder({0, 1, 2, 3, 4}));
    check("empty", V{}, heapInorder({0}));
}
