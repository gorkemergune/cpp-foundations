// Mini Project 06 tests.
#include <algorithm>

#include "test.h"
#include "triage.h"

using namespace lab;

static std::vector<std::string> drain(Triage& t) {
    std::vector<std::string> out;
    std::string n;
    while (t.treat(n)) out.push_back(n);
    return out;
}

QUESTION("P06-A", "arrive / peek / treat / waiting", "Triage::arrive(") {
    Triage t;
    std::string n = "none";
    check("peek on an empty room", false, t.peek(n));
    check("treat on an empty room", false, t.treat(n));
    check("name unchanged", std::string("none"), n);
    t.arrive("Ali", 2);
    t.arrive("Ayse", 5);
    t.arrive("Can", 3);
    t.arrive("Deniz", 5);
    t.arrive("Ece", 2);
    check("waiting", 5, t.waiting());
    t.peek(n);
    check("peek", std::string("Ayse"), n);
    check("waiting after peek", 5, t.waiting());
    check("treatment order", std::vector<std::string>{"Ayse", "Deniz", "Can", "Ali", "Ece"}, drain(t));
    for (int r = 0; r < 20; r++) t.arrive("P" + std::to_string(r), 1);
    t.treat(n);
    check("20 equal severities: the first arrival", std::string("P0"), n);
}

QUESTION("P06-B", "upgrade / leave", "Triage::upgrade(") {
    Triage t;
    for (auto [n, s] : std::vector<std::pair<std::string, int>>{{"Ali", 2}, {"Ayse", 5}, {"Can", 3}, {"Deniz", 4}, {"Ece", 1}})
        t.arrive(n, s);
    check("upgrade Ece to 5 (after Ayse: she came later)", true, t.upgrade("Ece", 5));
    check("upgrade Can to 2 (not higher)", false, t.upgrade("Can", 2));
    check("upgrade an unknown name", false, t.upgrade("Zeynep", 5));
    check("leave Deniz", true, t.leave("Deniz"));
    check("leave Deniz again", false, t.leave("Deniz"));
    check("waiting", 4, t.waiting());
    check("order", std::vector<std::string>{"Ayse", "Ece", "Can", "Ali"}, drain(t));
    for (int r = 0; r < RANDOM_CASES; r++) {             // random operations vs. a sorted list
        Triage q;
        struct E { std::string n; int s; int a; };
        std::vector<E> ref;
        int next = 0;
        bool ok = true;
        for (int k = 0; k < 25 && ok; k++) {
            int op = randInt(0, 3);
            if (op <= 1 || ref.empty()) {
                std::string n = "p" + std::to_string(next);
                int s = randInt(1, 5);
                q.arrive(n, s);
                ref.push_back({n, s, next++});
            } else if (op == 2) {
                E& e = ref[randInt(0, (int)ref.size() - 1)];
                int s = randInt(1, 6);
                bool want = s > e.s;
                ok = q.upgrade(e.n, s) == want;
                if (want) e.s = s;
            } else {
                int i = randInt(0, (int)ref.size() - 1);
                ok = q.leave(ref[i].n);
                ref.erase(ref.begin() + i);
            }
        }
        std::sort(ref.begin(), ref.end(), [](const E& a, const E& b) { return a.s != b.s ? a.s > b.s : a.a < b.a; });
        std::vector<std::string> want;
        for (auto& e : ref) want.push_back(e.n);
        checkTrue("random operations", ok && drain(q) == want, "wrong order after upgrade/leave");
    }
}

QUESTION("P06-C", "report", "Triage::report(") {
    Triage t;
    check("empty room", std::string(""), t.report());
    t.arrive("Ali", 2);
    t.arrive("Ayse", 5);
    t.arrive("Can", 3);
    check("report", std::string("Ayse(5) Can(3) Ali(2)"), t.report());
    check("report does not treat anybody", 3, t.waiting());
    std::string n;
    t.peek(n);
    check("still Ayse next", std::string("Ayse"), n);
}
