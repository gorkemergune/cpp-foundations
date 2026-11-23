// ============================================================================
//  Lab 25 · std::queue and the slides' Queue · YOU WORK HERE
//  Test everything:      .\run.ps1 L25
//  std::queue: push (back), front, back, pop (void!), empty, size.
// ============================================================================
#include "lab25.h"

#include "todo.h"

using namespace std;

// L25-A · Example: front -> 1, 2, 3  =>  {1, 2, 3}, queue empty
vector<int> drainStd(queue<int>& q) {
    TODO();
}

// L25-B · Example: the same values in the slides' Queue  =>  {1, 2, 3}
vector<int> drainSlides(Queue& q) {
    TODO();
}

// L25-M1 · Example: ping(1) 1, ping(100) 2, ping(3001) 3, ping(3002) 3
int RecentCounter::ping(int t) {
    TODO();
}

// L25-M2 · Example: a = 1 2 3, b = 1 2 3  =>  true;  a = 1 2, b = 1 2 3  =>  false
bool sameQueue(const Queue& a, const Queue& b) {
    TODO();
}

// L25-X · Example: students {1,1,0,0}, sandwiches {0,1,0,1}  =>  0
int countStudents(const vector<int>& students, const vector<int>& sandwiches) {
    TODO();
}

// L25-V · Example: front -> 1, 2, 3, 4, 5, k = 7  =>  front -> 3, 4, 5, 1, 2
void rotateK(queue<int>& q, int k) {
    TODO();
}
