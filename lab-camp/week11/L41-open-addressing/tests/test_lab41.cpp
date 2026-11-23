// Lab 41 tests. The slides' examples (size 11) are in the PDF tables.
#include <set>

#include "lab41.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_OA_Case { std::string mode; int size; V keys; V where; std::string layout; };
#include "pdf_cases.inc"

static Probing modeOf(const std::string& m) {
    return m == "linear" ? Probing::LINEAR : m == "quadratic" ? Probing::QUADRATIC : Probing::DOUBLE;
}

QUESTION("L41-A", "probe", "probe(") {
    OpenTable lin(11, Probing::LINEAR), quad(11, Probing::QUADRATIC), dbl(11, Probing::DOUBLE);
    check("linear 9, i=0..2", V{9, 10, 0}, V{lin.probe(9, 0), lin.probe(9, 1), lin.probe(9, 2)});
    check("quadratic 24, i=0..2", V{2, 3, 6}, V{quad.probe(24, 0), quad.probe(24, 1), quad.probe(24, 2)});
    check("quadratic 9, i=0..3", V{9, 10, 2, 7}, V{quad.probe(9, 0), quad.probe(9, 1), quad.probe(9, 2), quad.probe(9, 3)});
    check("double 91 (h2 = 7), i=0..2", V{3, 10, 6}, V{dbl.probe(91, 0), dbl.probe(91, 1), dbl.probe(91, 2)});
    check("double 14 (h2 = 7 - 0 = 7), i=1", 10, dbl.probe(14, 1));
}

QUESTION("L41-B", "layout", "layout(") {
    check("empty table of 3", std::string("_ _ _"), OpenTable(3, Probing::LINEAR).layout());
    check("empty table of 1", std::string("_"), OpenTable(1, Probing::DOUBLE).layout());
}

QUESTION("L41-M1", "insert", "insert(") {
    for (auto& c : PDF_OA) {
        OpenTable t(c.size, modeOf(c.mode));
        V where;
        for (int k : c.keys) where.push_back(t.insert(k));
        check(c.mode + " insert " + show(c.keys) + " (indexes)", c.where, where);
        check(c.mode + " insert " + show(c.keys) + " (layout)", c.layout, t.layout());
    }
}

QUESTION("L41-M2", "find (DELETED does not stop it)", "find(") {
    OpenTable t(11, Probing::LINEAR);
    for (int k : {20, 30, 2, 13, 25, 24, 10, 9}) t.insert(k);
    check("find 24", 5, t.find(24));
    check("find 9 (wrapped around to 0)", 0, t.find(9));
    check("find 35 (stops at the empty slot 6)", -1, t.find(35));
    check("find 46", -1, t.find(46));
    OpenTable full(3, Probing::LINEAR);
    for (int k : {0, 1, 2}) full.insert(k);
    check("find in a full table, key missing", -1, full.find(3));
}

QUESTION("L41-M3", "remove", "remove(") {
    OpenTable t(11, Probing::LINEAR);
    for (int k : {20, 30, 2, 13, 25, 24}) t.insert(k);
    check("remove 13", true, t.remove(13));
    check("layout", std::string("_ _ 2 x 25 24 _ _ 30 20 _"), t.layout());
    check("find 24 after removing 13", 5, t.find(24));
    check("find 13", -1, t.find(13));
    check("remove 13 again", false, t.remove(13));
    check("insert 46 reuses the DELETED slot 3", 3, t.insert(46));
    check("insert 24 again (it is further along)", -1, t.insert(24));
    for (int r = 0; r < RANDOM_CASES; r++) {
        int n = randInt(1, 13);
        Probing m = (Probing)randInt(0, 2);
        OpenTable h(n, m);
        std::set<int> ref;
        bool ok = true;
        for (int s = 0; s < 40 && ok; s++) {
            int x = randInt(0, 30), op = randInt(0, 2);
            if (op == 0) {
                int at = h.insert(x);
                if (ref.count(x)) ok = at == -1;
                else if (at != -1) ref.insert(x);
            }
            if (op == 1) ok = h.remove(x) == (ref.erase(x) == 1);
            if (op == 2) ok = (h.find(x) != -1) == (ref.count(x) == 1);
        }
        checkTrue("random operations, size " + std::to_string(n), ok, "a key was lost, duplicated or found after removal");
    }
}

OPTIONAL_QUESTION("L41-X", "rehash", "rehash(") {
    OpenTable t(5, Probing::LINEAR);
    t.insert(1);
    t.insert(6);
    t.insert(3);
    t.remove(3);
    t.rehash();
    check("size 5 -> 11, DELETED gone", std::string("_ 1 _ _ _ _ 6 _ _ _ _"), t.layout());
}

OPTIONAL_QUESTION("L41-V", "longestCluster", "longestCluster(") {
    OpenTable t(11, Probing::LINEAR);
    for (int k : {20, 30, 2, 13, 25, 24, 10, 9}) t.insert(k);
    check("slide 19 table", 4, t.longestCluster());
    check("empty table", 0, OpenTable(4, Probing::LINEAR).longestCluster());
}
