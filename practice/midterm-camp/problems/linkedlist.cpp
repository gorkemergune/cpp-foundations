// ============================================================================
//  LINKED LIST · LL-1 … LL-10
//  Delete the TODO(); line in a function and write your own code.
//  Test:  .\run.ps1 ll        single problem:  .\run.ps1 LL-6
//  Debugging: you can call print(); inside any function.
// ============================================================================
#include "../ds/LinkedList.h"

// LL-1 · Easy · Node count
// Return the number of nodes in the list. 0 for an empty list.
// Example: 3 → 8 → 1  ⇒  3
int LinkedList::count() const
{
    Node *p = head;
    int count = 0;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }
    return count;
}

// LL-2 · Easy · Occurrences of a value
// Return how many times v appears in the list.
// Example: 4 → 2 → 4 → 4, v = 4  ⇒  3
int LinkedList::countValue(int v) const
{
    int count = 0;
    Node *p = head;
    while (p != NULL)
    {
        if (p->item == v)
            count++;
        p = p->next;
    }
    return count;
}

// LL-3 · Easy · Index of the maximum
// Return the index (0-based) of the FIRST occurrence of the largest value. -1 if empty.
// Example: 3 → 9 → 2 → 9  ⇒  1
int LinkedList::indexOfMax() const
{
    Node *p = head;
    if (p == NULL)
        return -1;

    int max = -100, index = 0, maxIndex = 0;

    while (p != NULL)
    {
        if (p->item > max)
        {
            max = p->item;
            maxIndex = index;
        }
        index++;
        p = p->next;
    }
    return maxIndex;
}

// LL-4 · Easy · Insert at end
// Append v to the end of the list.
// Example: 1 → 2, v = 7  ⇒  1 → 2 → 7
void LinkedList::insertAtEnd(int v)
{
    Node *p = head;

    if (head == NULL)
    {
        head = new Node;
        head->item = v;
        head->next = NULL;
        return;
    }

    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = new Node;
    p->next->item = v;
    p->next->next = NULL;
}

// LL-5 · Medium · Remove first occurrence
// Remove the FIRST node holding v (don't forget delete). Return true if removed, false otherwise.
// Example: 1 → 4 → 3 → 4, v = 4  ⇒  1 → 3 → 4  (returns true)
bool LinkedList::removeFirst(int v)
{
    Node *p = head;
    Node *prev = NULL;

    while (p != NULL)
    {
        if (p->item == v)
        {
            if (prev == NULL)
                head = p->next; // v değeri ilk kez gelince sil
            else
                prev->next = p->next; // aynı v değeri tekrar gelirse atla
            delete p;
            return true;
        }

        prev = p;
        p = p->next;
    }
    return false;
}

// LL-6 · Medium · Reverse the list
// Reverse the list in place (without allocating new nodes).
// Example: 1 → 2 → 3  ⇒  3 → 2 → 1
void LinkedList::reverse()
{
    TODO();
}

// LL-7 · Medium · Insert into a sorted list
// The list is sorted in ascending order. Insert v so that it stays sorted.
// Example: 1 → 3 → 8, v = 5  ⇒  1 → 3 → 5 → 8
void LinkedList::insertSorted(int v)
{
    TODO();
}

// LL-8 · Medium · Insert after every target
// Insert a new node holding value after every node holding target.
// Return the number of inserted nodes.
// Example: 2 → 5 → 2, target = 2, value = 9  ⇒  2 → 9 → 5 → 2 → 9  (returns 2)
int LinkedList::insertAfterEach(int target, int value)
{
    TODO();
}

// LL-9 · Hard · Remove duplicates (unsorted list)
// Keep the first occurrence of each value, delete the later duplicates.
// Return the number of deleted nodes.
// Example: 3 → 1 → 3 → 2 → 1  ⇒  3 → 1 → 2  (returns 2)
int LinkedList::removeDuplicates()
{
    TODO();
}

// LL-10 · Hard · Swap adjacent pairs (with pointers)
// Swap consecutive nodes two by two. Changing item values is FORBIDDEN, only the
// pointers may change (the tests check this). A leftover single node stays in place.
// Example: 1 → 2 → 3 → 4 → 5  ⇒  2 → 1 → 4 → 3 → 5
void LinkedList::swapPairs()
{
    TODO();
}
