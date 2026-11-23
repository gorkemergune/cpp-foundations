// ============================================================================
//  Lab 11 · Header and source: your first class                    DO NOT EDIT
//  The header DECLARES the class; bankaccount.cpp DEFINES its member functions.
//  Money is stored in cents (int) so that 0.1 + 0.2 problems never appear.
// ============================================================================
#ifndef BANKACCOUNT_H     // include guard: the same as #pragma once, the old way
#define BANKACCOUNT_H

#include <string>

class BankAccount {
public:
    // L11-A · owner name and starting balance; a negative start becomes 0.
    BankAccount(const std::string& owner, int initialCents);

    std::string owner() const;      // L11-A · const: does not change the object
    int balance() const;            // L11-A · in cents
    int transactionCount() const;   // L11-A · successful deposits + withdrawals

    bool deposit(int cents);        // L11-B · cents > 0, otherwise false and no change
    bool withdraw(int cents);       // L11-M1 · 0 < cents <= balance, otherwise false

private:
    std::string owner_;
    int balance_;
    int transactions_;
};

// L11-M2 · move money from one account to another: all or nothing.
bool transfer(BankAccount& from, BankAccount& to, int cents);

// L11-X · Optional · LeetCode 58: length of the last word of s.
int lengthOfLastWord(const std::string& s);

// L11-V · Optional · "Ada: 12.50 TL (3 tx)" (two decimals, transactions in brackets).
std::string summary(const BankAccount& a);

#endif
