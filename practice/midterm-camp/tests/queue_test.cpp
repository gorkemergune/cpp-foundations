// QU tests. Queues are written as {front, ..., rear}.
// The PDF examples + edge cases + RANDOM_CASES random inputs vs. a std::vector reference.
#include "../ds/LLQueue.h"

namespace qu_test {
using namespace camp;
using V = std::vector<int>;

inline std::string Q(const V& v) { return "front→" + show(v); }
inline std::string I(int x) { return std::to_string(x); }

// after the operation, is rear still correct? enqueue one more and look again
inline void checkRear(const std::string& d, LLQueue<int>& q, V exp) {
    q.enqueue(99);
    exp.push_back(99);
    check(d + " then enqueue(99)", exp, q.toVector());
}

// ---------------------------------------------------------------- QU-1
QUESTION("QU-1", "Queue size", "LLQueue<T>::size(") {
    auto run = [](const V& in) {
        LLQueue<int> q;
        q.fill(in);
        check(Q(in), (int)in.size(), q.size());
        check(Q(in) + " (queue must stay unchanged)", in, q.toVector());
    };
    for (V in : std::vector<V>{{4, 6, 1}, {}, {9}, {0, 0}}) run(in);
    for (int i = 0; i < RANDOM_CASES; i++) run(randVec(30, -9, 9));
}

// ---------------------------------------------------------------- QU-2
QUESTION("QU-2", "Front and rear elements", "LLQueue<T>::get") {
    auto run = [](const V& in) {
        LLQueue<int> q;
        q.fill(in);
        check(Q(in) + " getFront", in.front(), q.getFront());
        check(Q(in) + " getRear", in.back(), q.getRear());
        check(Q(in) + " (queue must stay unchanged)", in, q.toVector());
    };
    for (V in : std::vector<V>{{4, 6, 1}, {7}, {1, 2}}) run(in);
    for (int i = 0; i < RANDOM_CASES; i++) run(randVec(10, -9, 9, 1));
    {
        LLQueue<int> q;
        checkThrows("empty queue getFront", [&] { q.getFront(); });
        checkThrows("empty queue getRear", [&] { q.getRear(); });
        q.enqueue(1);
        q.dequeue();
        checkThrows("emptied queue getFront", [&] { q.getFront(); });
        checkThrows("emptied queue getRear", [&] { q.getRear(); });
    }
}

// ---------------------------------------------------------------- QU-3
QUESTION("QU-3", "Contains", "LLQueue<T>::contains(") {
    auto run = [](const V& in, int v) {
        LLQueue<int> q;
        q.fill(in);
        std::string d = Q(in) + ", v=" + I(v);
        check(d, std::find(in.begin(), in.end(), v) != in.end(), q.contains(v));
        check(d + " (queue must stay unchanged)", in, q.toVector());
    };
    run({4, 6, 1}, 6);
    run({4, 6, 1}, 4);  // front
    run({4, 6, 1}, 1);  // rear
    run({4, 6, 1}, 9);
    run({}, 1);
    for (int i = 0; i < RANDOM_CASES; i++) run(randVec(10, 0, 9), randInt(0, 10));
}

// ---------------------------------------------------------------- QU-4
QUESTION("QU-4", "Count greater", "LLQueue<T>::countGreater(") {
    auto run = [](const V& in, int v) {
        LLQueue<int> q;
        q.fill(in);
        int exp = (int)std::count_if(in.begin(), in.end(), [v](int x) { return x > v; });
        check(Q(in) + ", v=" + I(v), exp, q.countGreater(v));
    };
    run({5, 2, 8, 7}, 5);
    run({}, 0);
    run({1, 2}, 5);
    run({5, 5}, 5);  // equal is not greater
    run({-1, -2}, -3);
    for (int i = 0; i < RANDOM_CASES; i++) run(randVec(15, -10, 10), randInt(-10, 10));
}

// ---------------------------------------------------------------- QU-5
QUESTION("QU-5", "Reverse the queue", "LLQueue<T>::reverse(") {
    auto run = [](const V& in) {
        LLQueue<int> q;
        q.fill(in);
        q.reverse();
        V exp(in.rbegin(), in.rend());
        check(Q(in), exp, q.toVector());
        checkRear(Q(in), q, exp);
    };
    for (V in : std::vector<V>{{1, 2, 3}, {}, {1}, {1, 2}, {3, 3, 1}}) run(in);
    for (int i = 0; i < RANDOM_CASES; i++) run(randVec(20, -9, 9));
}

// ---------------------------------------------------------------- QU-6
QUESTION("QU-6", "Remove all occurrences", "LLQueue<T>::removeAll(") {
    auto run = [](const V& in, int v) {
        V exp;
        for (int x : in)
            if (x != v) exp.push_back(x);
        LLQueue<int> q;
        q.fill(in);
        std::string d = Q(in) + ", v=" + I(v);
        check(d + " return", (int)(in.size() - exp.size()), q.removeAll(v));
        check(d + " queue", exp, q.toVector());
        checkRear(d, q, exp);
    };
    run({3, 7, 3, 1}, 3);
    run({}, 1);
    run({3, 3}, 3);
    run({1, 2}, 9);
    run({1, 2, 3}, 3);  // the rear element
    run({1, 2, 3}, 1);  // the front element
    for (int i = 0; i < RANDOM_CASES; i++) run(randVec(15, 0, 4), randInt(0, 5));
}

// ---------------------------------------------------------------- QU-7
QUESTION("QU-7", "Rotate k steps", "LLQueue<T>::rotate(") {
    auto run = [](const V& in, int k) {
        V exp = in;
        if (!exp.empty()) std::rotate(exp.begin(), exp.begin() + k % exp.size(), exp.end());
        LLQueue<int> q;
        q.fill(in);
        q.rotate(k);
        std::string d = Q(in) + ", k=" + I(k);
        check(d, exp, q.toVector());
        checkRear(d, q, exp);
    };
    run({1, 2, 3, 4, 5}, 7);
    run({1, 2, 3, 4, 5}, 0);
    run({1, 2, 3, 4, 5}, 5);
    run({1, 2, 3, 4, 5}, 4);
    run({1, 2, 3}, 1);
    run({1, 2, 3}, 100);
    run({}, 3);  // careful: k % 0
    run({8}, 3);
    for (int i = 0; i < RANDOM_CASES; i++) {
        V in = randVec(10, 0, 9);
        run(in, randInt(0, 3 * (int)in.size() + 2));
    }
}

// ---------------------------------------------------------------- QU-8
QUESTION("QU-8", "Reverse the first k elements", "LLQueue<T>::reverseFirstK(") {
    auto run = [](const V& in, int k) {
        V exp = in;
        if (k > 0 && k <= (int)in.size()) std::reverse(exp.begin(), exp.begin() + k);
        LLQueue<int> q;
        q.fill(in);
        q.reverseFirstK(k);
        std::string d = Q(in) + ", k=" + I(k);
        check(d, exp, q.toVector());
        checkRear(d, q, exp);
    };
    run({1, 2, 3, 4, 5}, 3);
    run({1, 2, 3, 4, 5}, 5);  // whole queue
    run({1, 2, 3, 4, 5}, 1);
    run({1, 2, 3, 4, 5}, 0);  // invalid
    run({1, 2, 3, 4, 5}, 6);  // invalid
    run({1, 2, 3, 4, 5}, -1);  // invalid
    run({}, 0);
    run({}, 1);
    run({7}, 1);
    for (int i = 0; i < RANDOM_CASES; i++) {
        V in = randVec(10, 0, 9);
        run(in, randInt(-2, (int)in.size() + 2));
    }
}

// ---------------------------------------------------------------- QU-9
QUESTION("QU-9", "Interleave the two halves", "LLQueue<T>::interleave(") {
    auto run = [](const V& in) {
        V exp;
        size_t h = in.size() / 2;
        for (size_t i = 0; i < h; i++) {
            exp.push_back(in[i]);
            exp.push_back(in[h + i]);
        }
        LLQueue<int> q;
        q.fill(in);
        q.interleave();
        check(Q(in), exp, q.toVector());
        checkRear(Q(in), q, exp);
    };
    for (V in : std::vector<V>{{1, 2, 3, 4, 5, 6}, {1, 2, 3, 4}, {1, 2}, {}, {5, 5, 6, 6},
                               {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}})
        run(in);
    for (int i = 0; i < RANDOM_CASES; i++) {
        V in = randVec(10, 0, 50);
        if (in.size() % 2) in.pop_back();
        run(in);
    }
}

// ---------------------------------------------------------------- QU-10
QUESTION("QU-10", "Josephus problem", "josephus(") {
    auto run = [](int n, int k) {
        V people;
        for (int i = 1; i <= n; i++) people.push_back(i);
        size_t idx = 0;
        while (people.size() > 1) {
            idx = (idx + k - 1) % people.size();
            people.erase(people.begin() + idx);
        }
        check("n=" + I(n) + ", k=" + I(k), people[0], josephus(n, k));
    };
    run(5, 2);
    run(1, 3);
    run(7, 3);
    run(6, 1);
    run(10, 2);
    run(2, 2);
    run(3, 5);  // k > n
    run(41, 3);
    for (int i = 0; i < RANDOM_CASES; i++) run(randInt(1, 30), randInt(1, 10));
}

}  // namespace qu_test
