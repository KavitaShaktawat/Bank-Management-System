# Bank-Management-System
Bank Management System with User Authentication
This is a C++ console application for managing user authentication and a bank system. The program allows users to register, log in, and perform various banking operations such as creating accounts, depositing money, withdrawing funds, and deleting accounts.

Features
User Authentication:

Register a new user.
Login for existing users with validation.
Persistent storage of user credentials in users.txt.
Bank Management:

Create a new bank account with account number, holder name, and initial balance.
Display details of all accounts.
Deposit money into an account.
Withdraw money from an account (with insufficient funds check).
Delete an account.
Persistent storage of account details in accounts.txt.
Requirements
C++ Compiler: Ensure you have a working C++ compiler (e.g., GCC or MSVC).
Input Files:
users.txt: File to store user credentials.
accounts.txt: File to store bank account details.
How to Run
Clone the repository or download the source code.
Compile the program:
bash
Copy code
g++ -o BankSystem BankSystem.cpp
Run the executable:
bash
Copy code
./BankSystem
Follow the prompts in the console to register, log in, and use the bank management features.
File Details
users.txt: Stores username-password pairs.
accounts.txt: Stores account details in the format:
Copy code
AccountNumber|AccountHolderName|Balance
Example Usage
Register a User:

Enter a new username and password.
Successfully register to log in later.
Login:

Enter username and password.
Gain access to banking operations upon successful login.
Banking Operations:

Create an account with details such as account number, holder name, and initial balance.
View all created accounts.
Deposit or withdraw funds from specific accounts.
Delete accounts if no longer needed.
Future Enhancements
Add encryption for user credentials.
Improve UI for better user experience.
Implement transaction history for accounts.
License
This project is open-source and free to use.
