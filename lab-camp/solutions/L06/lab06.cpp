// ============================================================================
//  Lab 06 · std::array · YOU WORK HERE
//  Reference solution. @solution-note
//  Test one question:    .\run.ps1 L06 L06-M
//  Allowed: t.size(), t[i], t.at(i), range-for. Not allowed: <algorithm>, <numeric>.
// ============================================================================
#include "lab06.h"

#include "todo.h"

using namespace std;

// L06-M · min, max, average (as a double) and the first index of the max.
// Example: {20, 23, 19, 23, 18, 21, 22}  =>  {18, 23, 20.857..., 1}
// @begin weekStats
WeekStats weekStats(const array<int, 7>& t) {
    WeekStats s{t[0], t[0], 0.0, 0};          // a week always has 7 days: t[0] exists
    int sum = 0;
    for (size_t i = 0; i < t.size(); i++) {
        sum += t[i];
        if (t[i] < s.minTemp) s.minTemp = t[i];
        if (t[i] > s.maxTemp) {
            s.maxTemp = t[i];
            s.warmestDay = (int)i;
        }
    }
    s.average = sum / 7.0;                    // 7.0 makes it a floating-point division
    return s;
}
// @end weekStats

// L06-X · LeetCode 1550.   Example: {1, 2, 34, 3, 4, 5, 7, 23, 12}  =>  true (5, 7, 23)
// @begin threeConsecutiveOdds
bool threeConsecutiveOdds(const vector<int>& arr) {
    int run = 0;                              // length of the current odd streak
    for (int x : arr) {
        run = (x % 2 != 0) ? run + 1 : 0;     // != 0 works for negative odds too
        if (run == 3) return true;
    }
    return false;
}
// @end threeConsecutiveOdds
