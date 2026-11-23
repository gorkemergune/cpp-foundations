// ============================================================================
//  Lab 29 · MIDTERM MOCK A (50 min) · linked lists and stacks       DO NOT EDIT
// ============================================================================
#pragma once

#include <stack>

#include "SlidesStack.h"

// Part A (30 pts) · two stacks with the SLIDES' API (push, pop(item&), getTop, isEmpty):
// move the top of `from` onto `to`. Empty `from` -> false. `to` full -> false and
// `from` must be unchanged.
bool moveTopSlides(Stack& from, Stack& to);

// Part B (30 pts) · empty() vs !empty(): count the values greater than x in st.
// st is passed BY VALUE (a copy), so you may empty it.
int countAbove(std::stack<int> st, int x);

// Part C (40 pts) · a doubly linked list given by head AND tail. Delete the middle node
// (index n/2) and keep every next and prev correct. Empty list -> false.
struct DNode {
    int data;
    DNode* prev;
    DNode* next;
    DNode(int d) : data(d), prev(nullptr), next(nullptr) { alive++; }
    ~DNode() { alive--; }
    static inline int alive = 0;
};
bool deleteMiddleDLL(DNode*& head, DNode*& tail);
