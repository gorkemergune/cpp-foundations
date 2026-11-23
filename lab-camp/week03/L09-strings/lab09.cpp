// ============================================================================
//  Lab 09 · std::string · YOU WORK HERE
//  Test everything:      .\run.ps1 L09
//  Allowed: s.size(), s[i], +=, s.find, s.substr, <cctype>. Not allowed: std::reverse.
// ============================================================================
#include "lab09.h"

#include <cctype>

#include "todo.h"

using namespace std;

// L09-A · Example: "abc"  =>  "cba"
string reversed(const string& s) {
    TODO();
}

// L09-B · Example: "banana", 'a'  =>  3
int countChar(const string& s, char c) {
    TODO();
}

// L09-M1 · Example: "stack", "kcats"  =>  true;  "abc", "abc"  =>  false
bool areReverses(const string& a, const string& b) {
    TODO();
}

// L09-M2 · Example: "A man, a plan, a canal: Panama"  =>  true
bool isPalindromeAlnum(const string& s) {
    TODO();
}

// L09-X · Example: {'h','e','l','l','o'}  =>  {'o','l','l','e','h'}
void reverseString(vector<char>& s) {
    TODO();
}

// L09-V · Example: "the cat and the hat", "the"  =>  2;  "aaaa", "aa"  =>  2
int countWord(const string& text, const string& word) {
    TODO();
}
