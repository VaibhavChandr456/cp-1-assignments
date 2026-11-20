#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    int accountNumber;
    string holderName;
    string accountType;
    double balance;
    static int totalAccounts;
    static int activeAccounts;

public:
    BankAccount() {
        accountNumber = 0;
        holderName = "Unknown";
        accountType = "Savings";
        balance = 0.0;
        totalAccounts++;
        activeAccounts++;
    }

    BankAccount(int number, string name, string type, double initialBalance) {
        accountNumber = number;
        holderName = name;
        accountType = type;
        balance = initialBalance;
        totalAccounts++;
        activeAccounts++;
    }

    ~BankAccount() {
        activeAccounts--;
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    double getBalance() const {
        return balance;
    }

    static int getTotalAccounts() {
        return totalAccounts;
    }

    static int getActiveAccounts() {
        return activeAccounts;
    }

    bool deposit(double amount) {
        if (amount <= 0) {
            cout << "Invalid deposit amount.\n";
            return false;
        }
        balance += amount;
        cout << "Deposit successful.\n";
        return true;
    }

    bool withdraw(double amount) {
        if (amount <= 0) {
            cout << "Invalid withdrawal amount.\n";
            return false;
        }
        if (amount > balance) {
            cout << "Insufficient balance.\n";
            return false;
        }
        balance -= amount;
        cout << "Withdrawal successful.\n";
        return true;
    }

    bool transfer(BankAccount &to, double amount) {
        if (this == &to) {
            cout << "Cannot transfer to the same account.\n";
            return false;
        }
        if (amount <= 0) {
            cout << "Invalid transfer amount.\n";
            return false;
        }
        if (amount > balance) {
            cout << "Insufficient balance.\n";
            return false;
        }
        balance -= amount;
        to.balance += amount;
        cout << "Transfer successful.\n";
        return true;
    }

    void display() const {
        cout << "Account Number : " << accountNumber << "\n";
        cout << "Holder Name    : " << holderName << "\n";
        cout << "Account Type   : " << accountType << "\n";
        cout << "Balance        : " << balance << "\n";
    }
};

int BankAccount::totalAccounts = 0;
int BankAccount::activeAccounts = 0;

int findAccount(BankAccount *accounts[], int count, int number) {
    for (int i = 0; i < count; i++) {
        if (accounts[i]->getAccountNumber() == number) {
            return i;
        }
    }
    return -1;
}

int main() {
    const int MAX = 100;
    BankAccount *accounts[MAX];
    int n;

    cout << "How many accounts do you want to create? ";
    cin >> n;
    while (n < 1 || n > MAX) {
        cout << "Enter a number between 1 and " << MAX << ": ";
        cin >> n;
    }

    for (int i = 0; i < n; i++) {
        int number, typeChoice;
        string name, type;
        double balance;

        cout << "\nAccount " << i + 1 << "\n";
        cout << "Account Number: ";
        cin >> number;
        cout << "Holder Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Account Type (1 - Savings, 2 - Current): ";
        cin >> typeChoice;
        type = (typeChoice == 2) ? "Current" : "Savings";
        cout << "Initial Balance: ";
        cin >> balance;
        while (balance < 0) {
            cout << "Balance cannot be negative. Re-enter: ";
            cin >> balance;
        }

        accounts[i] = new BankAccount(number, name, type, balance);
    }

    int choice;
    do {
        cout << "\n1. Deposit\n2. Withdraw\n3. Transfer\n4. Display All Accounts\n";
        cout << "5. Highest Balance Account\n6. Account Counts\n0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int number;
            double amount;
            cout << "Account Number: ";
            cin >> number;
            int index = findAccount(accounts, n, number);
            if (index == -1) {
                cout << "Account not found.\n";
                break;
            }
            cout << "Amount: ";
            cin >> amount;
            accounts[index]->deposit(amount);
            break;
        }
        case 2: {
            int number;
            double amount;
            cout << "Account Number: ";
            cin >> number;
            int index = findAccount(accounts, n, number);
            if (index == -1) {
                cout << "Account not found.\n";
                break;
            }
            cout << "Amount: ";
            cin >> amount;
            accounts[index]->withdraw(amount);
            break;
        }
        case 3: {
            int fromNumber, toNumber;
            double amount;
            cout << "From Account Number: ";
            cin >> fromNumber;
            cout << "To Account Number: ";
            cin >> toNumber;
            int from = findAccount(accounts, n, fromNumber);
            int to = findAccount(accounts, n, toNumber);
            if (from == -1 || to == -1) {
                cout << "Account not found.\n";
                break;
            }
            cout << "Amount: ";
            cin >> amount;
            accounts[from]->transfer(*accounts[to], amount);
            break;
        }
        case 4:
            for (int i = 0; i < n; i++) {
                cout << "\n";
                accounts[i]->display();
            }
            break;
        case 5: {
            int highest = 0;
            for (int i = 1; i < n; i++) {
                if (accounts[i]->getBalance() > accounts[highest]->getBalance()) {
                    highest = i;
                }
            }
            cout << "\nAccount with highest balance:\n";
            accounts[highest]->display();
            break;
        }
        case 6:
            cout << "Total accounts created : " << BankAccount::getTotalAccounts() << "\n";
            cout << "Currently active       : " << BankAccount::getActiveAccounts() << "\n";
            break;
        case 0:
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    for (int i = 0; i < n; i++) {
        delete accounts[i];
    }

    cout << "\nTotal accounts created : " << BankAccount::getTotalAccounts() << "\n";
    cout << "Currently active       : " << BankAccount::getActiveAccounts() << "\n";

    return 0;
}
