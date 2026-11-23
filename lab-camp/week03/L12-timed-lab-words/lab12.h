// ============================================================================
//  Lab 12 · TIMED LAB (50 min) · Word processing                    DO NOT EDIT
// ============================================================================
#pragma once

#include <string>
#include <vector>

// Part A · L12-A · LeetCode 151: words in reverse order, single spaces, no spaces at the ends.
std::string reverseWords(const std::string& s);

// Part B · L12-B · run-length encoding: "aaabcc" -> "a3b1c2"; "" -> "".
std::string compress(const std::string& s);

// Part C · L12-C · (midterm variant) smallest and largest integer on a line of
// space-separated integers. No integer: false, outputs unchanged.
bool minMaxTokens(const std::string& line, int& mn, int& mx);

// L12-X · Optional · LeetCode 14: longest common prefix of all strings ("" if none).
std::string longestCommonPrefix(const std::vector<std::string>& strs);

// L12-V · Optional · memory variant: is b a rotation of a? ("abcde", "cdeab" -> true)
bool isRotationString(const std::string& a, const std::string& b);
