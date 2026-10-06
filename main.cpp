/*
Author: Fabian Olmedo
Date: September 5, 2026
Project: Advanced Objects & Classes II
Purpose: Extend your existing `BankAccount` class to incorporate operator overloading and
static utility functions, allowing for more natural and intuitive interactions with bank account objects
*/
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

class BankAccount {
private:
    string* accountNumber; // pointers to strings
    string* accountHolderName; // pointers to strings
    double balance;

public:
    // Empty account w default values
    BankAccount() {
        accountNumber = new string("Unknown"); // string in dynamic memory
        accountHolderName = new string("Unknown"); // string in dynamic memory
        balance = 0.0;
    }

    // Creates an acc
    BankAccount(string number, string name, double initialBalance) {
        accountNumber = new string(number); // separate copy of the acc num
        accountHolderName = new string(name); // separate copy of the acc num
        balance = initialBalance;
    }

    // Copy constructor
    BankAccount(const BankAccount& other) {
        accountNumber = new string(*other.accountNumber);
        accountHolderName = new string(*other.accountHolderName);
        balance = other.balance;
    }

    // Copy assignment operator
    BankAccount& operator=(const BankAccount& other) {
        if (this != &other) {
            *accountNumber = *other.accountNumber;
            *accountHolderName = *other.accountHolderName;
            balance = other.balance;
        }
        return *this;
    }

    // Destructor (cleanup)
    ~BankAccount() {
        delete accountNumber;
        delete accountHolderName;
    }

    // Get the account number
    string getAccountNumber() const {
        return *accountNumber;
    }

    string getAccountHolderName() const {
        return *accountHolderName;
    }

    // Gets the balance
    double getBalance() const {
        return balance;
    }

    // Get account holder name
    void setAccountHolderName(string name) {
        *accountHolderName = name;
    }

    // Add money using +=
    BankAccount& operator+=(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposit successful.\n";
        }
        else {
            cout << "Deposit amount must be greater than 0.\n";
        }

        return *this;
    }

    // Withdraw money using -=
    BankAccount& operator-=(double amount) {
        if (amount <= 0) {
            cout << "Withdrawal amount must be greater than 0.\n";
        }
        else if (amount > balance) {
            cout << "Insufficient funds.\n";
        }
        else {
            balance -= amount;
            cout << "Withdrawal successful.\n";
        }

        return *this;
    }

    // Compares account numbers
    bool operator==(const BankAccount& other) const {
        return *accountNumber == *other.accountNumber;
    }

    // Compares balances
    bool operator<(const BankAccount& other) const {
        return balance < other.balance;
    }

    // Compares balances
    bool operator>(const BankAccount& other) const {
        return balance > other.balance;
    }

    // Prints account information
    static void printAccount(const BankAccount& account) {
        cout << fixed << setprecision(2);
        cout << "Account Number: " << account.getAccountNumber() << endl;
        cout << "Account Holder: " << account.getAccountHolderName() << endl;
        cout << "Balance: $" << account.getBalance() << endl;
    }

    // Creates an account using user input
    static BankAccount createAccountFromInput() {
        string accountNumber;
        string accountHolderName;
        double initialBalance;

        cout << "Enter account number: ";
        cin >> accountNumber;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter account holder name: ";
        getline(cin, accountHolderName);

        cout << "Enter initial balance: ";
        cin >> initialBalance;

        while (cin.fail() || initialBalance < 0) {
            cout << "Invalid amount. Enter a non-negative balance: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> initialBalance;
        }

        return BankAccount(accountNumber, accountHolderName, initialBalance);
    }
};

// Gets a valid integer from the user
int getInteger() {
    int value;

    while (!(cin >> value)) {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return value;
}

// Gets a valid positive amount from the user
double getAmount() {
    double amount;

    while (!(cin >> amount) || amount <= 0) {
        cout << "Invalid amount. Enter a value greater than 0: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return amount;
}

// Displays all accounts
void displayAccounts(const vector<BankAccount>& accounts) {
    if (accounts.empty()) {
        cout << "No accounts available.\n";
        return;
    }

    cout << fixed << setprecision(2);

    for (size_t i = 0; i < accounts.size(); ++i) {
        cout << "\nAccount " << i + 1 << endl;
        BankAccount::printAccount(accounts[i]);
    }
}

int main() {
    //keeps track of all the accounts
    vector<BankAccount> accounts;

    int choice;

    do {
        cout << "\n===== Bank Account Management System =====\n";
        cout << "1. Create Account\n";
        cout << "2. Display Accounts\n";
        cout << "3. Deposit\n";
        cout << "4. Withdraw\n";
        cout << "5. Change Account Holder Name\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        choice = getInteger();

        if (choice == 1) {
            string accountNumber;
            string accountHolderName;
            double initialBalance;

            cout << "Enter account number: ";
            cin >> accountNumber;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter account holder name: ";
            getline(cin, accountHolderName);

            cout << "Enter initial balance: ";
            initialBalance = getAmount();

            // Add new account to the vector
            accounts.emplace_back(accountNumber, accountHolderName, initialBalance);

            cout << "Account created successfully.\n";
        }
        else if (choice == 2) {
            displayAccounts(accounts);
        }
        else if (choice == 3) {
            if (accounts.empty()) {
                cout << "No accounts available.\n";
            }
            else {
                displayAccounts(accounts);

                cout << "\nEnter account number (1-" << accounts.size() << "): ";
                int accountIndex = getInteger();

                if (accountIndex >= 1 &&
                    accountIndex <= static_cast<int>(accounts.size())) {

                    cout << "Enter deposit amount: ";
                    double amount = getAmount();

                    accounts[accountIndex - 1].deposit(amount);
                    }
                else {
                    cout << "Invalid account number.\n";
                }
            }
        }
        else if (choice == 4) {
            if (accounts.empty()) {
                cout << "No accounts available.\n";
            }
            else {
                displayAccounts(accounts);

                cout << "\nEnter account number (1-" << accounts.size() << "): ";
                int accountIndex = getInteger();

                if (accountIndex >= 1 &&
                    accountIndex <= static_cast<int>(accounts.size())) {

                    cout << "Enter withdrawal amount: ";
                    double amount = getAmount();

                    accounts[accountIndex - 1].withdraw(amount);
                    }
                else {
                    cout << "Invalid account number.\n";
                }
            }
        }
        else if (choice == 5) {
            if (accounts.empty()) {
                cout << "No accounts available.\n";
            }
            else {
                displayAccounts(accounts);

                cout << "\nEnter account number (1-" << accounts.size() << "): ";
                int accountIndex = getInteger();

                if (accountIndex >= 1 &&
                    accountIndex <= static_cast<int>(accounts.size())) {

                    string newName;

                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    cout << "Enter new account holder name: ";
                    getline(cin, newName);

                    accounts[accountIndex - 1].setAccountHolderName(newName);

                    cout << "Account holder name updated.\n";
                    }
                else {
                    cout << "Invalid account number.\n";
                }
            }
        }
        else if (choice == 6) {
            cout << "Thank you for using the Bank Account Management System.\n";
        }
        else {
            cout << "Invalid choice. Please select 1-6.\n";
        }

    } while (choice != 6);

    return 0;
}
