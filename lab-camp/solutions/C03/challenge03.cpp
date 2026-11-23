// ============================================================================
//  Challenge Set 03 · strings · YOU WORK HERE
//  Reference solution. @solution-note
//  Test:  .\run.ps1 C03        one problem:  .\run.ps1 C03 C03-C
// ============================================================================
#include "challenge03.h"

#include <climits>

#include "todo.h"

using namespace std;

// C03-A · Example: "abcabcbb"  =>  3 ("abc")
// @begin lengthOfLongestSubstring
int lengthOfLongestSubstring(const string& s) {
    int last[256];                         // last index where each byte value was seen
    for (int& x : last) x = -1;
    int best = 0, left = 0;                // window s[left..i] has no repeats
    for (int i = 0; i < (int)s.size(); i++) {
        unsigned char c = s[i];
        if (last[c] >= left) left = last[c] + 1;   // c is inside the window: jump past it
        last[c] = i;
        if (i - left + 1 > best) best = i - left + 1;
    }
    return best;
}
// @end lengthOfLongestSubstring

// C03-B · Example: "babad"  =>  "bab"
// @begin longestPalindrome
string longestPalindrome(const string& s) {
    int n = s.size(), bestStart = 0, bestLen = n ? 1 : 0;
    for (int center = 0; center < n; center++) {
        for (int odd = 1; odd >= 0; odd--) {          // "aba" (odd) and "abba" (even)
            int lo = center, hi = center + 1 - odd;
            while (lo >= 0 && hi < n && s[lo] == s[hi]) { lo--; hi++; }
            int len = hi - lo - 1;                    // the last successful expansion
            if (len > bestLen) { bestLen = len; bestStart = lo + 1; }
        }
    }
    return s.substr(bestStart, bestLen);
}
// @end longestPalindrome

// C03-C · Example: "   -042"  =>  -42;  "91283472332"  =>  2147483647
// @begin myAtoi
int myAtoi(const string& s) {
    size_t i = 0;
    while (i < s.size() && s[i] == ' ') i++;          // 1) leading spaces
    int sign = 1;
    if (i < s.size() && (s[i] == '+' || s[i] == '-')) // 2) one optional sign
        sign = (s[i++] == '-') ? -1 : 1;
    long long value = 0;                              // 3) digits, stop at anything else
    while (i < s.size() && s[i] >= '0' && s[i] <= '9') {
        value = value * 10 + (s[i++] - '0');
        if (value * sign > INT_MAX) return INT_MAX;   // 4) clamp as soon as it overflows
        if (value * sign < INT_MIN) return INT_MIN;
    }
    return (int)(value * sign);
}
// @end myAtoi
