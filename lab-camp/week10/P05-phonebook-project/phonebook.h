// ============================================================================
//  Mini Project 05 · Phone book on a binary search tree             DO NOT EDIT
//  Keys are names (std::string, compared with <); every name appears once.
// ============================================================================
#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include <iostream>
#include <string>
#include <vector>

class PhoneBook {
public:
    PhoneBook() = default;
    ~PhoneBook();                                    // P05-A · free every entry
    PhoneBook(const PhoneBook&) = delete;            // no copies (rule of three)
    PhoneBook& operator=(const PhoneBook&) = delete;

    // P05-A
    bool add(const std::string& name, const std::string& phone);     // false if the name exists
    bool update(const std::string& name, const std::string& phone);  // false if it does not
    bool find(const std::string& name, std::string& phone) const;
    int size() const;

    // P05-B · remove by copying the inorder successor (Lab 38); names starting with prefix,
    // ascending, without visiting subtrees that cannot contain any.
    bool remove(const std::string& name);
    std::vector<std::string> namesWithPrefix(const std::string& prefix) const;

    // P05-C · one "name phone" line per entry in PREORDER, so that load() rebuilds exactly the
    // same tree; load adds the lines of a stream (existing names are skipped); height (Lab 36).
    void save(std::ostream& out) const;
    void load(std::istream& in);
    int height() const;

private:
    struct Entry {
        std::string name, phone;
        Entry* left = nullptr;
        Entry* right = nullptr;
    };
    Entry* root = nullptr;
    int count = 0;

    static void destroy(Entry* p);
    Entry** findLink(const std::string& name);       // the pointer that holds / would hold name
    static void prefixInto(const Entry* p, const std::string& prefix, std::vector<std::string>& out);
    static void saveFrom(const Entry* p, std::ostream& out);
    static int heightOf(const Entry* p);
};

#endif
