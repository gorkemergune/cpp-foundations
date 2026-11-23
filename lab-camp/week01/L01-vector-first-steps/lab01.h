// ============================================================================
//  Lab 01 · First steps with std::vector                      DO NOT EDIT
//  The declarations of the functions you write in lab01.cpp.
//  A header uses std:: in front of names; lab01.cpp may say
//  "using namespace std;" instead.
// ============================================================================
#pragma once

#include <vector>

// L01-A · Warm-up · sum of all elements. Empty vector -> 0.
int sumAll(std::vector<int> v);

// L01-B · Warm-up · the even elements, in their original order.
std::vector<int> evensOnly(std::vector<int> v);

// L01-M · Main problem · result[i] = changes[0] + ... + changes[i].
std::vector<int> runningTotals(std::vector<int> changes);

// L01-X · Optional · LeetCode 1929: nums followed by nums again.
std::vector<int> getConcatenation(std::vector<int> nums);

// L01-V · Optional · memory variant: result[i] = max(v[0], ..., v[i]).
std::vector<int> runningMax(std::vector<int> v);
