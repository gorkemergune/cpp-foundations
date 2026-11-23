// Labwork 3 Q2 · palindrome check that uses ONLY push, top and pop.
#include "palindrome.h"

#include "genDLList.h"

bool is_palindrome(const std::string& s) {
    DoublyLinkedList<char> st;
    for (char c : s) st.push(c);          // the top is now the LAST character
    for (char c : s) {                    // read forward, pop backward
        if (c != st.top()) return false;  // stack has exactly s.size() items, never empty here
        st.pop();
    }
    return true;                          // "" is a palindrome
}
