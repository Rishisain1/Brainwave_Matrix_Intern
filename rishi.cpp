#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Account {
private:
    int accountNumber;
    string accountHolderName;
    double balance;

public:
    // Constructor to initialize account
    Account(int accNum, string name, double initialDeposit) {
        accountNumber = accNum;
        accountHolderName = name;
        balance = initialDeposit;
    }

    // Getter for account number
    int getAccountNumber() {
        return accountNumber;
    }

    // Getter for account holder name
    string getAccountHolderName() {
        return accountHolderName;
    }

    // Getter for balance
    double getBalance() {
        return balance;
    }

    // Deposit method
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposit successful! Current balance: " << balance << endl;
        } else {
            cout << "Invalid deposit amount!" << endl;
        }
    }

    // Withdraw method
    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawal successful! Current balance: " << balance << endl;
        } else {
            cout << "Invalid withdrawal amount or insufficient funds!" << endl;
        }
    }

    // Transfer method
    void transfer(Account &receiver, double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            receiver.deposit(amount);
            cout << "Transfer successful! Your current balance: " << balance << endl;
        } else {
            cout << "Invalid transfer amount or insufficient funds!" << endl;
        }
    }

    // Display account details
    void display() {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Balance: " << balance << endl;
    }
};

class BankingSystem {
private:
    vector<Account> accounts;
    int nextAccountNumber;

public:
    // Constructor to initialize the next account number
    BankingSystem() {
        nextAccountNumber = 1001; // Initial account number
    }

    // Create a new account
    void createAccount(string name, double initialDeposit) {
        if (initialDeposit >= 0) {
            Account newAccount(nextAccountNumber, name, initialDeposit);
            accounts.push_back(newAccount);
            cout << "Account created successfully! Account Number: " << nextAccountNumber << endl;
            nextAccountNumber++;
        } else {
            cout << "Initial deposit cannot be negative!" << endl;
        }
    }

    // Find account by account number
    Account* findAccount(int accNum) {
        for (auto &account : accounts) {
            if (account.getAccountNumber() == accNum) {
                return &account;
            }
        }
        return nullptr;
    }

    // Deposit to an account
    void depositToAccount(int accNum, double amount) {
        Account* account = findAccount(accNum);
        if (account != nullptr) {
            account->deposit(amount);
        } else {
            cout << "Account not found!" << endl;
        }
    }

    // Withdraw from an account
    void withdrawFromAccount(int accNum, double amount) {
        Account* account = findAccount(accNum);
        if (account != nullptr) {
            account->withdraw(amount);
        } else {
            cout << "Account not found!" << endl;
        }
    }

    // Transfer between accounts
    void transferBetweenAccounts(int senderAccNum, int receiverAccNum, double amount) {
        Account* sender = findAccount(senderAccNum);
        Account* receiver = findAccount(receiverAccNum);

        if (sender != nullptr && receiver != nullptr) {
            sender->transfer(*receiver, amount);
        } else {
            cout << "Sender or receiver account not found!" << endl;
        }
    }

    // Display account information
    void displayAccount(int accNum) {
        Account* account = findAccount(accNum);
        if (account != nullptr) {
            account->display();
        } else {
            cout << "Account not found!" << endl;
        }
    }
};

// Main program to test the banking system
int main() {
    BankingSystem bank;
    int choice;
    string name;
    double amount;
    int accNum, senderAccNum, receiverAccNum;

    do {
        cout << "\n--- Online Banking System ---\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Funds\n";
        cout << "3. Withdraw Funds\n";
        cout << "4. Transfer Funds\n";
        cout << "5. Display Account Information\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter account holder's name: ";
                cin.ignore(); // To clear the newline from the buffer
                getline(cin, name);
                cout << "Enter initial deposit: ";
                cin >> amount;
                bank.createAccount(name, amount);
                break;
            case 2:
                cout << "Enter account number: ";
                cin >> accNum;
                cout << "Enter deposit amount: ";
                cin >> amount;
                bank.depositToAccount(accNum, amount);
                break;
            case 3:
                cout << "Enter account number: ";
                cin >> accNum;
                cout << "Enter withdrawal amount: ";
                cin >> amount;
                bank.withdrawFromAccount(accNum, amount);
                break;
            case 4:
                cout << "Enter sender account number: ";
                cin >> senderAccNum;
                cout << "Enter receiver account number: ";
                cin >> receiverAccNum;
                cout << "Enter transfer amount: ";
                cin >> amount;
                bank.transferBetweenAccounts(senderAccNum, receiverAccNum, amount);
                break;
            case 5:
                cout << "Enter account number: ";
                cin >> accNum;
                bank.displayAccount(accNum);
                break;
            case 6:
                cout << "Exiting the system.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
