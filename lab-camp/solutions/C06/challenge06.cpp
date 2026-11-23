// ============================================================================
//  Challenge Set 06 · stacks · YOU WORK HERE
//  Reference solution. @solution-note
//  Test:  .\run.ps1 C06        one problem:  .\run.ps1 C06 C06-C
// ============================================================================
#include "challenge06.h"

#include <stack>

#include "todo.h"

using namespace std;

// C06-A · Example: {73,74,75,71,69,72,76,73}  =>  {1,1,4,2,1,1,0,0}
// @begin dailyTemperatures
vector<int> dailyTemperatures(const vector<int>& t) {
    vector<int> answer(t.size(), 0);
    stack<int> waiting;                     // indexes of days still waiting, temperatures decreasing
    for (int i = 0; i < (int)t.size(); i++) {
        while (!waiting.empty() && t[waiting.top()] < t[i]) {
            answer[waiting.top()] = i - waiting.top();   // day i is the first warmer day
            waiting.pop();
        }
        waiting.push(i);
    }
    return answer;                          // days left in the stack keep 0
}
// @end dailyTemperatures

// C06-B · Example: "3[a]2[bc]"  =>  "aaabcbc"
// @begin decodeString
string decodeString(const string& s) {
    stack<int> counts;
    stack<string> outer;                    // the text built before each '['
    string cur;
    int k = 0;
    for (char c : s) {
        if (c >= '0' && c <= '9') {
            k = k * 10 + (c - '0');         // counts may have several digits
        } else if (c == '[') {
            counts.push(k);
            outer.push(cur);
            k = 0;
            cur.clear();
        } else if (c == ']') {
            string repeated;
            for (int i = 0; i < counts.top(); i++) repeated += cur;
            counts.pop();
            cur = outer.top() + repeated;   // glue the decoded part to what came before
            outer.pop();
        } else {
            cur += c;
        }
    }
    return cur;
}
// @end decodeString

// C06-C · Example: {2,1,5,6,2,3}  =>  10 (bars 5 and 6, width 2)
// @begin largestRectangleArea
int largestRectangleArea(const vector<int>& h) {
    stack<int> st;                          // indexes with increasing heights
    int best = 0, n = h.size();
    for (int i = 0; i <= n; i++) {
        int cur = (i == n) ? 0 : h[i];      // a 0 at the end flushes the stack
        while (!st.empty() && h[st.top()] >= cur) {
            int height = h[st.top()];
            st.pop();
            int left = st.empty() ? -1 : st.top();   // first lower bar on the left
            int width = i - left - 1;                // i is the first lower bar on the right
            if (height * width > best) best = height * width;
        }
        st.push(i);
    }
    return best;
}
// @end largestRectangleArea
