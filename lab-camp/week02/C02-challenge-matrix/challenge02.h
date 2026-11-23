// ============================================================================
//  Challenge Set 02 · 2-D arrays / matrices (medium)                DO NOT EDIT
// ============================================================================
#pragma once

#include <vector>

using Matrix = std::vector<std::vector<int>>;

// C02-A · LeetCode 54: the elements in clockwise spiral order.
std::vector<int> spiralOrder(const Matrix& m);

// C02-B · LeetCode 48 (called rotate there): rotate an n x n matrix 90 degrees clockwise IN PLACE.
void rotateImage(Matrix& m);

// C02-C · LeetCode 73: if a cell is 0, set its whole row and column to 0. O(1) extra memory.
void setZeroes(Matrix& m);
