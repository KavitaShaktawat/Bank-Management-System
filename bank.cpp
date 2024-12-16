#include <iostream> 
#include <fstream> 
#include <vector>  
#include <iomanip> 
#include <string>  
#include <map>     
using namespace std;

// Class to handle user login and registration
class UserAuth {
    map<string, string> users; // Map to store username and password

    // Method to load users from file
    void loadUsers() {
        ifstream file("users.txt", ios::in);
        string username, password;
        while (file >> username >> password) { 
            users[username] = password;
        }
        file.close();
    }

    // Method to save users to file
    void saveUsers() {
        ofstream file("users.txt", ios::out | ios::trunc);
        for (const auto &user : users) {
            file << user.first << " " << user.second << endl; // Write username and password pairs
        }
        file.close();
    }

public:
    UserAuth() {
        loadUsers(); // Load users during initialization
    }

    ~UserAuth() {
        saveUsers(); // Save users during destruction
    }

    // Method to register a new user
    void registerUser() {
        string username, password;
        cout << "Enter a new username: ";
        cin >> username;
        if (users.find(username) != users.end()) { // Check if username already exists
            cout << "Username already exists. Try a different one.\n";
            return;
        }
        cout << "Enter a new password: ";
        cin >> password;
        users[username] = password; // Add new user to map
        cout << "Registration successful! You can now log in.\n";
    }

    // Method to login an existing user
    bool loginUser() {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        if (users.find(username) != users.end() && users[username] == password) { // Validate credentials
            cout << "Login successful!\n";
            return true;
        }
        cout << "Invalid username or password.\n";
        return false;
    }
};

// Class to represent a single account
class Account {
public:
    string accountNumber; 
    string accountHolderName; 
    double balance; 

    Account() {} // Default constructor

    // Parameterized constructor to initialize account details
    Account(string accNum, string name, double bal) {
        accountNumber = accNum;
        accountHolderName = name;
        balance = bal;
    }

    // Method to display account details
    void display() const {
        cout << left << setw(15) << accountNumber
             << setw(20) << accountHolderName
             << setw(10) << balance << endl;
    }
};

// Class to manage bank operations
class Bank {
    vector<Account> accounts; 

    // Method to save all account details to a file
    void saveToFile() {
        ofstream file("accounts.txt", ios::out | ios::trunc); // Open file in write mode
        for (const auto &acc : accounts) {
            file << acc.accountNumber << "|" << acc.accountHolderName << "|" << acc.balance << endl; // Write account details
        }
        file.close(); // Close the file
    }

    // Method to load account details from a file
    void loadFromFile() {
        accounts.clear();
        ifstream file("accounts.txt", ios::in); 
        string line;
        while (getline(file, line)) { 
            size_t pos1 = line.find('|'); 

            size_t pos2 = line.find('|', pos1 + 1); 

            string accNum = line.substr(0, pos1); 
            string name = line.substr(pos1 + 1, pos2 - pos1 - 1); 
            double bal = stod(line.substr(pos2 + 1)); 

            accounts.emplace_back(accNum, name, bal); 
        }
        file.close(); 
    }

public:
    Bank() {
        loadFromFile(); // Load accounts from file during initialization
    }

    ~Bank() {
        saveToFile(); // Save accounts to file during destruction
    }

    // Method to create a new account
    void createAccount() {
        string accNum, name;
        double bal;
        cout << "Enter Account Number: ";
        cin >> accNum; 
        cout << "Enter Account Holder Name: ";
        cin.ignore(); 
        getline(cin, name); 
        cout << "Enter Initial Balance: ";
        cin >> bal; 
        accounts.emplace_back(accNum, name, bal); 
        cout << "Account created successfully!\n";
    }

    // Method to display all accounts
    void displayAccounts() {
        cout << left << setw(15) << "Account No" << setw(20) << "Account Holder" << setw(10) << "Balance" << endl; // Header
        cout << string(45, '-') << endl; 
        for (const auto &acc : accounts) { 
            acc.display(); 
        }
    }

    // Method to deposit money into an account
    void deposit() {
        string accNum;
        double amount;
        cout << "Enter Account Number: ";
        cin >> accNum; 
        cout << "Enter Amount to Deposit: ";
        cin >> amount; 

        for (auto &acc : accounts) { // Search for the account
            if (acc.accountNumber == accNum) { // Match found
                acc.balance += amount; // Add amount to balance
                cout << "Deposit successful!\n";
                return;
            }
        }
        cout << "Account not found!\n";
    }

    // Method to withdraw money from an account
    void withdraw() {
        string accNum;
        double amount;
        cout << "Enter Account Number: ";
        cin >> accNum; 
        cout << "Enter Amount to Withdraw: ";
        cin >> amount; 

        for (auto &acc : accounts) { // Search for the account
            if (acc.accountNumber == accNum) { 
                if (acc.balance >= amount) { 
                    acc.balance -= amount; 
                    cout << "Withdrawal successful!\n";
                } else {
                    cout << "Insufficient balance!\n";
                }
                return;
            }
        }
        cout << "Account not found!\n";
    }

    // Method to delete an account
    void deleteAccount() {
        string accNum;
        cout << "Enter Account Number to Delete: ";
        cin >> accNum; 

        for (auto it = accounts.begin(); it != accounts.end(); ++it) { // Search for the account
            if (it->accountNumber == accNum) { 
                accounts.erase(it); 
                cout << "Account deleted successfully!\n";
                return;
            }
        }
        cout << "Account not found!\n";
    }
};

int main() {
    UserAuth auth; // Create UserAuth object
    int authChoice;

    // Authentication menu
    while (true) {
        cout << "1. Register\n2. Login\nEnter your choice: ";
        cin >> authChoice;

        if (authChoice == 1) {
            auth.registerUser(); // Register a new user
        } else if (authChoice == 2) {
            if (auth.loginUser()) {
                break; // Proceed if login is successful
            }
        } else {
            cout << "Invalid choice!\n";
            continue;
        }
    }

    Bank bank; // Create Bank object
    int choice; // Store user choice

    do {
        // Display menu options
        cout << "\nBank Management System" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Display All Accounts" << endl;
        cout << "3. Deposit Money" << endl;
        cout << "4. Withdraw Money" << endl;
        cout << "5. Delete Account" << endl;
        cout << "6. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bank.createAccount();
                break;
            case 2:
                bank.displayAccounts();
                break;
            case 3:
                bank.deposit();
                break;
            case 4:
                bank.withdraw();
                break;
            case 5:
                bank.deleteAccount();
                break;
            case 6:
                cout << "Exiting the system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}