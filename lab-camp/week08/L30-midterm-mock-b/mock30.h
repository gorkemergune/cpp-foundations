// ============================================================================
//  Lab 30 · MIDTERM MOCK B (50 min) · strings, stacks, queues       DO NOT EDIT
// ============================================================================
#pragma once

#include <string>

#include "SlidesQueue.h"
#include "SlidesStack.h"

// Part A (30 pts) · the smallest integer written inside a text. A number is a maximal run
// of digits; a '-' directly before the run makes it negative. "a12b-3c5" -> -3.
// No number in the text: false, out unchanged. Numbers have at most 9 digits.
bool minNumberInText(const std::string& s, int& out);

// Part B (30 pts) · is b the reverse of a? Use TWO of the slides' Stacks (char codes as int).
// Strings are at most MAX_STACK characters long.
bool areReversesSlides(const std::string& a, const std::string& b);

// Part C (40 pts) · the queue holds n values. Reverse the 1st, 3rd, 5th ... COMPLETE group
// of g values (g >= 1); the other groups and an incomplete last group keep their order.
// Use only the slides' Queue and ONE slides' Stack.
void reverseAlternateGroupsSlides(Queue& q, int n, int g);
