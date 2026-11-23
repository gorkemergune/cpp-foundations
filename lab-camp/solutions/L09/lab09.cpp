// ============================================================================
//  Lab 09 · std::string · YOU WORK HERE
//  Reference solution. @solution-note
//  Test everything:      .\run.ps1 L09
//  Allowed: s.size(), s[i], +=, s.find, s.substr, <cctype>. Not allowed: std::reverse.
// ============================================================================
#include "lab09.h"

#include <cctype>

#include "todo.h"

using namespace std;

// L09-A · Example: "abc"  =>  "cba"
// @begin reversed
string reversed(const string& s) {
    string r;
    for (int i = (int)s.size() - 1; i >= 0; i--) r += s[i];   // int: i must reach -1
    return r;
}
// @end reversed

// L09-B · Example: "banana", 'a'  =>  3
// @begin countChar
int countChar(const string& s, char c) {
    int n = 0;
    for (char x : s)
        if (x == c) n++;
    return n;
}
// @end countChar

// L09-M1 · Example: "stack", "kcats"  =>  true;  "abc", "abc"  =>  false
// @begin areReverses
bool areReverses(const string& a, const string& b) {
    if (a.size() != b.size()) return false;
    int n = a.size();
    for (int i = 0; i < n; i++)
        if (a[i] != b[n - 1 - i]) return false;
    return true;
}
// @end areReverses

// L09-M2 · Example: "A man, a plan, a canal: Panama"  =>  true
// @begin isPalindromeAlnum
bool isPalindromeAlnum(const string& s) {
    int lo = 0, hi = (int)s.size() - 1;
    while (lo < hi) {
        // isalnum/tolower expect an unsigned char value: a plain char may be negative
        if (!isalnum((unsigned char)s[lo])) { lo++; continue; }
        if (!isalnum((unsigned char)s[hi])) { hi--; continue; }
        if (tolower((unsigned char)s[lo]) != tolower((unsigned char)s[hi])) return false;
        lo++;
        hi--;
    }
    return true;
}
// @end isPalindromeAlnum

// L09-X · Example: {'h','e','l','l','o'}  =>  {'o','l','l','e','h'}
// @begin reverseString
void reverseString(vector<char>& s) {
    for (int lo = 0, hi = (int)s.size() - 1; lo < hi; lo++, hi--) {
        char t = s[lo];
        s[lo] = s[hi];
        s[hi] = t;
    }
}
// @end reverseString

// L09-V · Example: "the cat and the hat", "the"  =>  2;  "aaaa", "aa"  =>  2
// @begin countWord
int countWord(const string& text, const string& word) {
    if (word.empty()) return 0;
    int n = 0;
    size_t pos = text.find(word);              // npos = "not found"
    while (pos != string::npos) {
        n++;
        pos = text.find(word, pos + word.size());   // continue AFTER this match
    }
    return n;
}
// @end countWord
