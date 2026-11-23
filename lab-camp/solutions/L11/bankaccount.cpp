// ============================================================================
//  Lab 11 · BankAccount · YOU WORK HERE
//  Reference solution. @solution-note
//  Test everything:      .\run.ps1 L11
//  Write every member as  ReturnType BankAccount::name(params) [const] { ... }
// ============================================================================
#include "bankaccount.h"

#include <sstream>

#include "todo.h"

using namespace std;

// L11-A · Example: BankAccount a("Ada", 1250)  =>  owner "Ada", balance 1250, 0 transactions
// @begin BankAccount
BankAccount::BankAccount(const string& owner, int initialCents)
    : owner_(owner), balance_(initialCents < 0 ? 0 : initialCents), transactions_(0) {
    // members are initialised in the list above, before this body runs
}
// @end BankAccount

// @begin owner
string BankAccount::owner() const {
    return owner_;
}
// @end owner

// @begin balance
int BankAccount::balance() const {
    return balance_;
}
// @end balance

// @begin transactionCount
int BankAccount::transactionCount() const {
    return transactions_;
}
// @end transactionCount

// L11-B · Example: deposit(500) on 1250  =>  true, balance 1750;  deposit(0)  =>  false
// @begin deposit
bool BankAccount::deposit(int cents) {
    if (cents <= 0) return false;
    balance_ += cents;
    transactions_++;
    return true;
}
// @end deposit

// L11-M1 · Example: withdraw(2000) on 1750  =>  false, nothing changes
// @begin withdraw
bool BankAccount::withdraw(int cents) {
    if (cents <= 0 || cents > balance_) return false;   // check everything first
    balance_ -= cents;
    transactions_++;
    return true;
}
// @end withdraw

// L11-M2 · Example: transfer(ada, bob, 300)  =>  true; ada -300, bob +300
// @begin transfer
bool transfer(BankAccount& from, BankAccount& to, int cents) {
    if (&from == &to) return false;              // same object: refuse
    if (!from.withdraw(cents)) return false;     // fails -> nothing has happened yet
    to.deposit(cents);                           // cannot fail: cents > 0 was checked
    return true;
}
// @end transfer

// L11-X · Example: "   fly me   to   the moon  "  =>  4
// @begin lengthOfLastWord
int lengthOfLastWord(const string& s) {
    int i = (int)s.size() - 1, len = 0;
    while (i >= 0 && s[i] == ' ') i--;           // skip trailing spaces
    while (i >= 0 && s[i] != ' ') { len++; i--; }
    return len;
}
// @end lengthOfLastWord

// L11-V · Example: Ada with 1250 cents and 3 transactions  =>  "Ada: 12.50 TL (3 tx)"
// @begin summary
string summary(const BankAccount& a) {
    ostringstream out;                           // build a string like cout
    int c = a.balance() % 100;
    out << a.owner() << ": " << a.balance() / 100 << "." << (c < 10 ? "0" : "") << c
        << " TL (" << a.transactionCount() << " tx)";
    return out.str();
}
// @end summary
