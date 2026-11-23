#include "editor.h"

#include <fstream>
#include <sstream>

void TextEditor::clear() {
    while (head) {
        LineNode* next = head->next;
        delete head;
        head = next;
    }
    count = 0;
}

LineNode* TextEditor::nodeAt(int n) const {
    LineNode* p = head;
    for (int i = 1; i < n && p; i++) p = p->next;
    return p;
}

std::string TextEditor::line(int n) const {
    if (n < 1 || n > count) return "";
    return nodeAt(n)->text;
}

void TextEditor::insertAt(int n, const std::string& text) {
    if (n == 1) {
        head = new LineNode{text, head};
    } else {
        LineNode* prev = nodeAt(n - 1);
        prev->next = new LineNode{text, prev->next};
    }
    count++;
}

std::string TextEditor::removeAt(int n) {
    LineNode* dead;
    if (n == 1) {
        dead = head;
        head = head->next;
    } else {
        LineNode* prev = nodeAt(n - 1);
        dead = prev->next;
        prev->next = dead->next;
    }
    std::string text = dead->text;
    delete dead;
    count--;
    return text;
}

std::string TextEditor::page() const {
    std::ostringstream out;
    int first = currentPage * PAGE + 1;
    LineNode* p = nodeAt(first);
    for (int i = first; i < first + PAGE && p; i++, p = p->next) out << i << ") " << p->text << "\n";
    out << "--- page " << currentPage + 1 << "/" << pageCount() << " ---\n";
    return out.str();
}

std::string TextEditor::execute(const std::string& command) {
    std::istringstream in(command);
    std::string cmd, rest;
    in >> cmd;
    auto restOfLine = [&]() {                         // text after the number, one space skipped
        std::string r;
        std::getline(in, r);
        if (!r.empty() && r[0] == ' ') r.erase(0, 1);
        return r;
    };
    if (cmd == "open") {
        std::string name = restOfLine();
        std::ifstream f(name);
        if (!f) return "cannot open " + name;
        clear();
        std::string l;
        while (std::getline(f, l)) insertAt(count + 1, l);
        undoStack = std::stack<Action>();             // nothing before the file can be undone
        currentPage = 0;
        return "opened " + name;
    }
    if (cmd == "save") {
        std::string name = restOfLine();
        std::ofstream f(name);
        if (!f) return "cannot write " + name;
        for (LineNode* p = head; p; p = p->next) f << p->text << "\n";
        return "saved " + name;
    }
    if (cmd == "next") {
        if (currentPage + 1 < pageCount()) currentPage++;
        return "";
    }
    if (cmd == "prev") {
        if (currentPage > 0) currentPage--;
        return "";
    }
    if (cmd == "undo") return undo();

    int n = 0;
    if (!(in >> n) || n < 1) return "bad command";
    if (cmd == "insert") {
        Action a;
        a.kind = Action::Insert;
        a.n = n;
        while (count < n - 1) {                       // fill the gap with blank lines
            insertAt(count + 1, "");
            a.blanksAdded++;
        }
        insertAt(n, restOfLine());
        undoStack.push(a);
        return "";
    }
    if (n > count) return "no line " + std::to_string(n);
    if (cmd == "delete") {
        Action a;
        a.kind = Action::Delete;
        a.n = n;
        a.text = removeAt(n);
        undoStack.push(a);
        return "";
    }
    if (cmd == "replace") {
        Action a;
        a.kind = Action::Replace;
        a.n = n;
        a.text = nodeAt(n)->text;
        nodeAt(n)->text = restOfLine();
        undoStack.push(a);
        return "";
    }
    if (cmd == "move") {
        int m = 0;
        if (!(in >> m) || m < 1 || m > count) return "bad target line";
        insertAt(m, removeAt(n));                     // after removal, position m means "becomes line m"
        Action a;
        a.kind = Action::Move;
        a.n = n;
        a.m = m;
        undoStack.push(a);
        return "";
    }
    return "unknown command " + cmd;
}

std::string TextEditor::undo() {
    if (undoStack.empty()) return "nothing to undo";
    Action a = undoStack.top();
    undoStack.pop();
    switch (a.kind) {
        case Action::Insert:
            removeAt(a.n);
            for (int i = 0; i < a.blanksAdded; i++) removeAt(count);   // blanks were at the end
            break;
        case Action::Delete:
            insertAt(a.n, a.text);
            break;
        case Action::Replace:
            nodeAt(a.n)->text = a.text;
            break;
        case Action::Move:
            insertAt(a.n, removeAt(a.m));
            break;
    }
    if (currentPage >= pageCount()) currentPage = pageCount() - 1;
    return "undone";
}
