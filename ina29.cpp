#include <iostream>
#include <stdexcept>
using namespace std;

class BankAccount {
private:
    int balance;

public:
    BankAccount(int b) {
        balance = b;
    }

    void deposit(int amount) {
        if (amount < 0)
            throw invalid_argument("Negative deposit not allowed");

        balance += amount;
    }

    bool withdraw(int amount) {
        if (amount < 0)
            throw invalid_argument("Negative withdrawal not allowed");

        if (amount > balance)
            return false;

        balance -= amount;
        return true;
    }

    int getBalance() {
        return balance;
    }
};

int main() {
    BankAccount acc(100);

    cout << "===== UNIT TESTING =====" << endl;
    // TODO 1:
    // Test deposit(50)
    // Check if balance becomes 150
    acc.deposit(50);
    if (acc.getBalance() == 150)
        cout << "Deposit Test Passed\n";
    else
        cout << "Deposit Test Failed\n";

    cout << "\n===== FUNCTIONAL TESTING =====" << endl;
    // TODO 2:
    // Withdraw valid amount (30)
    // Check if success and balance updated
    if (acc.withdraw(30) && acc.getBalance() == 120)
        cout << "Withdraw Test Passed\n";
    else
        cout << "Withdraw Test Failed\n";

    cout << "\n===== NEGATIVE TESTING (Exception) =====" << endl;
    // TODO 3:
    // Try deposit(-10)
    // Use try-catch to handle exception
    try {
        acc.deposit(-10);
    } catch (invalid_argument &e) {
        cout << "Caught Exception: " << e.what() << endl;
    }

    cout << "\n===== BOUNDARY TESTING =====" << endl;
    // TODO 4:
    // Withdraw exactly remaining balance
    // Check if balance becomes 0
    if (acc.withdraw(acc.getBalance()) && acc.getBalance() == 0)
        cout << "Boundary Test Passed\n";
    else
        cout << "Boundary Test Failed\n";

    cout << "\n===== REGRESSION TESTING =====" << endl;
    // TODO 5:
    // After all operations, test deposit again
    // Ensure it still works
    acc.deposit(200);
    if (acc.getBalance() == 200)
        cout << "Regression Test Passed\n";
    else
        cout << "Regression Test Failed\n";

    cout << "\n===== EXCEPTION TESTING =====" << endl;
    // TODO 6:
    // Try withdraw(-5)
    // Catch exception and print error message
    try {
        acc.withdraw(-5);
    } catch (invalid_argument &e) {
        cout << "Caught Exception: " << e.what() << endl;
    }

    return 0;
}