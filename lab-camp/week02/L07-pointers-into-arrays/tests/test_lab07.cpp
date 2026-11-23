// Lab 07 tests. PDF rows + random inputs.
#include <algorithm>

#include "lab07.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;
using M = std::vector<std::vector<int>>;

struct PDF_FIND_Case { V a; int x; int index; };
struct PDF_DIAG_Case { M m; int ret; };
struct PDF_TRANS_Case { M m; M after; };
struct PDF_TX_Case { M m; M t; };
struct PDF_RANGE_Case { V a; int lo; int hi; int ret; };
#include "pdf_cases.inc"

static void load(int m[][MAXN], const M& src) {
    for (int i = 0; i < MAXN; i++)
        for (int j = 0; j < MAXN; j++) m[i][j] = -99;     // guard values outside n x n
    for (size_t i = 0; i < src.size(); i++)
        for (size_t j = 0; j < src[i].size(); j++) m[i][j] = src[i][j];
}
static M part(int m[][MAXN], int n) {
    M r(n, V(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) r[i][j] = m[i][j];
    return r;
}
static M randSquare(int n) {
    M m(n, V(n));
    for (auto& row : m)
        for (int& x : row) x = randInt(-9, 9);
    return m;
}

QUESTION("L07-A", "findFirst (pointer range)", "findFirst(") {
    for (auto& c : PDF_FIND) {
        const int* b = c.a.data();
        const int* got = findFirst(b, b + c.a.size(), c.x);
        check("a=" + show(c.a) + ", x=" + std::to_string(c.x) + " (index of the returned pointer)", c.index, (int)(got - b));
    }
    for (int i = 0; i < RANDOM_CASES; i++) {
        V v = randVec(12, 0, 5);
        int x = randInt(0, 6);
        const int* got = findFirst(v.data(), v.data() + v.size(), x);
        check("a=" + show(v) + ", x=" + std::to_string(x), (int)(std::find(v.begin(), v.end(), x) - v.begin()),
              (int)(got - v.data()));
    }
}

QUESTION("L07-B", "swapViaPointers", "swapViaPointers(") {
    int a = 3, b = 8;
    swapViaPointers(&a, &b);
    check("a=3, b=8 (a after)", 8, a);
    check("a=3, b=8 (b after)", 3, b);
    swapViaPointers(&a, &a);
    check("same pointer twice", 8, a);
    swapViaPointers(&a, nullptr);
    check("y == nullptr: a unchanged", 8, a);
    int arr[3] = {1, 2, 3};
    swapViaPointers(arr, arr + 2);
    check("swapViaPointers(arr, arr + 2) on {1, 2, 3}", V{3, 2, 1}, V(arr, arr + 3));
}

QUESTION("L07-M1", "diagonalSum (LC 1572)", "diagonalSum(") {
    int m[MAXN][MAXN];
    for (auto& c : PDF_DIAG) {
        load(m, c.m);
        check("m=" + show(c.m), c.ret, diagonalSum(m, (int)c.m.size()));
    }
    for (int i = 0; i < RANDOM_CASES; i++) {
        int n = randInt(1, MAXN);
        M src = randSquare(n);
        int want = 0;
        for (int k = 0; k < n; k++) want += src[k][k] + (k != n - 1 - k ? src[k][n - 1 - k] : 0);
        load(m, src);
        check("random " + std::to_string(n) + "x" + std::to_string(n), want, diagonalSum(m, n));
    }
}

QUESTION("L07-M2", "transposeSquare", "transposeSquare(") {
    int m[MAXN][MAXN];
    for (auto& c : PDF_TRANS) {
        load(m, c.m);
        int n = (int)c.m.size();
        transposeSquare(m, n);
        check("m=" + show(c.m), c.after, part(m, n));
        checkTrue("m=" + show(c.m) + " (cells outside n x n)", n == MAXN || m[0][n] == -99, "wrote outside the n x n part");
    }
    for (int i = 0; i < RANDOM_CASES; i++) {
        int n = randInt(1, MAXN);
        M src = randSquare(n), want(n, V(n));
        for (int r = 0; r < n; r++)
            for (int c = 0; c < n; c++) want[c][r] = src[r][c];
        load(m, src);
        transposeSquare(m, n);
        check("random " + std::to_string(n) + "x" + std::to_string(n), want, part(m, n));
    }
}

OPTIONAL_QUESTION("L07-X", "transpose (LC 867)", "transpose(") {
    for (auto& c : PDF_TX) check("matrix=" + show(c.m), c.t, transpose(c.m));
}

OPTIONAL_QUESTION("L07-V", "countInRange", "countInRange(") {
    for (auto& c : PDF_RANGE)
        check("a=" + show(c.a) + ", lo=" + std::to_string(c.lo) + ", hi=" + std::to_string(c.hi), c.ret,
              countInRange(c.a.data(), c.a.data() + c.a.size(), c.lo, c.hi));
}
