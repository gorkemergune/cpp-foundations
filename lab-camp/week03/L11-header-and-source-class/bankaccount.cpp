// ============================================================================
//  Lab 11 · BankAccount · YOU WORK HERE
//  Test everything:      .\run.ps1 L11
//  Write every member as  ReturnType BankAccount::name(params) [const] { ... }
// ============================================================================
#include "bankaccount.h"

#include <sstream>

#include "todo.h"

using namespace std;

// L11-A · Example: BankAccount a("Ada", 1250)  =>  owner "Ada", balance 1250, 0 transactions
BankAccount::BankAccount(const string& owner, int initialCents) {
    TODO();
}

string BankAccount::owner() const {
    TODO();
}

int BankAccount::balance() const {
    TODO();
}

int BankAccount::transactionCount() const {
    TODO();
}

// L11-B · Example: deposit(500) on 1250  =>  true, balance 1750;  deposit(0)  =>  false
bool BankAccount::deposit(int cents) {
    TODO();
}

// L11-M1 · Example: withdraw(2000) on 1750  =>  false, nothing changes
bool BankAccount::withdraw(int cents) {
    TODO();
}

// L11-M2 · Example: transfer(ada, bob, 300)  =>  true; ada -300, bob +300
bool transfer(BankAccount& from, BankAccount& to, int cents) {
    TODO();
}

// L11-X · Example: "   fly me   to   the moon  "  =>  4
int lengthOfLastWord(const string& s) {
    TODO();
}

// L11-V · Example: Ada with 1250 cents and 3 transactions  =>  "Ada: 12.50 TL (3 tx)"
string summary(const BankAccount& a) {
    TODO();
}
