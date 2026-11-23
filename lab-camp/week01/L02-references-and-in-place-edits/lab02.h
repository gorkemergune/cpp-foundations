// ============================================================================
//  Lab 02 · References: editing a vector in place               DO NOT EDIT
//  &       : the function works on the caller's vector (no copy)
//  const & : no copy AND the function promises not to change it
// ============================================================================
#pragma once

#include <vector>

// L02-A · Warm-up · add d to every element of the caller's vector.
void addToEach(std::vector<int>& v, int d);

// L02-B · Warm-up · index of the first x, or -1 if x is not in v.
int indexOf(const std::vector<int>& v, int x);

// L02-M1 · Main · remove the element at index; shift the rest left.
// Invalid index (< 0 or >= size): return false and leave v unchanged.
bool removeAt(std::vector<int>& v, int index);

// L02-M2 · Main · insert value so that it ends up at position index.
// Valid indexes are 0..size (size means "append"). Otherwise return false.
bool insertAt(std::vector<int>& v, int index, int value);

// L02-X · Optional · LeetCode 27 Remove Element (this lab: keep the order).
int removeElement(std::vector<int>& nums, int val);

// L02-V · Optional · memory variant: move v[index] to the front.
bool moveToFront(std::vector<int>& v, int index);
