// Lab 10 · Warm-up. The input comes from a string here so that the output is fixed;
// cin works exactly the same way. Predict every line, then compile.
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {
    istringstream cin2("42\nAda Lovelace\n  7 8\n");   // pretend this is the keyboard
    int n;
    string line;
    cin2 >> n;                                         // reads 42, the '\n' stays
    getline(cin2, line);                               // reads what is LEFT of line 1
    cout << "1) n=" << n << " line=[" << line << "]\n";
    getline(cin2, line);
    cout << "2) line=[" << line << "]\n";
    string first, last;
    istringstream words(line);                         // split one line into words
    words >> first >> last;
    cout << "3) first=" << first << " last=" << last << "\n";
    getline(cin2, line);
    cout << "4) line=[" << line << "]\n";
    istringstream nums(line);
    int a, b, c = -1;
    nums >> a >> b;
    bool ok = static_cast<bool>(nums >> c);            // there is no third number
    cout << "5) a=" << a << " b=" << b << " third read ok? " << ok << " c=" << c << "\n";
    return 0;
}
