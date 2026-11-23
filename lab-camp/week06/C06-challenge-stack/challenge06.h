// ============================================================================
//  Challenge Set 06 · stacks (medium / hard)                        DO NOT EDIT
// ============================================================================
#pragma once

#include <string>
#include <vector>

// C06-A · LeetCode 739 (medium): days to wait for a warmer temperature (0 if never).
std::vector<int> dailyTemperatures(const std::vector<int>& temperatures);

// C06-B · LeetCode 394 (medium): decode k[encoded] (nesting allowed), e.g. "3[a2[c]]" -> "accaccacc".
std::string decodeString(const std::string& s);

// C06-C · LeetCode 84 (hard): area of the largest rectangle in a histogram. O(n).
int largestRectangleArea(const std::vector<int>& heights);
