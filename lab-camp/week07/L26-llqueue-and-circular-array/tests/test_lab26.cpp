// Lab 26 tests. Queues are written front first.
#include <deque>
#include <stdexcept>

#include "circularqueue.h"
#include "llqueue.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_TICKET_Case { V tickets; int k; int ret; };
#include "pdf_cases.inc"

template <class F>
static bool throwsRuntime(F f) {
    try {
        f();
    } catch (const NotImplemented&) {
        throw;
    } catch (const std::runtime_error&) {
        return true;
    }
    return false;
}

QUESTION("L26-A", "LLQueue enqueue / isEmpty / size", "LLQueue<T>::enqueue(") {
    LLQueue<int> q;
    check("new queue isEmpty", true, q.isEmpty());
    for (int x : {1, 2, 3}) q.enqueue(x);
    check("enqueue 1, 2, 3", V{1, 2, 3}, q.toVector());
    check("size", 3, q.size());
    checkTrue("rear is the last node", q.endsOk(), "rear is wrong");
}

QUESTION("L26-B", "LLQueue dequeue / getFront / getRear", "LLQueue<T>::dequeue(") {
    LLQueue<int> q;
    for (int x : {0, 2, 3}) q.enqueue(x);
    check("getFront", 0, q.getFront());
    check("getRear", 3, q.getRear());
    check("dequeue returns 0 (a value, not 'false')", 0, q.dequeue());
    check("dequeue", 2, q.dequeue());
    check("dequeue the last element", 3, q.dequeue());
    checkTrue("empty: front and rear both null", q.isEmpty() && q.endsOk() && q.size() == 0, "rear dangles");
    q.enqueue(9);
    check("enqueue after emptying (rear must have been reset)", V{9}, q.toVector());
    check("getFront == getRear for one element", q.getFront(), q.getRear());
    q.dequeue();
    checkTrue("dequeue on empty throws runtime_error", throwsRuntime([&] { q.dequeue(); }), "no runtime_error");
    checkTrue("getFront on empty throws", throwsRuntime([&] { q.getFront(); }), "no runtime_error");
    checkTrue("getRear on empty throws", throwsRuntime([&] { q.getRear(); }), "no runtime_error");
    for (int t = 0; t < RANDOM_CASES; t++) {                      // random mixes vs std::deque
        LLQueue<int> m;
        std::deque<int> ref;
        bool ok = true;
        for (int k = 0; k < 20 && ok; k++) {
            if (ref.empty() || randInt(0, 2) > 0) {
                int x = randInt(0, 9);
                m.enqueue(x);
                ref.push_back(x);
            } else {
                ok = m.dequeue() == ref.front();
                ref.pop_front();
            }
            ok = ok && m.size() == (int)ref.size() && m.endsOk();
        }
        checkTrue("random enqueue/dequeue sequence " + std::to_string(t), ok, "FIFO order, size or rear is wrong");
    }
}

QUESTION("L26-M1", "LLQueue clear / destructor", "LLQueue<T>::clear(") {
    int before = queueNode<int>::alive;
    {
        LLQueue<int> q;
        for (int x : {1, 2, 3}) q.enqueue(x);
    }
    check("destructor freed every node", before, queueNode<int>::alive);
    LLQueue<int> q;
    for (int x : {1, 2}) q.enqueue(x);
    q.clear();
    checkTrue("clear(): empty, rear null, size 0", q.isEmpty() && q.endsOk() && q.size() == 0, "not cleared");
    q.enqueue(5);
    check("usable after clear", V{5}, q.toVector());
}

QUESTION("L26-M2", "MyCircularQueue (LC 622, slides' array queue)", "MyCircularQueue::") {
    MyCircularQueue c(3);
    check("enQueue(1)", true, c.enQueue(1));
    check("enQueue(2)", true, c.enQueue(2));
    check("enQueue(3)", true, c.enQueue(3));
    check("enQueue(4) on a full queue", false, c.enQueue(4));
    check("Rear", 3, c.Rear());
    check("isFull", true, c.isFull());
    check("deQueue", true, c.deQueue());
    check("enQueue(4) after deQueue (wraps to index 0)", true, c.enQueue(4));
    check("Rear", 4, c.Rear());
    check("Front", 2, c.Front());
    MyCircularQueue e(2);
    check("empty: Front", -1, e.Front());
    check("empty: Rear", -1, e.Rear());
    check("empty: deQueue", false, e.deQueue());
    for (int t = 0; t < RANDOM_CASES; t++) {
        int k = randInt(1, 4);
        MyCircularQueue m(k);
        std::deque<int> ref;
        bool ok = true;
        for (int s = 0; s < 25 && ok; s++) {
            if (randInt(0, 1)) {
                int x = randInt(0, 9);
                bool want = (int)ref.size() < k;
                if (want) ref.push_back(x);
                ok = m.enQueue(x) == want;
            } else {
                bool want = !ref.empty();
                if (want) ref.pop_front();
                ok = m.deQueue() == want;
            }
            ok = ok && m.Front() == (ref.empty() ? -1 : ref.front()) && m.Rear() == (ref.empty() ? -1 : ref.back()) &&
                 m.isEmpty() == ref.empty() && m.isFull() == ((int)ref.size() == k);
        }
        checkTrue("random operations, capacity " + std::to_string(k), ok, "wrap-around or full/empty is wrong");
    }
}

OPTIONAL_QUESTION("L26-X", "timeRequiredToBuy (LC 2073)", "timeRequiredToBuy(") {
    for (auto& c : PDF_TICKET)
        check("tickets=" + show(c.tickets) + ", k=" + std::to_string(c.k), c.ret, timeRequiredToBuy(c.tickets, c.k));
}

OPTIONAL_QUESTION("L26-V", "LLQueue reverse (relink)", "LLQueue<T>::reverse(") {
    LLQueue<int> q;
    for (int x : {1, 2, 3}) q.enqueue(x);
    q.reverse();
    check("reverse", V{3, 2, 1}, q.toVector());
    checkTrue("rear after reverse", q.endsOk(), "rear is wrong");
    q.enqueue(4);
    check("enqueue after reverse", V{3, 2, 1, 4}, q.toVector());
}
