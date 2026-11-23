// Counts how many times the innermost statement of each fragment runs.
#include "check.h"

long long a(int N) { long long c = 0; for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) c++; for (int k = 0; k < N; k++) c++; return c; }
long long b(int N) { long long c = 0; for (int i = 0; i < N; i++) for (int j = N; j > i; j--) c++; return c; }
long long cOuter(int N) { long long c = 0; for (int i = 0; i < N; i++) { c++; for (int j = 1; j > N; j *= 2) c += 1000; } return c; }
long long d(int) { long long c = 0; for (int i = 0; i < 10000; i++) for (int j = 50; j > 1; j--) c++; return c; }

int main() {
    for (int N : {10, 100, 1000}) {
        CHECK_EQ(a(N), (long long)N * N + N);
        CHECK_EQ(b(N), (long long)N * (N + 1) / 2);
        CHECK_EQ(cOuter(N), (long long)N);    // only the outer loop runs: O(N)
        CHECK_EQ(d(N), 490000LL);             // constant
    }
    // Question 2: quadratic algorithm, 4x slower machine, same time -> n = 500
    long long stepsOnC = 1000LL * 1000;
    int n = 0;
    while ((long long)(n + 1) * (n + 1) * 4 <= stepsOnC) n++;
    CHECK_EQ(n, 500);
    return check_summary("2017 as2 algorithm analysis");
}
