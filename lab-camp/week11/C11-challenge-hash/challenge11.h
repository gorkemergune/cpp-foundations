// ============================================================================
//  Challenge Set 11 · hashing (medium)                               DO NOT EDIT
// ============================================================================
#pragma once

#include <string>
#include <vector>

// C11-A · LeetCode 49: group the words that are anagrams of each other.
// Any order of the groups and of the words inside a group is accepted.
std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string>& words);

// C11-B · LeetCode 128: the length of the longest run of consecutive integers
// (in any order in the input). O(n) — no sorting.
int longestConsecutive(const std::vector<int>& nums);

// C11-C · LeetCode 560: the number of contiguous subarrays whose sum is k
// (values may be negative).
int subarraySum(const std::vector<int>& nums, int k);
