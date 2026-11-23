#include <cstdio>
#include <fstream>

#include "check.h"
#include "editor.h"

static std::string all(const TextEditor& e) {
    std::string r;
    for (int i = 1; i <= e.lineCount(); i++) r += e.line(i) + "|";
    return r;
}

int main() {
    { std::ofstream f("tmp_in.txt"); for (int i = 1; i <= 12; i++) f << "line " << i << "\n"; }
    TextEditor e;
    CHECK_EQ(e.execute("open tmp_in.txt"), std::string("opened tmp_in.txt"));
    CHECK_EQ(e.lineCount(), 12);
    CHECK(e.page().find("--- page 1/2 ---") != std::string::npos);
    e.execute("next");
    CHECK(e.page().find("11) line 11") != std::string::npos);
    e.execute("next");                                       // already the last page
    CHECK(e.page().find("page 2/2") != std::string::npos);
    e.execute("prev");

    e.execute("insert 2 hello my friend");
    CHECK_EQ(e.line(2), std::string("hello my friend"));
    CHECK_EQ(e.line(3), std::string("line 2"));
    e.execute("delete 1");
    CHECK_EQ(e.line(1), std::string("hello my friend"));
    e.execute("replace 1 changed");
    e.execute("move 1 3");
    CHECK_EQ(e.line(3), std::string("changed"));
    CHECK_EQ(e.line(1), std::string("line 2"));
    e.execute("insert 16 far away");                         // 13 lines -> 3 blanks + new line 16
    CHECK_EQ(e.lineCount(), 16);
    CHECK_EQ(e.line(15), std::string(""));
    CHECK_EQ(e.line(16), std::string("far away"));

    for (int i = 0; i < 5; i++) e.execute("undo");           // back to the opened file
    CHECK_EQ(e.lineCount(), 12);
    CHECK_EQ(e.line(1), std::string("line 1"));
    CHECK_EQ(e.line(2), std::string("line 2"));
    CHECK_EQ(e.execute("undo"), std::string("nothing to undo"));   // open cleared the stack

    e.execute("replace 12 last");
    CHECK_EQ(e.execute("save tmp_out.txt"), std::string("saved tmp_out.txt"));
    TextEditor f;
    f.execute("open tmp_out.txt");
    CHECK_EQ(f.line(12), std::string("last"));
    CHECK_EQ(all(f).substr(0, 14), std::string("line 1|line 2|"));
    CHECK_EQ(f.execute("delete 99"), std::string("no line 99"));
    CHECK_EQ(f.execute("move 1 99"), std::string("bad target line"));
    CHECK_EQ(f.execute("open no_such_file.txt"), std::string("cannot open no_such_file.txt"));
    std::remove("tmp_in.txt");
    std::remove("tmp_out.txt");
    return check_summary("2021 term project text editor");
}
