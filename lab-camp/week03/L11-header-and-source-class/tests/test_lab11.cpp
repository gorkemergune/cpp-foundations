// Lab 11 tests.
#include "bankaccount.h"
#include "test.h"

using namespace lab;

struct PDF_LEN_Case { std::string s; int ret; };
#include "pdf_cases.inc"

QUESTION("L11-A", "constructor and getters", "BankAccount::BankAccount(") {
    BankAccount a("Ada", 1250);
    check("BankAccount(\"Ada\", 1250).owner()", std::string("Ada"), a.owner());
    check("balance()", 1250, a.balance());
    check("transactionCount()", 0, a.transactionCount());
    BankAccount z("Zed", -40);
    check("BankAccount(\"Zed\", -40).balance()", 0, z.balance());
}

QUESTION("L11-B", "deposit", "BankAccount::deposit(") {
    BankAccount a("Ada", 1250);
    check("deposit(500)", true, a.deposit(500));
    check("balance after deposit(500)", 1750, a.balance());
    check("deposit(0)", false, a.deposit(0));
    check("deposit(-10)", false, a.deposit(-10));
    check("balance after two rejected deposits", 1750, a.balance());
    check("transactionCount (only successful ones)", 1, a.transactionCount());
}

QUESTION("L11-M1", "withdraw", "BankAccount::withdraw(") {
    BankAccount a("Ada", 1750);
    check("withdraw(2000) on 1750", false, a.withdraw(2000));
    check("balance unchanged", 1750, a.balance());
    check("withdraw(1750): the whole balance", true, a.withdraw(1750));
    check("balance", 0, a.balance());
    check("withdraw(0)", false, a.withdraw(0));
    check("withdraw(-5)", false, a.withdraw(-5));
    check("transactionCount", 1, a.transactionCount());
}

QUESTION("L11-M2", "transfer (all or nothing)", "transfer(") {
    BankAccount ada("Ada", 1000), bob("Bob", 0);
    check("transfer(ada, bob, 300)", true, transfer(ada, bob, 300));
    check("ada", 700, ada.balance());
    check("bob", 300, bob.balance());
    check("transfer(ada, bob, 701): too much", false, transfer(ada, bob, 701));
    check("ada unchanged", 700, ada.balance());
    check("bob unchanged", 300, bob.balance());
    check("transfer(ada, bob, 0)", false, transfer(ada, bob, 0));
    check("transfer(ada, ada, 100): same account", false, transfer(ada, ada, 100));
    check("ada after self transfer", 700, ada.balance());
    check("transaction counts (1 each)", 2, ada.transactionCount() + bob.transactionCount());
}

OPTIONAL_QUESTION("L11-X", "lengthOfLastWord (LC 58)", "lengthOfLastWord(") {
    for (auto& c : PDF_LEN) check("s=" + show(c.s), c.ret, lengthOfLastWord(c.s));
}

OPTIONAL_QUESTION("L11-V", "summary", "summary(") {
    BankAccount a("Ada", 1000);
    a.deposit(250);
    a.withdraw(100);
    a.deposit(100);
    check("Ada, 12.50, 3 tx", std::string("Ada: 12.50 TL (3 tx)"), summary(a));
    BankAccount b("Bob", 5);
    check("Bob, 0.05", std::string("Bob: 0.05 TL (0 tx)"), summary(b));
}
