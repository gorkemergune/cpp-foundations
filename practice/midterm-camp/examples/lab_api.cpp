#include <array>
#include <cassert>
#include <cstddef>
#include <deque>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

#include "../ds/LLQueue.h"
#include "../ds/LLStack.h"

// Alıştırma API'si: deque'nin standart push_back işlemini bu adla çağır.
void pushToBack(std::deque<int>& items, int value) {
    items.push_back(value);
}

// Alıştırma API'si: source'un tepesini destination'a taşı.
bool pushFromStack(LLStack<int>& source, LLStack<int>& destination) {
    if (source.isEmpty()) {
        return false;
    }
    const int value = source.popFromStack();
    destination.pushToStack(value);
    return true;
}

// length, soruda verilen başlangıç uzunluğu.
// Önceki sıra korunacaksa kalan length - k öğeyi arkaya taşı.
void reverseFirstK(LLQueue<int>& queue, std::size_t length, std::size_t k) {
    if (k == 0 || k > length) {
        return;
    }

    LLStack<int> buffer;
    for (std::size_t i = 0; i < k; ++i) {
        buffer.pushToStack(queue.dequeue());
    }
    while (!buffer.isEmpty()) {
        queue.enqueue(buffer.popFromStack());
    }
    for (std::size_t i = k; i < length; ++i) {
        queue.enqueue(queue.dequeue());
    }
}

void showSequences() {
    std::vector<int> values{10, 20};
    values.reserve(8);
    assert(values.size() == 2 && values.capacity() >= 8);
    values.push_back(30);
    assert(values.at(1) == 20 && values.front() == 10 && values.back() == 30);
    values.pop_back();  // void
    values.resize(1);
    assert(values.size() == 1 && values[0] == 10);

    std::array<int, 3> fixed{4, 5, 6};
    assert(!fixed.empty() && fixed.size() == 3);
    assert(fixed.front() == 4 && fixed.at(1) == 5 && fixed.back() == 6);

    std::string word{"stack"};
    word.push_back('s');
    assert(word.find("ack") == 2 && word.find('!') == std::string::npos);
    assert(word.substr(2, 3) == "ack" && word.back() == 's');
    word.pop_back();
    assert(word == "stack");

    std::deque<int> ends;
    pushToBack(ends, 20);
    ends.push_front(10);
    ends.push_back(30);
    assert(ends.front() == 10 && ends.back() == 30);
    ends.pop_front();
    ends.pop_back();
    assert(ends.size() == 1 && ends.front() == 20);

    std::cout << "Vector, array, string, deque: OK\n";
}

void showStacks() {
    std::stack<int> st;
    assert(st.empty());
    st.push(10);
    st.push(20);
    int standardValue = 0;
    if (!st.empty()) {
        standardValue = st.top();  // Değeri pop'tan önce kopyala.
        st.pop();                  // void
    }
    assert(standardValue == 20 && st.top() == 10);

    LLStack<int> first;
    LLStack<int> second;
    first.pushToStack(10);
    first.pushToStack(20);
    const bool moved = pushFromStack(first, second);
    const int movedValue = second.popFromStack();  // Değeri döndürür.
    const int remaining = first.popFromStack();
    const bool movedFromEmpty = pushFromStack(first, second);
    assert(moved && movedValue == 20 && remaining == 10);
    assert(!movedFromEmpty && first.isEmpty() && second.isEmpty());

    std::cout << "Standard stack and LLStack: OK\n";
}

void showQueues() {
    std::queue<int> standard;
    standard.push(4);
    standard.push(5);
    assert(!standard.empty() && standard.size() == 2 && standard.back() == 5);
    const int front = standard.front();
    standard.pop();  // void
    assert(front == 4 && standard.front() == 5);

    LLQueue<int> queue;
    for (int value : {1, 2, 3, 4, 5}) {
        queue.enqueue(value);
    }
    reverseFirstK(queue, 5, 0);
    reverseFirstK(queue, 5, 6);
    reverseFirstK(queue, 5, 3);
    int count = 0;
    const std::array<int, 5> expected{3, 2, 1, 4, 5};
    while (!queue.isEmpty()) {
        const int value = queue.dequeue();  // Değeri döndürür.
        assert(count < static_cast<int>(expected.size()) && value == expected.at(count));
        ++count;
    }
    assert(count == 5);

    queue.enqueue(99);  // Boşaltılan queue yeniden kullanılabilmeli.
    const int afterRefill = queue.dequeue();
    assert(afterRefill == 99 && queue.isEmpty());
    reverseFirstK(queue, 0, 1);

    std::cout << "Standard queue and LLQueue: OK\n";
}

void showHashAndHeap() {
    std::unordered_map<std::string, int> counts;
    ++counts["lab"];
    const auto found = counts.find("lab");
    assert(found != counts.end() && found->second == 1);
    assert(counts.find("vize") == counts.end() && counts.size() == 1);
    const auto removed = counts.erase("lab");
    assert(removed == 1 && counts.empty());

    std::priority_queue<int> maxHeap;
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
    for (int value : {4, 1, 7}) {
        maxHeap.push(value);
        minHeap.push(value);
    }
    assert(!maxHeap.empty() && !minHeap.empty());
    assert(maxHeap.top() == 7 && minHeap.top() == 1);
    minHeap.pop();  // void
    assert(minHeap.top() == 4);

    std::cout << "Hash and priority queue: OK\n";
}

int main() {
    showSequences();
    showStacks();
    showQueues();
    showHashAndHeap();
}
