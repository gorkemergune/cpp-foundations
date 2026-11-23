// ============================================================================
//  Lab 10 · Reading lines: getline and istringstream              DO NOT EDIT
// ============================================================================
#pragma once

#include <istream>
#include <string>
#include <vector>

// L10-A · Warm-up · the words of a line (separated by any amount of spaces).
std::vector<std::string> splitWords(const std::string& line);

// L10-B · Warm-up · sum of the integers on a line ("" -> 0).
int sumLine(const std::string& line);

// L10-M1 · Main (midterm topic) · smallest integer on a line of space-separated
// integers. No integer on the line: return false and leave out unchanged.
bool minToken(const std::string& line, int& out);

// L10-M2 · Main · the stream holds a count n on its first line, then n lines of text.
// Return the number of words on each of those n lines.
std::vector<int> wordsPerLine(std::istream& in);

// L10-X · Optional · LeetCode 2042: are the numbers in the sentence strictly increasing?
bool areNumbersAscending(const std::string& s);

// L10-V · Optional · memory variant: largest integer and the index (0-based token
// position) of its first occurrence. No integer: false, outputs unchanged.
bool maxToken(const std::string& line, int& out, int& index);
