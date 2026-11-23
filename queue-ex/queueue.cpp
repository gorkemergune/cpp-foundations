#include "Queue.h"

// Safety limit for the tests: stops a runaway loop from using all memory.
static const size_t MAX_QUEUE_SIZE = 1000000;

template <typename T>
Queue<T>::Queue() : front(nullptr), rear(nullptr), count(0) {}

template <typename T> Queue<T>::~Queue() { clear(); }

// ---------------- Core operations ----------------

template <typename T> void Queue<T>::enqueue(const T &value) {
  if (count >= MAX_QUEUE_SIZE)
    throw std::length_error("enqueue: queue is too large (infinite loop?)");

  Node *node = new Node(value);
  if (isEmpty())
    front = node;
  else
    rear->next = node;
  rear = node;
  ++count;
}

template <typename T> T Queue<T>::dequeue() {
  if (isEmpty())
    throw std::runtime_error("dequeue: queue is empty");

  Node *temp = front;
  T value = temp->data;
  front = front->next;
  if (front == nullptr)
    rear = nullptr;
  delete temp;
  --count;
  return value;
}

template <typename T> T Queue<T>::getFront() const {
  if (isEmpty())
    throw std::runtime_error("getFront: queue is empty");
  return front->data;
}

// ---------------- Utility methods ----------------

template <typename T> bool Queue<T>::isEmpty() const { return front == nullptr; }

template <typename T> int Queue<T>::size() const {
  return static_cast<int>(count);
}

template <typename T> void Queue<T>::clear() {
  while (front != nullptr) {
    Node *temp = front;
    front = front->next;
    delete temp;
  }
  rear = nullptr;
  count = 0;
}

// ---------------- Copy operations ----------------

template <typename T>
Queue<T>::Queue(const Queue &other) : front(nullptr), rear(nullptr), count(0) {
  for (Node *p = other.front; p != nullptr; p = p->next)
    enqueue(p->data);
}

template <typename T> Queue<T> &Queue<T>::operator=(const Queue &other) {
  if (this != &other) {
    clear();
    for (Node *p = other.front; p != nullptr; p = p->next)
      enqueue(p->data);
  }
  return *this;
}

// ---------------- Move operations ----------------

template <typename T>
Queue<T>::Queue(Queue &&other) noexcept
    : front(other.front), rear(other.rear), count(other.count) {
  other.front = nullptr;
  other.rear = nullptr;
  other.count = 0;
}

template <typename T> Queue<T> &Queue<T>::operator=(Queue &&other) noexcept {
  if (this != &other) {
    clear();
    front = other.front;
    rear = other.rear;
    count = other.count;
    other.front = nullptr;
    other.rear = nullptr;
    other.count = 0;
  }
  return *this;
}

// ---------------- Question 1 ----------------

void fillGaps(Queue<int> &q) {
  int n = q.size();
  if (n < 2)
    return;

  int prev = q.dequeue();
  q.enqueue(prev);

  for (int i = 1; i < n; i++) {
    int cur = q.dequeue();
    for (int v = prev + 1; v < cur; v++)
      q.enqueue(v);
    q.enqueue(cur);
    prev = cur;
  }
}

// ---------------- Question 2 ----------------

Queue<char> mergeUnique(Queue<char> &a, Queue<char> &b) {
  Queue<char> result;
  Queue<char> x(a);
  Queue<char> y(b);

  bool hasLast = false;
  char last = 0;

  while (!x.isEmpty() || !y.isEmpty()) {
    char c;
    if (y.isEmpty() || (!x.isEmpty() && x.getFront() <= y.getFront()))
      c = x.dequeue();
    else
      c = y.dequeue();

    if (!hasLast || c != last) {
      result.enqueue(c);
      last = c;
      hasLast = true;
    }
  }

  return result;
}

template class Queue<int>;
template class Queue<char>;