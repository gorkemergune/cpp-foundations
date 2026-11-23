// ============================================================================
//  Challenge Set 11 · hashing · YOU WORK HERE
//  Reference solution. @solution-note
//  Test:  .\run.ps1 C11        one problem:  .\run.ps1 C11 C11-B
// ============================================================================
#include "challenge11.h"

#include <algorithm>
#include <unordered_map>
#include <unordered_set>

#include "todo.h"

using namespace std;

// C11-A · Example: {"eat","tea","tan","ate","nat","bat"}  =>  {eat tea ate} {tan nat} {bat}
// @begin groupAnagrams
vector<vector<string>> groupAnagrams(const vector<string>& words) {
    unordered_map<string, int> groupOf;     // sorted letters -> index of its group
    vector<vector<string>> groups;
    for (const string& w : words) {
        string key = w;
        sort(key.begin(), key.end());       // every anagram has the same sorted form
        auto it = groupOf.find(key);
        if (it == groupOf.end()) {
            groupOf[key] = groups.size();
            groups.push_back({w});
        } else {
            groups[it->second].push_back(w);
        }
    }
    return groups;
}
// @end groupAnagrams

// C11-B · Example: {100, 4, 200, 1, 3, 2}  =>  4 (1 2 3 4)
// @begin longestConsecutive
int longestConsecutive(const vector<int>& nums) {
    unordered_set<int> have(nums.begin(), nums.end());
    int best = 0;
    for (int x : have) {
        if (have.count(x - 1)) continue;    // x is not the start of a run
        int len = 1;
        while (have.count(x + len)) len++;  // every run is walked once, from its start
        best = max(best, len);
    }
    return best;
}
// @end longestConsecutive

// C11-C · Example: {1, 2, 3}, k = 3  =>  2 ({1,2} and {3})
// @begin subarraySum
int subarraySum(const vector<int>& nums, int k) {
    unordered_map<long long, int> seen;     // prefix sum -> how many times it occurred
    seen[0] = 1;                            // the empty prefix
    long long sum = 0;
    int count = 0;
    for (int x : nums) {
        sum += x;
        auto it = seen.find(sum - k);       // an earlier prefix p with sum - p == k
        if (it != seen.end()) count += it->second;
        seen[sum]++;
    }
    return count;
}
// @end subarraySum
