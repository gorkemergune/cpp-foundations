// ============================================================================
//  Lab 07 · Pointers into arrays and 2-D arrays                    DO NOT EDIT
//  A range is given as two pointers [begin, end): begin points at the first
//  element, end points ONE PAST the last one (it is never dereferenced).
// ============================================================================
#pragma once

#include <vector>

const int MAXN = 10;   // every 2-D array in this lab is declared as int m[MAXN][MAXN]

// L07-A · Warm-up · pointer to the first element equal to x in [begin, end), or end.
const int* findFirst(const int* begin, const int* end, int x);

// L07-B · Warm-up · exchange *x and *y. If either pointer is nullptr, do nothing.
void swapViaPointers(int* x, int* y);

// L07-M1 · Main · LeetCode 1572: sum of both diagonals of the n x n top-left part of m;
// the centre cell of an odd n is counted once.
int diagonalSum(const int m[][MAXN], int n);

// L07-M2 · Main · transpose the n x n top-left part of m in place (m[i][j] <-> m[j][i]).
void transposeSquare(int m[][MAXN], int n);

// L07-X · Optional · LeetCode 867: transpose of an R x C matrix (result is C x R).
std::vector<std::vector<int>> transpose(const std::vector<std::vector<int>>& matrix);

// L07-V · Optional · memory variant: how many values in [begin, end) satisfy lo <= v <= hi.
int countInRange(const int* begin, const int* end, int lo, int hi);
