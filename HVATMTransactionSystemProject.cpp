#include <iostream>
#include <string>
#include<vector>
using namespace std;
// Forward declarations of classes
class Bank;
class DebitCard;
class Customer;
class Account;
class CurrentAccount;
class SavingsAccount;
class ATMInfo;
class ATMTransaction;
class Withdrawal;
class Query;
class Transfer;
class PINValidation;

// Bank class
class Bank {
public:
    string code;
    string address;

    void manages() {
        cout << "Bank with code " << code << " manages its operations." <<endl;
    }
    void maintains() {
        cout << "Bank with code " << code << " maintains its infrastructure." <<endl;
    }
};
// Account class
class Account {
public:
    int accountNo;
    double balance;
    vector<string> transactionHistory;

    Account(int no, double bal) : accountNo(no), balance(bal) {}

    bool debit(double amount) {
        if (balance >= amount) {
            balance -= amount;
            return true; // Debit successful
        }
        return false; // Insufficient balance for debit
    }

    void addTransaction(const string& transaction) {
        transactionHistory.push_back(transaction);
    }

    // Credit operation
    void credit(double amount) {
        balance += amount;
    }

    virtual string getType() const {
        return "Generic Account";
    }

    vector<string> getTransactionHistory() const {
        return transactionHistory;
    }
};

// CurrentAccount class (child class of Account)
class CurrentAccount : public Account {
public:
    int accountNo;
    double balance;
    CurrentAccount(int accno, double bal) : Account(accno,bal){}
    void debit(double amount) {
        if (balance >= amount) {
            balance -= amount;
            cout << "Debit of $" << amount << " processed in Current Account." << endl;
            cout << "Remaining balance: $" << balance << endl;
        } else {
            cout << "Insufficient balance for debit." << endl;
        }
    }
    void credit(double amount) {
        balance += amount;
        cout << "Credit of $" << amount << " processed in Current Account." << endl;
        cout << "New balance: $" << balance << endl;
    }
    string getType() const override {
        return "Current Account";
    }
};
// SavingsAccount class (child class of Account)
class SavingsAccount : public Account {
public:
    int accountNo;
    double balance;
    SavingsAccount(int accno, double bal) : Account(accno, bal) {}
    void debit(double amount) {
        if (balance >= amount) {
            balance -= amount;
            cout << "Debit of $" << amount << " processed in Savings Account." << endl;
            cout << "Remaining balance: $" << balance << endl;
        } else {
            cout << "Insufficient balance for debit." << endl;
        }
    }
    void credit(double amount) {
        balance += amount;
        cout << "Credit of $" << amount << " processed in Savings Account." << endl;
        cout << "New balance: $" << balance << endl;
    }
    string getType() const override {
        return "Savings Account";
    }
};
class DebitCard {
public:
    string cardNo;

    DebitCard(const string& cardNumber)
        : cardNo(cardNumber) {}

    void access() {
        cout << "Accessing the Debit Card with card number: " << cardNo << endl;
    }
};
// Customer class
class Customer {
public:
    string name;
    string address;
    string DOB;
    string phoneNumber;
    string email;
    Account* account;  // Pointer to the customer's account (either SavingsAccount or CurrentAccount)
    DebitCard* debitCard; // Pointer to the customer's debit card

    Customer(const string& customerName, const string& customerAddress, const string& customerDOB, const string& customerPhoneNumber, const string& customerEmail)
        : name(customerName), address(customerAddress), DOB(customerDOB), phoneNumber(customerPhoneNumber), email(customerEmail), account(nullptr), debitCard(nullptr) {}

    // Function to link a customer to their account (either SavingsAccount or CurrentAccount)
    void owns(Account* customerAccount) {
        account = customerAccount;
    }

    // Function to link a customer to their debit card
    void hasDebitCard(DebitCard* card) {
        debitCard = card;
    }

    // Function to display customer information
    void displayInfo() {
        cout << "Customer Name: " << name << endl;
        cout << "Address: " << address << endl;
        cout << "Date of Birth: " << DOB << endl;
        cout << "Phone Number: " << phoneNumber << endl;
        cout << "Email: " << email << endl;
        if (account != nullptr) {
            cout << "Account Type: " << account->getType() << endl;
            cout << "Account Number: " << account->accountNo << endl;
            cout << "Account Balance: $" << account->balance << endl;
        }
        if (debitCard != nullptr) {
            cout << "Debit Card Number: " << debitCard->cardNo << endl;
        }
    }
};


// ATMInfo class
class ATMInfo {
public:
    string location;
    string managedBy;

    ATMInfo(const string& atmLocation, const string& manager)
        : location(atmLocation), managedBy(manager) {}

    void identifies() {
        cout << "ATM located at " << location << " is managed by " << managedBy << "." << endl;
    }

    void transactions() {
        cout << "ATM at " << location << " supports various transactions." << endl;
    }
};


// ATMTransaction class
class ATMTransaction {
public:
    int transactionID;
    string date;
    string type;

    ATMTransaction(int id, const string& transactionDate, const string& transactionType)
        : transactionID(id), date(transactionDate), type(transactionType) {}

    void modifies() {
        cout << "ATM Transaction with ID " << transactionID << " has been modified." << endl;
    }
};

// Withdrawal class (child class of ATMTransaction)
class Withdrawal : public ATMTransaction {
public:
    double amount;
    Account* account;
     Withdrawal(int id, const string& date, double withdrawalAmount, Account* customerAccount)
        : ATMTransaction(id, date, "Withdrawal"), amount(withdrawalAmount), account(customerAccount) {}

    void withdraw() {
        if (account != nullptr) {
            if (account->balance >= amount) {
                account->balance -= amount; // Deduct the amount from the account balance
                cout << "Withdrawal of $" << amount << " on " << date << " processed." << endl;
                cout << "Remaining balance: $" << account->balance << endl;
            } else {
                cout << "Insufficient balance for withdrawal." << endl;
            }
        } else {
            cout << "Account not found." << endl;
        }
    }
};


// Query class (child class of ATMTransaction)
// Query class (child class of ATMTransaction)
class Query : public ATMTransaction {
public:
    int queryID;
    string type;
    Account* account;

    Query(int id, const string& date, const string& queryType)
        : ATMTransaction(id, date, "Query"), queryID(id), type(queryType) {}

    void processing() {
        // Implement query-specific processing logic based on the query type
        if (type == "Balance") {
            // Example: Display account balance
            cout << "Query for account balance on " << date << ":" << endl;
            cout << "Account balance: $" << getAccountBalance() << endl;
        } else if (type == "TransactionHistory") {
            // Example: Display transaction history
            cout << "Query for transaction history on " << date << ":" << endl;
            displayTransactionHistory();
        } else {
            cout << "Invalid query type." << endl;
        }
    }

    // Example method to retrieve account balance 
    double getAccountBalance() const {
    if (account != nullptr) {
        return account->balance;
    } else {
        cout << "Account not found." << endl;
        return 0.0;  
    }
}

    // Example method to display transaction history (replace with actual logic)
    void displayTransactionHistory() const {
    if (account != nullptr) {
        cout << "Transaction History for Account " << account->accountNo << ":" << endl;
        // Assuming the account maintains a list of transactions (replace with your actual data structure)
        const vector<string>& transactionHistory = account->getTransactionHistory();

        if (!transactionHistory.empty()) {
            for (const string& transaction : transactionHistory) {
                cout << transaction << endl;
            }
        } else {
            cout << "No transaction history available for this account." << endl;
        }
    } else {
        cout << "Account not found." << endl;
    }
}
};


// Transfer class (child class of ATMTransaction)
class Transfer : public ATMTransaction {
public:
    double amount;
    int sourceAccountNo;
    int destinationAccountNo;

    Transfer(int transactionID, const string& date, const string& type, double transferAmount, int sourceAccount, int destinationAccount)
        : ATMTransaction(transactionID, date, type), amount(transferAmount), sourceAccountNo(sourceAccount), destinationAccountNo(destinationAccount) {}

    void transfer(Account& sourceAccount, Account& destinationAccount) {
        if (sourceAccount.debit(amount)) {
            destinationAccount.credit(amount);
            cout << "Transfer of $" << amount << " from Account " << sourceAccountNo << " to Account " << destinationAccountNo << " processed." << endl;
        } else {
            cout << "Transfer failed due to insufficient balance in Account " << sourceAccountNo << "." << endl;
        }
    }
};

// PINValidation class (child class of ATMTransaction)
class PINValidation : public ATMTransaction{
public:
    int oldPIN;
    int newPIN;

    PINValidation(int oldPin, int newPin)
        : ATMTransaction(0, "default_date", "PINValidation"), oldPIN(oldPin), newPIN(newPin) {}

    bool changePIN(int currentPIN) {
        if (currentPIN == oldPIN) {
            oldPIN = newPIN;
            cout << "PIN changed successfully." << endl;
            return true;
        } else {
            cout << "Incorrect old PIN. PIN change failed." << endl;
            return false;
        }
    }
};


int main() {
    // Get customer information from user input
    int oldPIN;
    cout << "Enter customer name: ";
    string customerName;
    getline(cin, customerName);

    cout << "Enter customer address: ";
    string customerAddress;
    getline(cin, customerAddress);

    cout << "Enter customer date of birth (YYYY-MM-DD): ";
    string customerDOB;
    getline(cin, customerDOB);

    cout << "Enter customer phone number: ";
    string customerPhoneNumber;
    getline(cin, customerPhoneNumber);

    cout << "Enter customer email: ";
    string customerEmail;
    getline(cin, customerEmail);

    // Create a Customer instance
    Customer customer(customerName, customerAddress, customerDOB, customerPhoneNumber, customerEmail);

    // Get debit card number from user input
    cout << "Enter debit card number: ";
    string debitCardNumber;
    cin.ignore(); // Clear the newline character from previous input
    getline(cin, debitCardNumber);

    DebitCard customerDebitCard(debitCardNumber);
    customer.hasDebitCard(&customerDebitCard);

    // Create account variables outside the if-else block
    SavingsAccount customerSavingsAccount(0, 0.0);
    CurrentAccount customerCurrentAccount(0, 0.0);

    cout << "Choose the type of account to create:" << endl;
    cout << "1. Savings Account" << endl;
    cout << "2. Current Account" << endl;
    cout << "Enter your choice (1 or 2): ";

    int accountChoice;
    cin >> accountChoice;

    if (accountChoice == 1) {
        // Create and link a SavingsAccount to the customer
        cout << "Enter savings account number: ";
        int savingsAccountNumber;
        cin >> savingsAccountNumber;

        cout << "Enter initial savings account balance: $";
        double initialSavingsBalance;
        cin >> initialSavingsBalance;

        customerSavingsAccount = SavingsAccount(savingsAccountNumber, initialSavingsBalance);
        customer.owns(&customerSavingsAccount);
    } else if (accountChoice == 2) {
        // Create and link a CurrentAccount to the customer
        cout << "Enter current account number: ";
        int currentAccountNumber;
        cin >> currentAccountNumber;

        cout << "Enter initial current account balance: $";
        double initialCurrentBalance;
        cin >> initialCurrentBalance;

        customerCurrentAccount = CurrentAccount(currentAccountNumber, initialCurrentBalance);
        customer.owns(&customerCurrentAccount);
    } else {
        cout << "Invalid choice. Exiting." << endl;
        return 1;
    }

    // Main menu loop
    while (true) {
        int choice;
        cout << "\nMain Menu:" << endl;
        cout << "1. Withdrawal" << endl;
        cout << "2. Transfer" << endl;
        cout << "3. Change PIN" << endl;
        cout << "4. Query Transaction History" << endl;
        cout << "5. Display Customer Info" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

       if (choice == 1) {
        // Withdrawal
        cout << "Enter the withdrawal amount: $";
        double withdrawalAmount;
        cin >> withdrawalAmount;

        Withdrawal withdrawal(1, "2023-10-09", withdrawalAmount, &customerSavingsAccount);
        withdrawal.withdraw();

        // Add the withdrawal transaction to the account's transaction history
        customerSavingsAccount.addTransaction("2023-10-09: Withdrawal $" + to_string(withdrawalAmount));
    } else if (choice == 2) {
        // Transfer
        cout << "Enter the transfer amount: $";
        double transferAmount;
        cin >> transferAmount;

        cout << "Enter the destination account number: ";
        int destinationAccountNo;
        cin >> destinationAccountNo;

        Transfer transfer(2, "2023-10-09", "Transfer", transferAmount, customerSavingsAccount.accountNo, destinationAccountNo);
        transfer.transfer(customerSavingsAccount, customerSavingsAccount); // For demonstration, transfer within the same account
    } else if (choice == 3) {
        // Change PIN
        cout << "Enter your current PIN: ";
        cin >> oldPIN;

        cout << "Enter your new PIN: ";
        int newPIN;
        cin >> newPIN;

        PINValidation pinValidation(oldPIN, newPIN);
        pinValidation.changePIN(oldPIN);
    } else if (choice == 4) {
        // Query Transaction History
        Query query(3, "2023-10-09", "TransactionHistory");
        query.processing();
    } else if (choice == 5) {
        // Display Customer Info
        customer.displayInfo();
    } else if (choice == 6) {
        // Exit
        cout << "Exiting ATM Transaction System." << endl;
        return 0;
    } else {
        cout << "Invalid choice. Please enter a valid option." << endl;
    }
    }
    return 0;
}
