// ============================================================================
//  Lab 21 · std::stack and the slides' Stack: two APIs, one idea    DO NOT EDIT
// ============================================================================
#pragma once

#include <stack>
#include <string>

#include "SlidesStack.h"

// L21-A · Warm-up · std::stack: pop everything, return the sum. The stack ends empty.
int popAllSum(std::stack<int>& st);

// L21-B · Warm-up · the same with the slides' Stack (use pop(item&) or getTop + pop()).
int popAllSumSlides(Stack& st);

// L21-M1 · Main · LeetCode 20: are the brackets ()[]{} balanced? Use std::stack<char>.
bool isValid(const std::string& s);

// L21-M2 · Main · the same contract (only ()[]{} characters), with the slides' Stack
// holding the char codes. Only isEmpty, push, pop, pop(item&), getTop are allowed.
bool isValidSlides(const std::string& s);

// L21-X · Optional · LeetCode 1047: repeatedly remove two equal adjacent letters.
std::string removeDuplicates(const std::string& s);

// L21-V · Optional · memory variant: the largest value in the slides' Stack;
// the stack must be EXACTLY as before afterwards. Precondition: not empty.
int maxKeep(Stack& st);
