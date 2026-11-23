// ============================================================================
//  Lab 09 · std::string: indexing, find, substr                    DO NOT EDIT
// ============================================================================
#pragma once

#include <string>
#include <vector>

// L09-A · Warm-up · s written backwards.
std::string reversed(const std::string& s);

// L09-B · Warm-up · how many times c occurs in s.
int countChar(const std::string& s, char c);

// L09-M1 · Main (midterm topic) · true if b is a read backwards (case-sensitive).
bool areReverses(const std::string& a, const std::string& b);

// L09-M2 · Main · LeetCode 125: palindrome after keeping only letters and digits and
// ignoring upper/lower case.
bool isPalindromeAlnum(const std::string& s);

// L09-X · Optional · LeetCode 344: reverse the characters in place.
void reverseString(std::vector<char>& s);

// L09-V · Optional · memory variant: non-overlapping occurrences of word in text
// (use find and npos). An empty word -> 0.
int countWord(const std::string& text, const std::string& word);
