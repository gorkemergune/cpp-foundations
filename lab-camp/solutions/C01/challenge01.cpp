// ============================================================================
//  Challenge Set 01 · vector · YOU WORK HERE
//  Reference solution. @solution-note
//  Test:  .\run.ps1 C01        one problem:  .\run.ps1 C01 C01-C
// ============================================================================
#include "challenge01.h"

#include <utility>

#include "todo.h"

using namespace std;

// C01-A · Example: {1, 2, 3, 4}  =>  {24, 12, 8, 6}
// @begin productExceptSelf
vector<int> productExceptSelf(const vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, 1);
    int left = 1;                          // product of everything left of i
    for (int i = 0; i < n; i++) {
        result[i] = left;
        left *= nums[i];
    }
    int right = 1;                         // product of everything right of i
    for (int i = n - 1; i >= 0; i--) {
        result[i] *= right;
        right *= nums[i];
    }
    return result;
}
// @end productExceptSelf

// C01-B · Example: {1, 8, 6, 2, 5, 4, 8, 3, 7}  =>  49 (lines 1 and 8: min(8, 7) * 7)
// @begin maxArea
int maxArea(const vector<int>& height) {
    int lo = 0, hi = (int)height.size() - 1, best = 0;
    while (lo < hi) {
        int h = height[lo] < height[hi] ? height[lo] : height[hi];
        if (h * (hi - lo) > best) best = h * (hi - lo);
        // the shorter line limits every container that uses it with a closer partner,
        // so it can never be part of a better answer: drop it
        if (height[lo] < height[hi]) lo++;
        else hi--;
    }
    return best;
}
// @end maxArea

// C01-C · Example: {3, 4, -1, 1}  =>  2
// @begin firstMissingPositive
int firstMissingPositive(vector<int>& nums) {
    int n = nums.size();
    // Put every value v in 1..n at index v-1 ("each number goes home").
    for (int i = 0; i < n; i++) {
        while (nums[i] >= 1 && nums[i] <= n && nums[nums[i] - 1] != nums[i])
            swap(nums[i], nums[nums[i] - 1]);   // every swap puts one value home: O(n) in total
    }
    for (int i = 0; i < n; i++)
        if (nums[i] != i + 1) return i + 1;    // first index whose owner is missing
    return n + 1;
}
// @end firstMissingPositive
