// ============================================================================
//  Lab 12 · TIMED LAB (50 min) · YOU WORK HERE
//  Reference solution. @solution-note
//  Start a timer. Test:  .\run.ps1 L12      one part:  .\run.ps1 L12 L12-B
//  Allowed: std::string members, std::istringstream, std::to_string.
//  Not allowed: <algorithm> (std::reverse, std::min_element ...).
// ============================================================================
#include "lab12.h"

#include <sstream>

#include "todo.h"

using namespace std;

// Part A · Example: "  the sky  is blue "  =>  "blue is sky the"
// @begin reverseWords
string reverseWords(const string& s) {
    istringstream in(s);
    vector<string> words;
    string w;
    while (in >> w) words.push_back(w);           // >> already drops all extra spaces
    string out;
    for (int i = (int)words.size() - 1; i >= 0; i--) {
        out += words[i];
        if (i > 0) out += ' ';                    // a space BETWEEN words only
    }
    return out;
}
// @end reverseWords

// Part B · Example: "aaabcc"  =>  "a3b1c2"
// @begin compress
string compress(const string& s) {
    string out;
    int n = s.size();
    for (int i = 0; i < n;) {
        int j = i;
        while (j < n && s[j] == s[i]) j++;        // s[i..j-1] is one run
        out += s[i];
        out += to_string(j - i);                  // the count may have several digits
        i = j;
    }
    return out;
}
// @end compress

// Part C · Example: "7 -2 9 3"  =>  true, mn = -2, mx = 9
// @begin minMaxTokens
bool minMaxTokens(const string& line, int& mn, int& mx) {
    istringstream in(line);
    int lo, hi, x;
    if (!(in >> lo)) return false;
    hi = lo;
    while (in >> x) {
        if (x < lo) lo = x;
        if (x > hi) hi = x;
    }
    mn = lo;
    mx = hi;
    return true;
}
// @end minMaxTokens

// L12-X · Example: {"flower", "flow", "flight"}  =>  "fl"
// @begin longestCommonPrefix
string longestCommonPrefix(const vector<string>& strs) {
    if (strs.empty()) return "";
    string prefix = strs[0];
    for (const string& s : strs) {
        size_t k = 0;
        while (k < prefix.size() && k < s.size() && prefix[k] == s[k]) k++;
        prefix = prefix.substr(0, k);             // shrink to what still matches
    }
    return prefix;
}
// @end longestCommonPrefix

// L12-V · Example: "abcde", "cdeab"  =>  true
// @begin isRotationString
bool isRotationString(const string& a, const string& b) {
    return a.size() == b.size() && (a + a).find(b) != string::npos;
}
// @end isRotationString
