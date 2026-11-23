// Challenge 07 tests.
#include <algorithm>
#include <deque>

#include "challenge07.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_SEN_Case { std::string senate; std::string winner; };
struct PDF_WIN_Case { V nums; int k; V out; };
#include "pdf_cases.inc"

static std::string slowSenate(std::string s) {       // literal simulation of the rules
    while (true) {
        bool r = s.find('R') != std::string::npos, d = s.find('D') != std::string::npos;
        if (!r) return "Dire";
        if (!d) return "Radiant";
        std::string banned(s.size(), '0');
        for (size_t i = 0; i < s.size(); i++) {
            if (banned[i] == '1') continue;
            char enemy = s[i] == 'R' ? 'D' : 'R';
            for (size_t j = 1; j <= s.size(); j++) {          // first active enemy after i (cyclic)
                size_t t = (i + j) % s.size();
                if (s[t] == enemy && banned[t] == '0') { banned[t] = '1'; break; }
            }
        }
        std::string next;
        for (size_t i = 0; i < s.size(); i++)
            if (banned[i] == '0') next += s[i];
        s = next;
    }
}

QUESTION("C07-A", "predictPartyVictory (LC 649)", "predictPartyVictory(") {
    for (auto& c : PDF_SEN) check("senate=" + show(c.senate), c.winner, predictPartyVictory(c.senate));
    for (int t = 0; t < RANDOM_CASES; t++) {
        std::string s;
        int n = randInt(1, 10);
        for (int i = 0; i < n; i++) s += "RD"[randInt(0, 1)];
        check("senate=" + show(s), slowSenate(s), predictPartyVictory(s));
    }
}

QUESTION("C07-B", "MyCircularDeque (LC 641)", "MyCircularDeque::") {
    MyCircularDeque d(3);
    check("insertLast(1)", true, d.insertLast(1));
    check("insertLast(2)", true, d.insertLast(2));
    check("insertFront(3)", true, d.insertFront(3));
    check("insertFront(4) on a full deque", false, d.insertFront(4));
    check("getRear", 2, d.getRear());
    check("isFull", true, d.isFull());
    check("deleteLast", true, d.deleteLast());
    check("insertFront(4)", true, d.insertFront(4));
    check("getFront", 4, d.getFront());
    for (int t = 0; t < RANDOM_CASES; t++) {
        int k = randInt(1, 4);
        MyCircularDeque m(k);
        std::deque<int> ref;
        bool ok = true;
        for (int s = 0; s < 30 && ok; s++) {
            int op = randInt(0, 3), x = randInt(0, 9);
            bool full = (int)ref.size() == k, empty = ref.empty();
            if (op == 0) { ok = m.insertFront(x) == !full; if (!full) ref.push_front(x); }
            if (op == 1) { ok = m.insertLast(x) == !full; if (!full) ref.push_back(x); }
            if (op == 2) { ok = m.deleteFront() == !empty; if (!empty) ref.pop_front(); }
            if (op == 3) { ok = m.deleteLast() == !empty; if (!empty) ref.pop_back(); }
            ok = ok && m.getFront() == (ref.empty() ? -1 : ref.front()) && m.getRear() == (ref.empty() ? -1 : ref.back());
        }
        checkTrue("random operations, capacity " + std::to_string(k), ok, "wrong result or wrap-around");
    }
}

QUESTION("C07-C", "maxSlidingWindow (LC 239)", "maxSlidingWindow(") {
    for (auto& c : PDF_WIN) check("nums=" + show(c.nums) + ", k=" + std::to_string(c.k), c.out, maxSlidingWindow(c.nums, c.k));
    for (int t = 0; t < RANDOM_CASES; t++) {
        V v = randVec(15, -9, 9, 1), w;
        int k = randInt(1, (int)v.size());
        for (size_t i = 0; i + k <= v.size(); i++) w.push_back(*std::max_element(v.begin() + i, v.begin() + i + k));
        check("nums=" + show(v) + ", k=" + std::to_string(k), w, maxSlidingWindow(v, k));
    }
}
