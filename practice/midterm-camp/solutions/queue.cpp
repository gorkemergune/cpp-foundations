// ============================================================================
//  QUEUE · QU-1 … QU-10 · reference solutions
//  Run the tests against this file:  .\run.ps1 -Solution qu
// ============================================================================
#include "../ds/LLQueue.h"

template <typename T>
int LLQueue<T>::size() {
    int n = 0;
    for (queueNode<T>* p = front; p != 0; p = p->next) n++;
    return n;
}

template <typename T>
T LLQueue<T>::getFront() {
    if (isEmpty()) throw runtime_error("getFront: queue is empty");
    return front->info;
}

template <typename T>
T LLQueue<T>::getRear() {
    if (isEmpty()) throw runtime_error("getRear: queue is empty");
    return rear->info;
}

template <typename T>
bool LLQueue<T>::contains(const T& v) {
    for (queueNode<T>* p = front; p != 0; p = p->next)
        if (p->info == v) return true;
    return false;
}

template <typename T>
int LLQueue<T>::countGreater(const T& v) {
    int n = 0;
    for (queueNode<T>* p = front; p != 0; p = p->next)
        if (p->info > v) n++;
    return n;
}

template <typename T>
void LLQueue<T>::reverse() {
    LLStack<T> st;
    while (!isEmpty()) st.pushToStack(dequeue());
    while (!st.isEmpty()) enqueue(st.popFromStack());
}

// Rotation pattern: look at each element exactly once (n = size at the start).
template <typename T>
int LLQueue<T>::removeAll(const T& v) {
    int n = size(), removed = 0;
    for (int i = 0; i < n; i++) {
        T x = dequeue();
        if (x == v) removed++;
        else enqueue(x);
    }
    return removed;
}

template <typename T>
void LLQueue<T>::rotate(int k) {
    int n = size();
    if (n == 0) return;
    for (int i = 0; i < k % n; i++) enqueue(dequeue());
}

template <typename T>
void LLQueue<T>::reverseFirstK(int k) {
    int n = size();
    if (k <= 0 || k > n) return;
    LLStack<T> st;
    for (int i = 0; i < k; i++) st.pushToStack(dequeue());
    while (!st.isEmpty()) enqueue(st.popFromStack());
    for (int i = 0; i < n - k; i++) enqueue(dequeue());   // the rest goes behind again
}

template <typename T>
void LLQueue<T>::interleave() {
    int half = size() / 2;
    LLQueue<T> first;
    for (int i = 0; i < half; i++) first.enqueue(dequeue());
    while (!first.isEmpty()) {
        enqueue(first.dequeue());           // one from the first half
        enqueue(dequeue());                 // one from the second half (now at the front)
    }
}

int josephus(int n, int k) {
    LLQueue<int> q;
    for (int i = 1; i <= n; i++) q.enqueue(i);
    while (q.size() > 1) {
        for (int i = 0; i < k - 1; i++) q.enqueue(q.dequeue());   // skip k-1 people
        q.dequeue();                                              // the k-th is out
    }
    return q.dequeue();
}
