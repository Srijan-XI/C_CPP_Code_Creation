//ATM Simulator
//This program simulates an ATM system where users can check balance, deposit, withdraw money, and view transaction history.
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class Account {
private:
    string accountHolder;
    string pin;
    double balance;
    vector<string> transactionHistory;

public:
    Account(string holder, string _pin, double initialBalance)
        : accountHolder(holder), pin(_pin), balance(initialBalance) {
        transactionHistory.push_back("Account created with balance: $" + to_string(balance));
    }

    bool authenticate(string inputPin) {
        return pin == inputPin;
    }

    void displayBalance() const {
        cout << "Current Balance: $" << fixed << setprecision(2) << balance << "\n";
    }

    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Invalid deposit amount.\n";
            return;
        }
        balance += amount;
        transactionHistory.push_back("Deposited: $" + to_string(amount));
        cout << "Deposit successful.\n";
    }

    void withdraw(double amount) {
        if (amount <= 0 || amount > balance) {
            cout << "Invalid or insufficient balance for withdrawal.\n";
            return;
        }
        balance -= amount;
        transactionHistory.push_back("Withdrawn: $" + to_string(amount));
        cout << "Withdrawal successful.\n";
    }

    bool transfer(Account &receiver, double amount) {
        if (amount <= 0 || amount > balance) {
            cout << "Invalid or insufficient balance for transfer.\n";
            return false;
        }
        balance -= amount;
        receiver.balance += amount;
        transactionHistory.push_back("Transferred: $" + to_string(amount) + " to " + receiver.accountHolder);
        receiver.transactionHistory.push_back("Received: $" + to_string(amount) + " from " + accountHolder);
        cout << "Transfer successful.\n";
        return true;
    }

    void showTransactionHistory() const {
        cout << "--- Transaction History for " << accountHolder << " ---\n";
        for (const auto &record : transactionHistory) {
            cout << record << "\n";
        }
    }

    string getName() const { return accountHolder; }
};

int main() {
    Account acc1("Srijan", "0000", 5000.0);
    Account acc2("Ankit", "1111", 3000.0);

    string inputPin;
    int option;
    cout << "Welcome to the ATM Simulator\n";
    cout << "Please enter your PIN: ";
    cin >> inputPin;

    if (!acc1.authenticate(inputPin)) {
        cout << "Authentication failed. Exiting...\n";
        return 1;
    }

    while (true) {
        cout << "\nATM Menu:\n";
        cout << "1. Check Balance\n";
        cout << "2. Deposit Funds\n";
        cout << "3. Withdraw Funds\n";
        cout << "4. Transfer Funds\n";
        cout << "5. Transaction History\n";
        cout << "6. Exit\n";
        cout << "Select an option: ";
        cin >> option;

        switch (option) {
            case 1:
                acc1.displayBalance();
                break;
            case 2: {
                double amount;
                cout << "Enter deposit amount: ";
                cin >> amount;
                acc1.deposit(amount);
                break;
            }
            case 3: {
                double amount;
                cout << "Enter withdrawal amount: ";
                cin >> amount;
                acc1.withdraw(amount);
                break;
            }
            case 4: {
                double amount;
                cout << "Enter amount to transfer to Rahul: ";
                cin >> amount;
                acc1.transfer(acc2, amount);
                break;
            }
            case 5:
                acc1.showTransactionHistory();
                break;
            case 6:
                cout << "Thank you for using our ATM. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}
