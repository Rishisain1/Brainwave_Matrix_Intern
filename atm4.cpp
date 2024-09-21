#include <iostream>
#include <string>
using namespace std;
const int MAX_TRANSACTIONS = 100;

struct Transaction {
    string type;
    double amount;
};

struct Account {
    string pin;
    double balance;
    Transaction transactions[MAX_TRANSACTIONS];
    int transactionCount;
};

void displayMenu() {
    cout<<"* * * * * * * * * * WELCOME * * * * * * * * * * \n";
    cout << "1. Check Balance\n";
    cout << "2. Deposit Money\n";
    cout << "3. Withdraw Money\n";
    cout << "4. View Transaction History\n";
    cout << "5. Exit\n";
    cout<<"* * * * * * * * * * * * * * * * * * * * * * * * \n";
}

bool authenticate(Account& account, const string& inputPin) {
    return inputPin == account.pin;
}

void deposit(Account& account, double amount) {
    if (amount > 0) {
        account.balance += amount;
        if (account.transactionCount < MAX_TRANSACTIONS) {
            account.transactions[account.transactionCount++] = {"Deposit", amount};
        }
        cout << "Rs." << amount << " deposited successfully.\n";
    } else {
        cout << "Invalid amount.\n";
    }
}

bool withdraw(Account& account, double amount) {
    if (amount > 0 && amount <= account.balance) {
        account.balance -= amount;
        if (account.transactionCount < MAX_TRANSACTIONS) {
            account.transactions[account.transactionCount++] = {"Withdrawal", amount};
        }
        cout << "Rs." << amount << " withdrawn successfully.\n";
        return true;
    } else if (amount > account.balance) {
        cout << "Insufficient funds.\n";
    } else {
        cout << "Invalid amount.\n";
    }
    return false;
}

void printTransactions(const Account& account) {
    cout << "Transaction History:\n";
    for (int i = 0; i < account.transactionCount; ++i) {
        cout << account.transactions[i].type << ": Rs." << account.transactions[i].amount << "\n";
    }
}

int main() {
    Account userAccount;
    userAccount.balance = 0.0;
    userAccount.transactionCount = 0;

    cout << "Set your PIN: ";
    cin >> userAccount.pin;

    string inputPin;
    cout << "Enter your PIN to access the ATM: ";
    cin >> inputPin;

    if (!authenticate(userAccount, inputPin)) {
        cout << "Incorrect PIN. Access denied.\n";
        return 1;
    }

    int choice;
    while (true) {
        displayMenu();
        cout << "Select an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Your current balance is: Rs." << userAccount.balance << "\n";
                break;
            case 2: {
                double amount;
                cout << "Enter amount to deposit: Rs.";
                cin >> amount;
                deposit(userAccount, amount);
                break;
            }
            case 3: {
                double amount;
                cout << "Enter amount to withdraw: Rs.";
                cin >> amount;
                withdraw(userAccount, amount);
                break;
            }
            case 4:
                printTransactions(userAccount);
                break;
            case 5:
                cout << "Thank you for using the ATM. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
        cout << "\n";
    }

    return 0;
}
