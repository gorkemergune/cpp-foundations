// Challenge 02 tests: PDF rows + random matrices compared with simple versions that use extra memory.
#include "challenge02.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_SPIRAL_Case { Matrix m; V out; };
struct PDF_ROT_Case { Matrix m; Matrix after; };
struct PDF_ZERO_Case { Matrix m; Matrix after; };
#include "pdf_cases.inc"

static Matrix randMatrix(int R, int C, int lo, int hi) {
    Matrix m(R, V(C));
    for (auto& r : m)
        for (int& x : r) x = randInt(lo, hi);
    return m;
}

QUESTION("C02-A", "spiralOrder (LC 54)", "spiralOrder(") {
    for (auto& c : PDF_SPIRAL) check("m=" + show(c.m), c.out, spiralOrder(c.m));
    for (int t = 0; t < RANDOM_CASES; t++) {
        int R = randInt(1, 6), C = randInt(1, 6);
        Matrix m = randMatrix(R, C, 0, 9);
        V want;                                      // simulate with a visited grid
        std::vector<std::vector<bool>> seen(R, std::vector<bool>(C, false));
        int dr[4] = {0, 1, 0, -1}, dc[4] = {1, 0, -1, 0}, r = 0, c = 0, d = 0;
        for (int k = 0; k < R * C; k++) {
            want.push_back(m[r][c]);
            seen[r][c] = true;
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C || seen[nr][nc]) {
                d = (d + 1) % 4;
                nr = r + dr[d];
                nc = c + dc[d];
            }
            r = nr;
            c = nc;
        }
        check("m=" + show(m), want, spiralOrder(m));
    }
}

QUESTION("C02-B", "rotateImage (LC 48)", "rotateImage(") {
    for (auto c : PDF_ROT) {
        std::string d = "m=" + show(c.m);
        rotateImage(c.m);
        check(d, c.after, c.m);
    }
    for (int t = 0; t < RANDOM_CASES; t++) {
        int n = randInt(1, 7);
        Matrix m = randMatrix(n, n, 0, 9), want(n, V(n));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) want[j][n - 1 - i] = m[i][j];
        std::string d = "m=" + show(m);
        rotateImage(m);
        check(d, want, m);
    }
}

QUESTION("C02-C", "setZeroes (LC 73)", "setZeroes(") {
    for (auto c : PDF_ZERO) {
        std::string d = "m=" + show(c.m);
        setZeroes(c.m);
        check(d, c.after, c.m);
    }
    for (int t = 0; t < RANDOM_CASES; t++) {
        int R = randInt(1, 6), C = randInt(1, 6);
        Matrix m = randMatrix(R, C, 0, 4), want = m;
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                if (m[i][j] == 0) {
                    for (int k = 0; k < C; k++) want[i][k] = 0;
                    for (int k = 0; k < R; k++) want[k][j] = 0;
                }
        std::string d = "m=" + show(m);
        setZeroes(m);
        check(d, want, m);
    }
}
