// Lab 46 tests. Random graphs: Dijkstra vs. Bellman-Ford, Prim vs. Kruskal.
#include <algorithm>
#include <functional>
#include <numeric>

#include "lab46.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;
using VL = std::vector<long long>;

struct PDF_DJ_Case { int n; WEdges edges; int src; VL dist; };
struct PDF_CPU_Case { WEdges tasks; V order; };
#include "pdf_cases.inc"

static WEdges randEdges(int n, int maxE) {
    WEdges e;
    for (int k = randInt(0, maxE); k > 0; k--) e.push_back({randInt(0, n - 1), randInt(0, n - 1), randInt(0, 9)});
    return e;
}
static VL bellman(int n, const WEdges& e, int s) {
    VL d(n, -1);
    d[s] = 0;
    for (int r = 0; r < n; r++)
        for (auto& x : e)
            if (d[x[0]] != -1 && (d[x[1]] == -1 || d[x[0]] + x[2] < d[x[1]])) d[x[1]] = d[x[0]] + x[2];
    return d;
}
static long long kruskal(int n, WEdges e) {
    if (n <= 1) return 0;
    std::sort(e.begin(), e.end(), [](const V& a, const V& b) { return a[2] < b[2]; });
    V p(n);
    std::iota(p.begin(), p.end(), 0);
    std::function<int(int)> f = [&](int x) { return p[x] == x ? x : p[x] = f(p[x]); };
    long long t = 0;
    int used = 0;
    for (auto& x : e)
        if (f(x[0]) != f(x[1])) { p[f(x[0])] = f(x[1]); t += x[2]; used++; }
    return used == n - 1 ? t : -1;
}
static V slowCpu(const WEdges& tasks) {
    int n = tasks.size();
    std::vector<bool> done(n);
    V order;
    long long time = 0;
    while ((int)order.size() < n) {
        int pick = -1;
        for (int i = 0; i < n; i++)
            if (!done[i] && tasks[i][0] <= time && (pick < 0 || tasks[i][1] < tasks[pick][1])) pick = i;
        if (pick < 0) {
            long long nextT = -1;
            for (int i = 0; i < n; i++) if (!done[i] && (nextT < 0 || tasks[i][0] < nextT)) nextT = tasks[i][0];
            time = nextT;
            continue;
        }
        done[pick] = true;
        order.push_back(pick);
        time += tasks[pick][1];
    }
    return order;
}

QUESTION("L46-A", "StablePQ (Labwork 5)", "StablePQ::") {
    StablePQ q;
    std::string out = "none";
    check("dequeue on empty", false, q.dequeue(out));
    check("out unchanged", std::string("none"), out);
    q.enqueue("a", 1);
    q.enqueue("b", 5);
    q.enqueue("c", 5);
    q.enqueue("d", 3);
    check("size", 4, q.size());
    std::vector<std::string> got;
    while (q.dequeue(out)) got.push_back(out);
    check("higher first, FIFO on ties", std::vector<std::string>{"b", "c", "d", "a"}, got);
    for (int i = 0; i < 20; i++) q.enqueue(std::to_string(i), 7);
    q.dequeue(out);
    check("20 equal priorities: the first one", std::string("0"), out);
    q.dequeue(out);
    check("then the second", std::string("1"), out);
}

QUESTION("L46-M1", "dijkstra", "dijkstra(") {
    for (auto& c : PDF_DJ) check("n=" + std::to_string(c.n) + ", edges " + show(c.edges) + ", src " + std::to_string(c.src),
                                  c.dist, dijkstra(c.n, c.edges, c.src));
    for (int t = 0; t < RANDOM_CASES; t++) {
        int n = randInt(1, 7);
        WEdges e = randEdges(n, 12);
        int s = randInt(0, n - 1);
        check("edges " + show(e) + ", src " + std::to_string(s), bellman(n, e, s), dijkstra(n, e, s));
    }
}

QUESTION("L46-M2", "primHeap", "primHeap(") {
    WEdges lab35 = {{0, 1, 2}, {0, 3, 6}, {1, 2, 3}, {1, 3, 8}, {1, 4, 5}, {2, 4, 7}, {3, 4, 9}};
    check("the Lab 35 graph", 16LL, primHeap(5, lab35));
    check("not connected", -1LL, primHeap(3, {{0, 1, 4}}));
    check("one vertex", 0LL, primHeap(1, {}));
    check("parallel edges: the cheaper one", 2LL, primHeap(2, {{0, 1, 5}, {1, 0, 2}}));
    for (int t = 0; t < RANDOM_CASES; t++) {
        int n = randInt(1, 7);
        WEdges e = randEdges(n, 14);
        check("n=" + std::to_string(n) + ", edges " + show(e), kruskal(n, e), primHeap(n, e));
    }
}

QUESTION("L46-M3", "getOrder (LC 1834)", "getOrder(") {
    for (auto& c : PDF_CPU) check("tasks " + show(c.tasks), c.order, getOrder(c.tasks));
    for (int t = 0; t < RANDOM_CASES; t++) {
        WEdges tasks;
        for (int k = randInt(1, 8); k > 0; k--) tasks.push_back({randInt(0, 10), randInt(1, 5)});
        check("tasks " + show(tasks), slowCpu(tasks), getOrder(tasks));
    }
}

OPTIONAL_QUESTION("L46-X", "furthestBuilding (LC 1642)", "furthestBuilding(") {
    check("LeetCode example 1", 4, furthestBuilding({4, 2, 7, 6, 9, 14, 12}, 5, 1));
    check("LeetCode example 2", 7, furthestBuilding({4, 12, 2, 7, 3, 18, 20, 3, 19}, 10, 2));
    check("LeetCode example 3", 3, furthestBuilding({14, 3, 19, 3}, 17, 0));
}

OPTIONAL_QUESTION("L46-V", "lastStoneWeightPQ", "lastStoneWeightPQ(") {
    check("{2,7,4,1,8,1}", 1, lastStoneWeightPQ({2, 7, 4, 1, 8, 1}));
    check("{3,3}", 0, lastStoneWeightPQ({3, 3}));
}
