#include "BankAccount.h"
#include <iostream>
using namespace std;

BankAccount::BankAccount(string accNum, double initialBalance) 
    : accountNumber(accNum), balance(initialBalance) {}

void BankAccount::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
    }
}

void BankAccount::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
    } else {
        cout << "Insufficient funds or invalid amount." << endl;
    }
}

double BankAccount::getBalance() const {
    return balance;
}
