// Banking System Simulation in C++
// This program simulates a simple banking system where users can create accounts, deposit, withdraw, and view transaction history.
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Transaction {
public:
    string type;
    double amount;
    string date;

    Transaction(const string& type, double amount, const string& date)
        : type(type), amount(amount), date(date) {}
};

class Account {
private:
    string accountNumber;
    string accountHolder;
    double balance;
    vector<Transaction> transactionHistory;

public:
    Account(const string& accNumber, const string& holder)
        : accountNumber(accNumber), accountHolder(holder), balance(0.0) {}

    string getAccountNumber() const {
        return accountNumber;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            transactionHistory.emplace_back("Deposit", amount, getCurrentDate());
            cout << "Deposited: $" << amount << "\n";
        } else {
            cout << "Invalid deposit amount.\n";
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            transactionHistory.emplace_back("Withdrawal", amount, getCurrentDate());
            cout << "Withdrew: $" << amount << "\n";
        } else {
            cout << "Invalid withdrawal amount or insufficient funds.\n";
        }
    }

    void printBalance() const {
        cout << "Current balance: $" << fixed << setprecision(2) << balance << "\n";
    }

    void printTransactionHistory() const {
        cout << "Transaction History for " << accountHolder << ":\n";
        for (const auto& transaction : transactionHistory) {
            cout << transaction.date << " - " << transaction.type << ": $" << transaction.amount << "\n";
        }
    }

    static string getCurrentDate() {
        return "2025-04-24";  // You may replace this with actual time logic using <ctime>
    }
};

class BankingSystem {
private:
    vector<Account> accounts;

public:
    void createAccount(const string& accNumber, const string& holder) {
        accounts.emplace_back(accNumber, holder);
        cout << "Account created for " << holder << " with account number " << accNumber << ".\n";
    }

    Account* findAccount(const string& accNumber) {
        for (auto& account : accounts) {
            if (account.getAccountNumber() == accNumber) {
                return &account;
            }
        }
        cout << "Account not found.\n";
        return nullptr;
    }
};

int main() {
    BankingSystem bank;
    int choice;
    string accNumber, holder;
    double amount;

    while (true) {
        cout << "\n--- Banking System Menu ---\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Show Balance\n";
        cout << "5. Show Transaction History\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Account Number: ";
                cin >> accNumber;
                cout << "Enter Account Holder Name: ";
                cin.ignore();  // Clear input buffer
                getline(cin, holder);
                bank.createAccount(accNumber, holder);
                break;

            case 2:
                cout << "Enter Account Number: ";
                cin >> accNumber;
                if (Account* acc = bank.findAccount(accNumber)) {
                    cout << "Enter amount to deposit: ";
                    cin >> amount;
                    acc->deposit(amount);
                }
                break;

            case 3:
                cout << "Enter Account Number: ";
                cin >> accNumber;
                if (Account* acc = bank.findAccount(accNumber)) {
                    cout << "Enter amount to withdraw: ";
                    cin >> amount;
                    acc->withdraw(amount);
                }
                break;

            case 4:
                cout << "Enter Account Number: ";
                cin >> accNumber;
                if (Account* acc = bank.findAccount(accNumber)) {
                    acc->printBalance();
                }
                break;

            case 5:
                cout << "Enter Account Number: ";
                cin >> accNumber;
                if (Account* acc = bank.findAccount(accNumber)) {
                    acc->printTransactionHistory();
                }
                break;

            case 6:
                cout << "Exiting Banking System. Goodbye!\n";
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
