// ============================================================================
//  Lab 04 · TIMED LAB (50 min) · Compacting and rotating a vector  DO NOT EDIT
// ============================================================================
#pragma once

#include <vector>

// Part A · LeetCode 283: move all 0s to the end, keep the order of the others.
void moveZeroes(std::vector<int>& nums);

// Part B · return a NEW vector: v rotated LEFT by k. v is not changed. k >= 0.
std::vector<int> rotatedCopy(const std::vector<int>& v, int k);

// Part C · rotate v LEFT by k in place, O(1) extra memory. k >= 0.
void rotateLeft(std::vector<int>& v, int k);

// L04-X · Optional · LeetCode 189 (there it is called rotate): rotate RIGHT by k.
void rotateRight(std::vector<int>& nums, int k);

// L04-V · Optional · memory variant: true if b is a rotation of a.
bool isRotation(const std::vector<int>& a, const std::vector<int>& b);
