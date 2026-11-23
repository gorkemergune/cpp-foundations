// ============================================================================
//  Challenge Set 01 · vector (medium / hard)                       DO NOT EDIT
// ============================================================================
#pragma once

#include <vector>

// C01-A · LeetCode 238 (medium): result[i] = product of all nums except nums[i].
// No division, O(n) time.
std::vector<int> productExceptSelf(const std::vector<int>& nums);

// C01-B · LeetCode 11 (medium): the most water two lines can hold.
int maxArea(const std::vector<int>& height);

// C01-C · LeetCode 41 (hard): smallest positive integer that is NOT in nums.
// O(n) time, O(1) extra memory: you may reorder nums.
int firstMissingPositive(std::vector<int>& nums);
