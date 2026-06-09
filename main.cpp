#include <iostream>
#include "BankAccount.h"
using namespace std;

int main() {
double deposit, withdraw;

    BankAccount myAccount("123456789", 1000.0);

    cout << "How much do you want to deposit: $ ";
    cin >> deposit ;

    myAccount.deposit(deposit);
    cout << "After depositing "<< deposit <<": " << endl;
    cout << "Balance is: $" << myAccount.getBalance() << endl << endl;

    cout << "How much do you want to withdraw: $ ";
    cin >> withdraw ;

    myAccount.withdraw(withdraw);
    cout << "After withdrawing "<< withdraw <<": " << endl;

    cout << "Balance is: $" << myAccount.getBalance() << endl;

    return 0;
}
