#include <sstream>

#include "check.h"
#include "codeStack.h"
#include "editor.h"

static std::string session(const std::string& commands) {
    std::istringstream in(commands);
    return captured([&] { run_editor(in); });
}

int main() {
    codeStack s;
    s.pushToStack("a");
    s.pushToStack("b");
    s.pushToStack("c");
    CHECK_EQ(captured([&] { s.printStack(); }), std::string("c\nb\na\n"));
    CHECK_EQ(captured([&] { s.printReverseStack(); }), std::string("a\nb\nc\n"));
    CHECK_EQ(s.popFromStack(), std::string("c"));
    CHECK_EQ(s.popFromStack(), std::string("b"));
    CHECK_EQ(s.popFromStack(), std::string("a"));
    CHECK(s.isEmpty());
    CHECK_EQ(captured([&] { CHECK_EQ(s.popFromStack(), std::string("")); }), std::string("Error: Nothing to delete.\n"));

    std::string end = "The last state of the document is:\n";
    CHECK_EQ(session("one\ntwo\nthree\n/delete\n/delete\n/undo\n/exit\n"), end + "one\ntwo\n");
    CHECK_EQ(session("one\ntwo\n/delete\n/delete\n/undo\n/undo\n/exit\n"), end + "one\ntwo\n");
    CHECK_EQ(session("one\n/delete\nnew\n/undo\n/exit\n"), "Nothing to undo.\n" + end + "new\n");  // new text clears undo
    CHECK_EQ(session("/delete\n/undo\n/exit\n"), "Error: Nothing to delete.\nNothing to undo.\n" + end);
    CHECK_EQ(session("x y z\n/print\n/exit\n"), "x y z\n" + end + "x y z\n");   // a line may contain spaces
    return check_summary("2021 a2 codeStack + undo");
}
