// Assignment 2 (2021) Q2 · the main loop of the given main.cpp with /delete and /undo filled in.
// It reads from `in` so the tests can feed commands.
#include "editor.h"

#include <string>

#include "codeStack.h"

using namespace std;

void run_editor(istream& in) {
    codeStack stk, undoStk;
    string input;
    while (getline(in, input)) {
        if (input == "/exit") {
            cout << "The last state of the document is:" << endl;
            stk.printReverseStack();
            break;
        }
        if (input == "/delete") {
            // delete = move the last line to the undo stack (it may come back)
            if (stk.isEmpty()) cout << "Error: Nothing to delete." << endl;
            else undoStk.pushToStack(stk.popFromStack().c_str());
        } else if (input == "/undo") {
            // undo = move the most recently deleted line back
            if (undoStk.isEmpty()) cout << "Nothing to undo." << endl;
            else stk.pushToStack(undoStk.popFromStack().c_str());
        } else if (input == "/reversePrint") {
            stk.printReverseStack();
        } else if (input == "/print") {
            stk.printStack();
        } else {
            stk.pushToStack(input.c_str());
            // A new line makes older deletions irrelevant. The given main called
            // undoStk.~codeStack() here; calling a destructor by hand and then using the
            // object again is undefined behaviour, so we empty it with pops instead.
            while (!undoStk.isEmpty()) undoStk.popFromStack();
        }
    }
}
