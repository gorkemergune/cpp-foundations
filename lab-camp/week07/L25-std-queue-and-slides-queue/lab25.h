// ============================================================================
//  Lab 25 · std::queue and the slides' Queue                        DO NOT EDIT
// ============================================================================
#pragma once

#include <queue>
#include <vector>

#include "SlidesQueue.h"

// L25-A · Warm-up · std::queue: remove everything, return the values front first.
std::vector<int> drainStd(std::queue<int>& q);

// L25-B · Warm-up · the same with the slides' Queue (use dequeue(item&)).
std::vector<int> drainSlides(Queue& q);

// L25-M1 · Main · LeetCode 933 with the slides' Queue: ping(t) adds a request at time t
// (t strictly increases) and returns how many requests happened in [t - 3000, t].
class RecentCounter {
public:
    int ping(int t);
private:
    Queue times;
};

// L25-M2 · Main · do a and b hold the same values in the same order? Neither may change
// (they are const): work on copies made with the copy constructor.
bool sameQueue(const Queue& a, const Queue& b);

// L25-X · Optional · LeetCode 1700: students (0/1) queue for sandwiches (0/1, a stack whose
// top is sandwiches[0]). Return how many students cannot eat.
int countStudents(const std::vector<int>& students, const std::vector<int>& sandwiches);

// L25-V · Optional · memory variant: move the front to the back k times (k may exceed size).
void rotateK(std::queue<int>& q, int k);
