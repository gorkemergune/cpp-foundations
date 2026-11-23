#include "check.h"
#include "genDLList.h"
#include "palindrome.h"

int main() {
    CHECK(is_palindrome("ey edip adanada pide ye"));
    CHECK(!is_palindrome("test"));
    CHECK(is_palindrome("mum"));
    CHECK(is_palindrome("racecar"));
    CHECK(is_palindrome(""));
    CHECK(is_palindrome("a"));
    CHECK(is_palindrome("abba"));
    CHECK(!is_palindrome("ab"));
    CHECK(!is_palindrome("Mum"));  // case-sensitive
    DoublyLinkedList<int> s;       // Q1 contract: LIFO, top() is a reference
    s.push(1); s.push(2); s.push(3);
    CHECK_EQ(s.top(), 3);
    s.top() = 30;
    CHECK_EQ(s.top(), 30);
    s.pop();
    CHECK_EQ(s.top(), 2);
    s.pop(); s.pop();
    CHECK(s.isEmpty());
    return check_summary("lw3 push/top/pop + is_palindrome");
}
