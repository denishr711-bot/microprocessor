#include <string>
using namespace std;

class BankAccount {
private:
    double balance;
    string accountNumber;

public:
    BankAccount(string accNum, double initialBalance);

    void deposit(double amount);
    void withdraw(double amount);
    double getBalance() const;
};