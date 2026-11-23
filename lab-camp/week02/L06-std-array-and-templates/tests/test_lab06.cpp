// Lab 06 tests. PDF rows + random inputs. The templates are also tested with other types.
#include <algorithm>
#include <cmath>
#include <string>

#include "lab06.h"
#include "lab06_templates.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_MAXOF_Case { V v; int ret; };
struct PDF_POS_Case { V a; int ret; };
struct PDF_WEEK_Case { V t; int mn; int mx; int avgTimes7; int warm; };
struct PDF_ODDS_Case { V arr; bool ret; };
struct PDF_REV_Case { V a; V after; };
#include "pdf_cases.inc"

QUESTION("L06-A", "maxOf<T>", "maxOf(") {
    for (auto& c : PDF_MAXOF) check("v=" + show(c.v), c.ret, maxOf(c.v));
    check("v={\"pear\", \"apple\", \"plum\"} (T = std::string)", std::string("plum"),
          maxOf(std::vector<std::string>{"pear", "apple", "plum"}));
    checkTrue("v={2.5, -1.0, 2.75} (T = double)", maxOf(std::vector<double>{2.5, -1.0, 2.75}) == 2.75, "expected 2.75");
    for (int i = 0; i < RANDOM_CASES; i++) {
        V v = randVec(15, -50, 50, 1);
        check("v=" + show(v), *std::max_element(v.begin(), v.end()), maxOf(v));
    }
}

QUESTION("L06-B", "countPositive<N>", "countPositive(") {
    for (auto& c : PDF_POS) {
        std::array<int, 5> a{};
        std::copy(c.a.begin(), c.a.end(), a.begin());
        check("a=" + show(c.a), c.ret, countPositive(a));
    }
    check("std::array<int, 1>{0}", 0, countPositive(std::array<int, 1>{0}));
    check("std::array<int, 3>{1, 2, 3}", 3, countPositive(std::array<int, 3>{1, 2, 3}));
}

QUESTION("L06-M", "weekStats", "weekStats(") {
    auto run = [](const V& v, int mn, int mx, double avg, int warm) {
        std::array<int, 7> t;
        std::copy(v.begin(), v.end(), t.begin());
        WeekStats s = weekStats(t);
        std::string d = "t=" + show(v);
        check(d + " (minTemp)", mn, s.minTemp);
        check(d + " (maxTemp)", mx, s.maxTemp);
        checkTrue(d + " (average)", std::fabs(s.average - avg) < 1e-9, "expected " + std::to_string(avg) + ", got " + std::to_string(s.average));
        check(d + " (warmestDay)", warm, s.warmestDay);
    };
    for (auto& c : PDF_WEEK) run(c.t, c.mn, c.mx, c.avgTimes7 / 7.0, c.warm);
    for (int i = 0; i < RANDOM_CASES; i++) {
        V v = randVec(7, -10, 35, 7);
        int sum = 0;
        for (int x : v) sum += x;
        run(v, *std::min_element(v.begin(), v.end()), *std::max_element(v.begin(), v.end()), sum / 7.0,
            (int)(std::max_element(v.begin(), v.end()) - v.begin()));
    }
}

OPTIONAL_QUESTION("L06-X", "threeConsecutiveOdds (LC 1550)", "threeConsecutiveOdds(") {
    for (auto& c : PDF_ODDS) check("arr=" + show(c.arr), c.ret, threeConsecutiveOdds(c.arr));
}

OPTIONAL_QUESTION("L06-V", "reverseArray<T, N>", "reverseArray(") {
    for (auto& c : PDF_REV) {
        std::array<int, 4> a;
        std::copy(c.a.begin(), c.a.end(), a.begin());
        reverseArray(a);
        check("a=" + show(c.a), c.after, V(a.begin(), a.end()));
    }
    std::array<std::string, 3> s = {"x", "y", "z"};
    reverseArray(s);
    check("std::array<std::string, 3>{x, y, z}", std::string("zyx"), s[0] + s[1] + s[2]);
    std::array<int, 1> one = {7};
    reverseArray(one);
    check("std::array<int, 1>{7}", 7, one[0]);
}
