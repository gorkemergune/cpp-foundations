// Lab 22 tests. toVector() lists the stack top first.
#include <stdexcept>
#include <string>

#include "llstack.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;

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

QUESTION("L22-A", "isEmpty / pushToStack / size", "LLStack<T>::pushToStack(") {
    LLStack<int> s;
    check("new stack isEmpty", true, s.isEmpty());
    check("new stack size", 0, s.size());
    for (int x : {1, 2, 3}) s.pushToStack(x);
    check("push 1, 2, 3 (top first)", V{3, 2, 1}, s.toVector());
    check("size", 3, s.size());
    check("isEmpty", false, s.isEmpty());
    LLStack<std::string> w;
    w.pushToStack("a");
    w.pushToStack("b");
    check("T = std::string", std::vector<std::string>{"b", "a"}, w.toVector());
}

QUESTION("L22-B", "popFromStack / peek", "LLStack<T>::popFromStack(") {
    LLStack<int> s;
    for (int x : {1, 2, 3}) s.pushToStack(x);
    check("peek", 3, s.peek());
    check("peek does not remove", 3, s.size());
    check("popFromStack returns the top", 3, s.popFromStack());
    check("then", 2, s.popFromStack());
    check("then", 1, s.popFromStack());
    check("size after popping everything", 0, s.size());
    checkTrue("popFromStack on empty throws runtime_error", throwsRuntime([&] { s.popFromStack(); }), "no runtime_error");
    checkTrue("peek on empty throws runtime_error", throwsRuntime([&] { s.peek(); }), "no runtime_error");
    int alive = stackNode<int>::alive;
    s.pushToStack(5);
    s.popFromStack();
    check("popFromStack deletes the node", alive, stackNode<int>::alive);
}

QUESTION("L22-M1", "clear / destructor", "LLStack<T>::clear(") {
    int before = stackNode<int>::alive;
    {
        LLStack<int> s;
        for (int x : {1, 2, 3, 4}) s.pushToStack(x);
        check("4 nodes inside the block", before + 4, stackNode<int>::alive);
    }
    check("destructor freed every node", before, stackNode<int>::alive);
    LLStack<int> s;
    for (int x : {1, 2}) s.pushToStack(x);
    s.clear();
    checkTrue("clear(): empty, size 0, no nodes", s.isEmpty() && s.size() == 0 && stackNode<int>::alive == before,
              "clear did not free everything");
    s.pushToStack(7);
    check("usable after clear", V{7}, s.toVector());
}

QUESTION("L22-M2", "pushFromStack (practice signature)", "LLStack<T>::pushFromStack(") {
    LLStack<int> a, b;
    a.pushToStack(9);
    b.pushToStack(7);
    b.pushToStack(4);
    int alive = stackNode<int>::alive;
    int created = stackNode<int>::created;
    check("a.pushFromStack(b) returns", true, a.pushFromStack(b));
    check("no node constructed: the existing node moved", created, stackNode<int>::created);
    check("a after (top first)", V{4, 9}, a.toVector());
    check("b after", V{7}, b.toVector());
    check("sizes", 3, a.size() * 1 + b.size());
    check("no node created or deleted (the node moved)", alive, stackNode<int>::alive);
    check("a.pushFromStack(b) again", true, a.pushFromStack(b));
    check("b is empty now: pushFromStack returns", false, a.pushFromStack(b));
    check("a", V{7, 4, 9}, a.toVector());
    check("a.pushFromStack(a)", false, a.pushFromStack(a));
}

OPTIONAL_QUESTION("L22-X", "copy constructor (deep copy)", "LLStack<T>::LLStack(const") {
    LLStack<int> a;
    for (int x : {1, 2, 3}) a.pushToStack(x);
    LLStack<int> b(a);
    check("copy has the same order", a.toVector(), b.toVector());
    check("copy size", 3, b.size());
    b.popFromStack();
    check("changing the copy leaves the original", V{3, 2, 1}, a.toVector());
}

OPTIONAL_QUESTION("L22-V", "reverse (relink)", "LLStack<T>::reverse(") {
    LLStack<int> s;
    for (int x : {1, 2, 3}) s.pushToStack(x);
    int alive = stackNode<int>::alive;
    s.reverse();
    check("reverse", V{1, 2, 3}, s.toVector());
    check("no new nodes", alive, stackNode<int>::alive);
    check("size unchanged", 3, s.size());
}
