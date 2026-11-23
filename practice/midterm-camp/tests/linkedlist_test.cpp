// LL tests: the PDF examples + edge cases (empty, single node, head/tail)
// + RANDOM_CASES random inputs checked against a simple std::vector reference.
#include "../ds/LinkedList.h"

namespace ll_test {
using namespace camp;
using V = std::vector<int>;

inline std::string D(const V& v) { return show(v); }
inline std::string I(int x) { return std::to_string(x); }

// was every removed node deleted? (base: Node::alive before the list was built)
inline void leak(const std::string& d, int base, const LinkedList& l) {
    int diff = Node::alive - (base + (int)l.toVector().size());
    if (diff == 0) pass();
    else if (diff > 0) fail(d + "  →  " + I(diff) + " node(s) were not deleted (memory leak)");
    else fail(d + "  →  a node that is still in the list was deleted");
}

// ---------------------------------------------------------------- LL-1
QUESTION("LL-1", "Node count", "LinkedList::count(") {
    auto run = [](const V& in) {
        LinkedList l(in);
        check(D(in), (int)in.size(), l.count());
        check(D(in) + " (list must stay unchanged)", in, l.toVector());
    };
    for (V in : std::vector<V>{{3, 8, 1}, {}, {7}, {1, 1, 1, 1, 1}, {0}, {-1, -2}}) run(in);
    for (int i = 0; i < RANDOM_CASES; i++) run(randVec(30, -50, 50));
}

// ---------------------------------------------------------------- LL-2
QUESTION("LL-2", "Occurrences of a value", "LinkedList::countValue(") {
    auto run = [](const V& in, int v) {
        LinkedList l(in);
        check(D(in) + ", v=" + I(v), (int)std::count(in.begin(), in.end(), v), l.countValue(v));
    };
    run({4, 2, 4, 4}, 4);
    run({4, 2, 4, 4}, 2);
    run({4, 2, 4, 4}, 9);
    run({}, 1);
    run({5}, 5);
    run({5}, 6);
    run({0, 0, 0}, 0);
    run({1, 2, 3}, 3);  // last node
    run({-4, 4, -4}, -4);
    for (int i = 0; i < RANDOM_CASES; i++) run(randVec(20, 0, 5), randInt(0, 6));
}

// ---------------------------------------------------------------- LL-3
QUESTION("LL-3", "Index of the maximum", "LinkedList::indexOfMax(") {
    auto run = [](const V& in) {
        LinkedList l(in);
        int exp = in.empty() ? -1 : (int)(std::max_element(in.begin(), in.end()) - in.begin());
        check(D(in), exp, l.indexOfMax());
    };
    for (V in : std::vector<V>{{3, 9, 2, 9}, {}, {7}, {1, 2, 3}, {5, 1, 2}, {4, 4, 4},
                               {-3, -1, -2}, {-5}, {0, -1}, {1, 9, 9, 9}, {2, 1, 3, 3}})
        run(in);
    for (int i = 0; i < RANDOM_CASES; i++) run(randVec(20, -20, 20));
}

// ---------------------------------------------------------------- LL-4
QUESTION("LL-4", "Insert at end", "LinkedList::insertAtEnd(") {
    auto run = [](const V& start, const V& adds) {
        LinkedList l(start);
        V exp = start;
        std::string d = D(start);
        for (int x : adds) {
            l.insertAtEnd(x);
            exp.push_back(x);
            d += " + " + I(x);
        }
        check(d, exp, l.toVector());
    };
    run({1, 2}, {7});
    run({}, {5});
    run({}, {1, 2, 3});
    run({9}, {9, 9});
    run({1, 2, 3}, {-1});
    for (int i = 0; i < RANDOM_CASES; i++) run(randVec(10, 0, 9), randVec(5, 0, 9, 1));
}

// ---------------------------------------------------------------- LL-5
QUESTION("LL-5", "Remove first occurrence", "LinkedList::removeFirst(") {
    auto run = [](const V& in, int v) {
        V exp = in;
        auto it = std::find(exp.begin(), exp.end(), v);
        bool found = it != exp.end();
        if (found) exp.erase(it);

        int base = Node::alive;
        LinkedList l(in);
        std::string d = D(in) + ", v=" + I(v);
        check(d + " return", found, l.removeFirst(v));
        check(d + " list", exp, l.toVector());
        leak(d, base, l);
    };
    run({1, 4, 3, 4}, 4);
    run({4, 1}, 4);  // head
    run({1, 4}, 4);  // tail
    run({7}, 7);     // only node
    run({1, 2}, 9);
    run({}, 3);
    run({4, 4, 4}, 4);
    run({1, 2, 3, 4, 5}, 3);
    for (int i = 0; i < RANDOM_CASES; i++) run(randVec(12, 0, 6), randInt(0, 7));
}

// ---------------------------------------------------------------- LL-6
QUESTION("LL-6", "Reverse the list", "LinkedList::reverse(") {
    auto run = [](const V& in) {
        int base = Node::alive;
        LinkedList l(in);
        auto before = l.nodes();
        l.reverse();
        check(D(in), V(in.rbegin(), in.rend()), l.toVector());
        std::reverse(before.begin(), before.end());
        checkTrue(D(in) + " (in place?)", before == l.nodes(),
                  "the same nodes must appear in reverse order: don't allocate new nodes or change items, flip the pointers");
        leak(D(in), base, l);
    };
    for (V in : std::vector<V>{{1, 2, 3}, {}, {5}, {1, 2}, {1, 2, 3, 4, 5, 6}, {2, 2, 1}})
        run(in);
    for (int i = 0; i < RANDOM_CASES; i++) run(randVec(25, -9, 9));
    {  // reversing twice must give back the original
        LinkedList l{1, 2, 3, 4};
        l.reverse();
        l.reverse();
        check("[1, 2, 3, 4] reversed twice", V{1, 2, 3, 4}, l.toVector());
    }
}

// ---------------------------------------------------------------- LL-7
QUESTION("LL-7", "Insert into a sorted list", "LinkedList::insertSorted(") {
    auto run = [](V in, int v) {
        std::sort(in.begin(), in.end());
        V exp = in;
        exp.insert(std::upper_bound(exp.begin(), exp.end(), v), v);
        LinkedList l(in);
        l.insertSorted(v);
        check(D(in) + ", v=" + I(v), exp, l.toVector());
    };
    run({1, 3, 8}, 5);
    run({}, 4);
    run({3, 5}, 1);  // new head
    run({3, 5}, 9);  // new tail
    run({2, 4}, 4);  // equal to tail
    run({2, 4}, 2);  // equal to head
    run({5}, 5);
    run({-3, 0, 3}, -1);
    for (int i = 0; i < RANDOM_CASES; i++) run(randVec(12, -10, 10), randInt(-12, 12));
    {  // building a sorted list from scratch
        LinkedList l;
        V vals = {5, 1, 4, 2, 3, 1};
        for (int x : vals) l.insertSorted(x);
        check("empty + 5,1,4,2,3,1", V{1, 1, 2, 3, 4, 5}, l.toVector());
    }
}

// ---------------------------------------------------------------- LL-8
QUESTION("LL-8", "Insert after every target", "LinkedList::insertAfterEach(") {
    auto run = [](const V& in, int target, int value) {
        V exp;
        int added = 0;
        for (int x : in) {
            exp.push_back(x);
            if (x == target) {
                exp.push_back(value);
                added++;
            }
        }
        LinkedList l(in);
        std::string d = D(in) + ", target=" + I(target) + ", value=" + I(value);
        check(d + " return", added, l.insertAfterEach(target, value));
        check(d + " list", exp, l.toVector());
    };
    run({2, 5, 2}, 2, 9);
    run({1, 2, 3}, 7, 0);
    run({}, 1, 1);
    run({5}, 5, 1);
    run({2, 2}, 2, 2);  // target == value trap
    run({1, 2, 3}, 3, 4);  // after the tail
    run({7, 7, 7}, 7, 0);
    for (int i = 0; i < RANDOM_CASES; i++) run(randVec(12, 0, 4), randInt(0, 4), randInt(0, 4));
}

// ---------------------------------------------------------------- LL-9
QUESTION("LL-9", "Remove duplicates (unsorted)", "LinkedList::removeDuplicates(") {
    auto run = [](const V& in) {
        V exp;
        for (int x : in)
            if (std::find(exp.begin(), exp.end(), x) == exp.end()) exp.push_back(x);
        int base = Node::alive;
        LinkedList l(in);
        check(D(in) + " return", (int)(in.size() - exp.size()), l.removeDuplicates());
        check(D(in) + " list", exp, l.toVector());
        leak(D(in), base, l);
    };
    for (V in : std::vector<V>{{3, 1, 3, 2, 1}, {1, 1, 1, 1}, {}, {1, 2, 3}, {5, 5, 6, 6, 5},
                               {7}, {1, 2, 1, 2, 1, 2}, {4, 3, 2, 1, 1, 2, 3, 4}})
        run(in);
    for (int i = 0; i < RANDOM_CASES; i++) run(randVec(15, 0, 6));
}

// ---------------------------------------------------------------- LL-10
QUESTION("LL-10", "Swap adjacent pairs", "LinkedList::swapPairs(") {
    auto run = [](const V& in) {
        LinkedList l(in);
        auto nodes = l.nodes();
        for (size_t i = 0; i + 1 < nodes.size(); i += 2) std::swap(nodes[i], nodes[i + 1]);
        V exp = in;
        for (size_t i = 0; i + 1 < exp.size(); i += 2) std::swap(exp[i], exp[i + 1]);
        l.swapPairs();
        check(D(in), exp, l.toVector());
        checkTrue(D(in) + " (with pointers?)", nodes == l.nodes(),
                  "the nodes themselves must move; changing item values is forbidden");
    };
    for (V in : std::vector<V>{{1, 2, 3, 4, 5}, {1, 2, 3, 4}, {}, {1}, {1, 2}, {1, 2, 3},
                               {1, 2, 3, 4, 5, 6, 7, 8}})
        run(in);
    for (int i = 0; i < RANDOM_CASES; i++) run(randVec(20, 0, 99));
}

}  // namespace ll_test
