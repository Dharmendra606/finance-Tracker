#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Transaction {
    string description;
    double amount;
    string type; // "Income" or "Expense"
};

class FinanceTracker {
private:
    vector<Transaction> transactions;

public:
    void addTransaction() {
        Transaction t;
        cout << "Enter description: ";
        cin.ignore(); // to clear the input buffer
        getline(cin, t.description);

        cout << "Enter amount: ";
        cin >> t.amount;

        cout << "Is this Income or Expense? (I/E): ";
        char c;
        cin >> c;

        if (c == 'I' || c == 'i') {
            t.type = "Income";
        } else if (c == 'E' || c == 'e') {
            t.type = "Expense";
            t.amount = -t.amount; // expenses reduce balance
        } else {
            cout << "Invalid type, transaction cancelled.\n";
            return;
        }

        transactions.push_back(t);
        cout << "Transaction added successfully.\n";
    }

    void showTransactions() {
        if (transactions.empty()) {
            cout << "No transactions to show.\n";
            return;
        }

        cout << left << setw(20) << "Description" << setw(10) << "Type" << setw(10) << "Amount" << endl;
        cout << "--------------------------------------------------\n";
        for (auto& t : transactions) {
            cout << left << setw(20) << t.description
                 << setw(10) << t.type
                 << fixed << setprecision(2) << t.amount << endl;
        }
    }

    void showBalance() {
        double balance = 0.0;
        for (auto& t : transactions) {
            balance += t.amount;
        }
        cout << fixed << setprecision(2);
        cout << "Current balance: $" << balance << "\n";
    }
};

int main() {
    FinanceTracker ft;
    int choice;

    do {
        cout << "\n--- Finance Tracker Menu ---\n";
        cout << "1. Add Transaction\n";
        cout << "2. View Transactions\n";
        cout << "3. View Balance\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                ft.addTransaction();
                break;
            case 2:
                ft.showTransactions();
                break;
            case 3:
                ft.showBalance();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
