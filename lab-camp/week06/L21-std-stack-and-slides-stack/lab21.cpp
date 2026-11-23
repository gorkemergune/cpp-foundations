// ============================================================================
//  Lab 21 · std::stack and the slides' Stack · YOU WORK HERE
//  Test everything:      .\run.ps1 L21
//  std::stack: push, top, pop (void!), empty.   Slides Stack: see SlidesStack.h.
// ============================================================================
#include "lab21.h"

#include "todo.h"

using namespace std;

// L21-A · Example: top -> 3, 2, 1  =>  6, stack empty
int popAllSum(stack<int>& st) {
    TODO();
}

// L21-B · Example: the same values in the slides' Stack  =>  6
int popAllSumSlides(Stack& st) {
    TODO();
}

// L21-M1 · Example: "{[()]}"  =>  true;  "([)]"  =>  false;  "(("  =>  false
bool isValid(const string& s) {
    TODO();
}

// L21-M2 · Same examples as M1.
bool isValidSlides(const string& s) {
    TODO();
}

// L21-X · Example: "abbaca"  =>  "ca"
string removeDuplicates(const string& s) {
    TODO();
}

// L21-V · Example: top -> 3, 9, 1  =>  9, stack still top -> 3, 9, 1
int maxKeep(Stack& st) {
    TODO();
}
