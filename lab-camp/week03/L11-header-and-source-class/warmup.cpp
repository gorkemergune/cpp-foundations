// Lab 11 · Warm-up: a whole class in one file. Predict the output, then compile:
//   g++ -std=c++17 -Wall warmup.cpp -o warmup.exe
#include <iostream>
#include <string>
using namespace std;

class Counter {
public:
    Counter(const string& name, int start) : name_(name), value_(start) {
        cout << "  [constructor " << name_ << "]\n";
    }
    ~Counter() { cout << "  [destructor " << name_ << "]\n"; }
    void add(int k) { value_ += k; }          // changes the object
    int value() const { return value_; }      // const: only reads
private:
    string name_;
    int value_;
};

int main() {
    cout << "1) start\n";
    Counter a("a", 10);
    a.add(5);
    cout << "2) a=" << a.value() << "\n";
    {
        Counter b("b", 1);                    // lives until the closing brace
        cout << "3) b=" << b.value() << "\n";
    }
    cout << "4) after the block\n";
    const Counter c("c", 7);
    cout << "5) c=" << c.value() << "\n";     // c.add(1) would not compile: c is const
    return 0;
}
