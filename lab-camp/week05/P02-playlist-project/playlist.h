// ============================================================================
//  Mini Project 02 · Playlist on a doubly linked list               DO NOT EDIT
// ============================================================================
#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>

class Playlist {
public:
    Playlist();
    ~Playlist();                                      // P02-A · frees every node
    Playlist(const Playlist&) = delete;
    Playlist& operator=(const Playlist&) = delete;

    // P02-A · append a song. If there is no current song, the new one becomes current.
    void add(const std::string& title, int seconds);
    int size() const;                                 // P02-A
    int totalSeconds() const;                         // P02-A
    std::string current() const;                      // P02-A · "" if the playlist is empty

    // P02-B · move the current song; false (and no move) at the ends - no wrap-around.
    bool next();
    bool prev();
    // P02-B · remove the FIRST song with this title. If it was current, the song after it
    // becomes current; if there is none, the one before it; if none, nothing is current.
    bool remove(const std::string& title);

    // P02-C · swap the song with the one before it by RELINKING nodes (current stays on
    // the same song). False if not found or already first.
    bool moveUp(const std::string& title);
    // P02-C · one line per song: "1. Title (3:05)\n"; the current song gets a '*' before
    // its title: "2. *Title (0:59)\n". Empty playlist -> "".
    std::string listing() const;

    // test helper: titles read backwards through prev (checks the prev links)
    std::string backwardTitles() const;

private:
    struct Node {
        std::string title;
        int seconds;
        Node* prev;
        Node* next;
    };
    Node* head;
    Node* tail;
    Node* cur;
    int count;
};

#endif
