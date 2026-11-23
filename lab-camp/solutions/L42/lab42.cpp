// ============================================================================
//  Lab 42 · unordered_map / unordered_set · YOU WORK HERE
//  Reference solution. @solution-note
//  Test everything:      .\run.ps1 L42
// ============================================================================
#include "lab42.h"

#include <map>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

#include "todo.h"

using namespace std;

// L42-A · Example: "b a b"  =>  {("a", 1), ("b", 2)}
// @begin wordCount
vector<pair<string, int>> wordCount(const string& text) {
    map<string, int> count;                 // a search tree: iterates in key order
    istringstream in(text);
    string w;
    while (in >> w) count[w]++;             // operator[] creates a 0 the first time
    return vector<pair<string, int>>(count.begin(), count.end());
}
// @end wordCount

// L42-B · Example: "loveleetcode"  =>  2
// @begin firstUniqChar
int firstUniqChar(const string& s) {
    unordered_map<char, int> count;
    for (char c : s) count[c]++;
    for (int i = 0; i < (int)s.size(); i++)
        if (count[s[i]] == 1) return i;     // second pass in the ORIGINAL order
    return -1;
}
// @end firstUniqChar

// L42-M1 · Example: {1, 2, 3, 1}, k = 3  =>  true
// @begin containsNearbyDuplicate
bool containsNearbyDuplicate(const vector<int>& nums, int k) {
    unordered_map<int, int> last;           // value -> the last index it was seen at
    for (int i = 0; i < (int)nums.size(); i++) {
        auto it = last.find(nums[i]);       // find: does not insert, unlike operator[]
        if (it != last.end() && i - it->second <= k) return true;
        last[nums[i]] = i;
    }
    return false;
}
// @end containsNearbyDuplicate

// L42-M2 · Example: "anagram", "nagaram"  =>  true
// @begin isAnagram
bool isAnagram(const string& s, const string& t) {
    if (s.size() != t.size()) return false;
    unordered_map<char, int> diff;
    for (char c : s) diff[c]++;
    for (char c : t)
        if (--diff[c] < 0) return false;    // t uses c more often than s
    return true;                            // same length and nothing negative: all zero
}
// @end isAnagram

// L42-M3 · Example: "abcabcbb"  =>  3 ("abc")
// @begin lengthOfLongestSubstring
int lengthOfLongestSubstring(const string& s) {
    unordered_map<char, int> last;          // character -> its last index
    int best = 0, start = 0;                // the window is s[start .. i]
    for (int i = 0; i < (int)s.size(); i++) {
        auto it = last.find(s[i]);
        if (it != last.end() && it->second >= start) start = it->second + 1;   // jump past it
        last[s[i]] = i;
        if (i - start + 1 > best) best = i - start + 1;
    }
    return best;
}
// @end lengthOfLongestSubstring

// L42-X · Example: "egg", "add"  =>  true;  "foo", "bar"  =>  false
// @begin isIsomorphic
bool isIsomorphic(const string& s, const string& t) {
    if (s.size() != t.size()) return false;
    unordered_map<char, char> to, from;     // both directions: one-to-one
    for (size_t i = 0; i < s.size(); i++) {
        auto a = to.find(s[i]);
        auto b = from.find(t[i]);
        if (a != to.end() && a->second != t[i]) return false;
        if (b != from.end() && b->second != s[i]) return false;
        to[s[i]] = t[i];
        from[t[i]] = s[i];
    }
    return true;
}
// @end isIsomorphic

// L42-V · Example: {3, 1, 3, 2, 1}  =>  3
// @begin countDistinct
int countDistinct(const vector<int>& v) {
    return unordered_set<int>(v.begin(), v.end()).size();
}
// @end countDistinct
