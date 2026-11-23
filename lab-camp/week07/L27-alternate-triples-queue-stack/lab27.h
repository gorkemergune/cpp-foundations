// ============================================================================
//  Lab 27 · Alternate triples with a queue and ONE stack (midterm)  DO NOT EDIT
//  Allowed: std::queue push/front/pop/empty/size, std::stack push/top/pop/empty.
// ============================================================================
#pragma once

#include <queue>
#include <stack>

// L27-A · Warm-up · reverse the whole queue with one stack.
void reverseQueue(std::queue<int>& q);

// L27-B · Warm-up · reverse the first k elements; k <= 0 or k > size: nothing changes.
void reverseFirstK(std::queue<int>& q, int k);

// L27-M · Main (midterm) · reverse the 1st, 3rd, 5th ... COMPLETE group of three; the other
// groups and an incomplete last group keep their order. At most one helper stack.
// 1 2 3 4 5 6 7 8 9  ->  3 2 1 4 5 6 9 8 7
void reverseAlternateTriples(std::queue<int>& q);

// L27-X · Optional · GeeksforGeeks "Reverse First K of Queue" signature: the queue is
// passed by value and the result is returned.
std::queue<int> reverseFirstKGfG(std::queue<int> q, int k);

// L27-V · Optional · memory variant: reverse EVERY complete group of g (g >= 1);
// an incomplete last group stays.
void reverseGroups(std::queue<int>& q, int g);
