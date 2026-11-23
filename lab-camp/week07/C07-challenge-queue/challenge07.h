// ============================================================================
//  Challenge Set 07 · queues and deques (medium / hard)             DO NOT EDIT
// ============================================================================
#pragma once

#include <string>
#include <vector>

// C07-A · LeetCode 649 (medium): "R"/"D" senators ban each other in rounds; the party that
// survives wins. Return "Radiant" or "Dire".
std::string predictPartyVictory(const std::string& senate);

// C07-B · LeetCode 641 (medium): a deque of capacity k in a circular array.
class MyCircularDeque {
public:
    explicit MyCircularDeque(int k);
    bool insertFront(int value);
    bool insertLast(int value);
    bool deleteFront();
    bool deleteLast();
    int getFront() const;   // -1 if empty
    int getRear() const;    // -1 if empty
    bool isEmpty() const;
    bool isFull() const;
private:
    std::vector<int> a;
    int head;   // index of the front element
    int count;
};

// C07-C · LeetCode 239 (hard): the maximum of every window of k consecutive values. O(n).
std::vector<int> maxSlidingWindow(const std::vector<int>& nums, int k);
