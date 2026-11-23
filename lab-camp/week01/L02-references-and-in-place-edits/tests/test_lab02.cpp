// Lab 02 tests. The table rows of the PDF (pdf_cases.inc) + RANDOM_CASES random inputs.
// Random inputs are compared with the standard library (erase/insert/find), which this
// lab does not allow in your solution.
#include <algorithm>

#include "lab02.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_ADD_Case { V v; int d; V after; };
struct PDF_INDEX_Case { V v; int x; int ret; };
struct PDF_REMOVE_Case { V v; int index; bool ret; V after; };
struct PDF_INSERT_Case { V v; int index; int value; bool ret; V after; };
struct PDF_REMOVE_ELEM_Case { V nums; int val; int k; V prefix; };
struct PDF_MOVE_Case { V v; int index; bool ret; V after; };
#include "pdf_cases.inc"

static std::string S(const V& v) { return show(v); }
static std::string I(int x) { return std::to_string(x); }

QUESTION("L02-A", "addToEach (int&)", "addToEach(") {
    for (auto c : PDF_ADD) {
        std::string d = "v=" + S(c.v) + ", d=" + I(c.d);
        addToEach(c.v, c.d);
        check(d + " (caller's vector)", c.after, c.v);
    }
    for (int i = 0; i < RANDOM_CASES; i++) {
        V v = randVec(15, -20, 20), ref = v;
        int d = randInt(-5, 5);
        for (int& x : ref) x += d;
        std::string desc = "v=" + S(v) + ", d=" + I(d);
        addToEach(v, d);
        check(desc, ref, v);
    }
}

QUESTION("L02-B", "indexOf (const&)", "indexOf(") {
    for (auto& c : PDF_INDEX) check("v=" + S(c.v) + ", x=" + I(c.x), c.ret, indexOf(c.v, c.x));
    for (int i = 0; i < RANDOM_CASES; i++) {
        V v = randVec(12, 0, 6);
        int x = randInt(0, 7);
        auto it = std::find(v.begin(), v.end(), x);
        check("v=" + S(v) + ", x=" + I(x), it == v.end() ? -1 : (int)(it - v.begin()), indexOf(v, x));
    }
}

QUESTION("L02-M1", "removeAt", "removeAt(") {
    auto run = [](V v, int index, bool ret, const V& after) {
        std::string d = "v=" + S(v) + ", index=" + I(index);
        bool got = removeAt(v, index);
        check(d + " (return)", ret, got);
        check(d + " (v after the call)", after, v);
    };
    for (auto& c : PDF_REMOVE) run(c.v, c.index, c.ret, c.after);
    for (int i = 0; i < RANDOM_CASES; i++) {
        V v = randVec(10, 0, 9), ref = v;
        int index = randInt(-2, (int)v.size() + 1);
        bool ok = index >= 0 && index < (int)v.size();
        if (ok) ref.erase(ref.begin() + index);
        run(v, index, ok, ref);
    }
}

QUESTION("L02-M2", "insertAt", "insertAt(") {
    auto run = [](V v, int index, int value, bool ret, const V& after) {
        std::string d = "v=" + S(v) + ", index=" + I(index) + ", value=" + I(value);
        bool got = insertAt(v, index, value);
        check(d + " (return)", ret, got);
        check(d + " (v after the call)", after, v);
    };
    for (auto& c : PDF_INSERT) run(c.v, c.index, c.value, c.ret, c.after);
    for (int i = 0; i < RANDOM_CASES; i++) {
        V v = randVec(10, 0, 9), ref = v;
        int index = randInt(-2, (int)v.size() + 2), value = randInt(0, 9);
        bool ok = index >= 0 && index <= (int)v.size();
        if (ok) ref.insert(ref.begin() + index, value);
        run(v, index, value, ok, ref);
    }
}

OPTIONAL_QUESTION("L02-X", "removeElement (LC 27)", "removeElement(") {
    auto run = [](V nums, int val, int k, const V& prefix) {
        std::string d = "nums=" + S(nums) + ", val=" + I(val);
        int got = removeElement(nums, val);
        check(d + " (k)", k, got);
        if (got == k && k <= (int)nums.size()) check(d + " (first k elements)", prefix, V(nums.begin(), nums.begin() + k));
    };
    for (auto& c : PDF_REMOVE_ELEM) run(c.nums, c.val, c.k, c.prefix);
    for (int i = 0; i < RANDOM_CASES; i++) {
        V v = randVec(12, 0, 4), ref;
        int val = randInt(0, 4);
        std::copy_if(v.begin(), v.end(), std::back_inserter(ref), [&](int x) { return x != val; });
        run(v, val, (int)ref.size(), ref);
    }
}

OPTIONAL_QUESTION("L02-V", "moveToFront", "moveToFront(") {
    auto run = [](V v, int index, bool ret, const V& after) {
        std::string d = "v=" + S(v) + ", index=" + I(index);
        bool got = moveToFront(v, index);
        check(d + " (return)", ret, got);
        check(d + " (v after the call)", after, v);
    };
    for (auto& c : PDF_MOVE) run(c.v, c.index, c.ret, c.after);
    for (int i = 0; i < RANDOM_CASES; i++) {
        V v = randVec(10, 0, 9), ref = v;
        int index = randInt(-1, (int)v.size());
        bool ok = index >= 0 && index < (int)v.size();
        if (ok) std::rotate(ref.begin(), ref.begin() + index, ref.begin() + index + 1);
        run(v, index, ok, ref);
    }
}
