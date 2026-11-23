// ============================================================================
//  Lab 42 · The library's hash tables: unordered_map and unordered_set  DO NOT EDIT
//  (and std::map, the library's balanced search tree, when the order matters)
// ============================================================================
#pragma once

#include <string>
#include <utility>
#include <vector>

// L42-A · Warm-up · every word of the text (words are separated by spaces, tabs or new
// lines) with its number of occurrences, sorted by word. Use std::map.
std::vector<std::pair<std::string, int>> wordCount(const std::string& text);

// L42-B · Warm-up · LeetCode 387: index of the first character that occurs once; -1 if none.
int firstUniqChar(const std::string& s);

// L42-M1 · Main · LeetCode 219: are there i != j with nums[i] == nums[j] and |i - j| <= k?
bool containsNearbyDuplicate(const std::vector<int>& nums, int k);

// L42-M2 · Main · LeetCode 242: is t an anagram of s (same characters, same counts)?
bool isAnagram(const std::string& s, const std::string& t);

// L42-M3 · Main · LeetCode 3: the length of the longest substring without a repeated
// character. O(n).
int lengthOfLongestSubstring(const std::string& s);

// L42-X · Optional · LeetCode 205: can the characters of s be replaced (one-to-one) to get t?
bool isIsomorphic(const std::string& s, const std::string& t);

// L42-V · Optional · memory variant: the number of different values.
int countDistinct(const std::vector<int>& v);
