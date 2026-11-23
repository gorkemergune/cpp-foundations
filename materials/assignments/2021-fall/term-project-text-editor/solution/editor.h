// Term project (2021) · command-based text editor.
// Lines live in a singly linked list (one node per line); every change is pushed to an
// undo stack as an Action record.
#pragma once
#include <stack>
#include <string>

struct LineNode {
    std::string text;
    LineNode* next;
};

// What is needed to reverse one command.
struct Action {
    enum Kind { Insert, Delete, Move, Replace } kind = Insert;
    int n = 0, m = 0;        // positions (1-based)
    int blanksAdded = 0;     // Insert: empty lines created to reach position n
    std::string text;        // Delete: removed text, Replace: previous text
};

class TextEditor {
public:
    static const int PAGE = 10;

    TextEditor() = default;
    ~TextEditor() { clear(); }
    TextEditor(const TextEditor&) = delete;
    TextEditor& operator=(const TextEditor&) = delete;

    // Runs one command line and returns a message ("" when there is nothing to say).
    // open f | save f | insert n text | delete n | move n m | replace n text | next | prev | undo
    std::string execute(const std::string& command);

    std::string page() const;          // the current page with line numbers and "page x/y"
    int lineCount() const { return count; }
    std::string line(int n) const;     // 1-based, "" if out of range

private:
    LineNode* head = nullptr;
    int count = 0;
    int currentPage = 0;               // 0-based
    std::stack<Action> undoStack;

    void clear();
    void insertAt(int n, const std::string& text);   // 1 <= n <= count + 1
    std::string removeAt(int n);                     // 1 <= n <= count
    LineNode* nodeAt(int n) const;
    int pageCount() const { return count == 0 ? 1 : (count + PAGE - 1) / PAGE; }
    std::string undo();
};
