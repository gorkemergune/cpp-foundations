// Lab 09 · Warm-up. Predict every output line on paper first, then compile:
//   g++ -std=c++17 -Wall warmup.cpp -o warmup.exe
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s = "data";                     // owns its characters, no '\0' to manage
    s += "-structures";                    // grows like a vector<char>
    cout << "1) " << s << " size=" << s.size() << "\n";
    cout << "2) s[0]=" << s[0] << " back=" << s.back() << "\n";
    cout << "3) find(\"struct\") = " << s.find("struct") << "\n";
    size_t miss = s.find("xyz");
    cout << "4) miss == npos? " << (miss == string::npos) << "\n";
    cout << "5) substr(5, 6) = " << s.substr(5, 6) << "\n";
    string t = s;                          // a copy, like std::vector
    t[0] = 'D';
    cout << "6) s=" << s << " t=" << t << "\n";
    cout << "7) \"abc\" < \"abd\"? " << (string("abc") < string("abd")) << "\n";
    char c = 'A' + 2;                      // a char is a small integer
    cout << "8) c=" << c << " as int=" << (int)c << "\n";
    return 0;
}
