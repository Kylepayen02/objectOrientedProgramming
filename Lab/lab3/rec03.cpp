
// Provided
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

//
// Task 1: The Account struct. Call it AccountS
//
struct AccountS{
    string accountName;
    int accountNumber;
};

vector<AccountS> task1a(ifstream& ifs){

    vector<AccountS> accountList;
    string name;
    int number;
    if (!ifs){
        cout << "The file could not be opened";
        exit(1);
    }

    while (ifs >> name >> number){
        AccountS myAccount;
        myAccount.accountName = name;
        myAccount.accountNumber = number;
        accountList.push_back(myAccount);
    }

    for (AccountS account : accountList){
        cout << account.accountName << " " << account.accountNumber << endl;
    }

    return accountList;
}

void task1b(ifstream& ifs, vector<AccountS>& accountList){
    accountList.clear();
    ifs.open("accounts.txt");
    string name;
    int number;

    if (!ifs){
        cout << "The file could not be opened";
        exit(1);
    }

    while (ifs >> name >> number){
        AccountS myAccount{name, number};
        accountList.push_back(myAccount);
    }

    for (AccountS account : accountList){
        cout << account.accountName << " " << account.accountNumber << endl;
    }

}


//
// Task 2: The Account class. Call it AccountC
//
class AccountC;


vector<AccountC> task2a(ifstream& ifs);



void task2b(ifstream& ifs, vector<AccountC>& accountList);


// 2.c: AccountC output operator, reimplemented as a friend.

void task2c(ifstream& ifs, vector<AccountC>& accountList);

// 2.d: Redo input but pass temp instances to the push_back method

void task2d(ifstream& ifs, vector<AccountC>& accountList);

// 2.e: Repeat the filling of the vector using emplace_back and again display the contents.

void task2e(ifstream& ifs, vector<AccountC>& accountList);

//
// Task 3
//
// Transaction class definition

class Transactions{
public:
    void display(){
        cout << transactionType << " " << transationAmount << endl;
    }


    string transactionType;
    int transationAmount;
};


// Account class definition

class AccountC {

public:

    vector<Transactions> transactionHistory;
    int balance;

    friend ostream& operator<<(ostream& os, const AccountC& somebody); // Task 2.c

    AccountC(const string& theName, int theNumber):accountName(theName), accountNumber(theNumber) {}

// Task 2.c
// Getters

    string getName() const {
        return accountName;
    }
    int getNumber() {
        return accountNumber;
    }

    void deposit(int amount){
        Transactions aTransaction;
        aTransaction.transactionType = "deposit";
        aTransaction.transationAmount = amount;
        transactionHistory.push_back(aTransaction);
        balance += amount;
    }

    void withdraw(int amount){
        Transactions aTransaction;
        aTransaction.transactionType = "withdraw";
        aTransaction.transationAmount = amount;
        transactionHistory.push_back(aTransaction);
        balance -= amount;
    }

private:
    string accountName;
    int accountNumber;


};

// 2.b: AccountC output operator, not a friend. && 3.e

ostream& operator<<(ostream& os, const AccountC& somebody) {
    os
            << "Account "
            << somebody.accountName
            << " "
            << somebody.accountNumber
            << endl;

    for (const Transactions& transaction : somebody.transactionHistory){
       os  << transaction.transactionType << " " << transaction.transationAmount << endl;
    };

    os << "Balance: " << somebody.balance << endl;

    return os;
}

//

void task3(ifstream& ifs, vector<AccountC>& accountList);


//
// Task 4
//
// Transaction class definition with embedded Account class



int main() {

    //
    // Task 1: account as struct
    //
    //      1a. Fill vector of account structs from file

    cout << "Task1a:\n";
    cout << "Filling vector of struct objects, define a local struct instance "
         << " and set fields explicitly:\n";

    ifstream file("accounts.txt");
    ifstream file2("transactions.txt");

    vector<AccountS> accountList = task1a(file);

    file.close();
    file.clear();

    cout << "\n";
    //      1b
    cout << "Task1b:\n";
    cout << "Filling vector of struct objects, using {} initialization:\n";

    task1b(file, accountList);
    file.close();
    file.clear();

    //==================================
    //
    // Task 2: account as class
    //

    //      2a
    cout << "==============\n";
    cout << "\nTask2a:";
    cout << "\nFilling vector of class objects, using local class object:\n";

    vector<AccountC> accountListC = task2a(file);

    file.close();
    file.clear();


    cout << "---\n";
    cout << "\nTask2b:\n";
    cout << "output using output operator with getters\n";

    task2b(file, accountListC);

    file.close();
    file.clear();

    cout << "\nTask2c:\n";
    cout << "output using output operator as friend without getters\n";
    // Note code here will be same as above.

    task2c(file, accountListC);

    file.close();
    file.clear();

    cout << "\nTask2d:\n";
    cout << "Filling vector of class objects, using temporary class object:\n";

    task2d(file, accountListC);

    file.close();
    file.clear();

    cout << "\nTask2e:\n";
    cout << "\nFilling vector of class objects, using emplace_back:\n";

    task2e(file, accountListC);

    file.close();

    // Task 3
    cout << "==============\n";
    cout << "\nTask 3:\n\nAccounts and Transaction:\n";

    task3(file2, accountListC);


    // Task 4
    cout << "==============\n";
    cout << "\nTask 4:\n\nAccounts and Transaction:\n"
         << "Account class is nested inside Transaction class.\n";

}

vector<AccountC> task2a(ifstream& ifs){
    ifs.open("accounts.txt");
    vector<AccountC> accountList;
    string name;
    int number;

    if (!ifs){
        cout << "The file could not be opened";
        exit(1);
    }

    while (ifs >> name >> number){
        AccountC myAccount{name, number};
        accountList.push_back(myAccount);
    }

    for (AccountC account: accountList){
        cout << account.getName() << " " << account.getNumber() << endl;
    }

    return accountList;

}

void task2b(ifstream& ifs, vector<AccountC>& accountList){
    ifs.open("accounts.txt");
    accountList.clear();
    string name;
    int number;

    if (!ifs){
        cout << "The file could not be opened";
        exit(1);
    }

    while (ifs >> name >> number){
        accountList.push_back(AccountC(name,number));
    }

    for (const AccountC& account: accountList){
        cout << account << endl;
    }


}

void task2c(ifstream& ifs, vector<AccountC>& accountList){
    ifs.open("accounts.txt");
    accountList.clear();
    string name;
    int number;

    if (!ifs){
        cout << "The file could not be opened";
        exit(1);
    }

    while (ifs >> name >> number){
        AccountC myAccount{name, number};
        accountList.push_back(myAccount);
    }

    for (AccountC account: accountList){
        cout << account << endl;
    }


}

void task2d(ifstream& ifs, vector<AccountC>& accountList){
    ifs.open("accounts.txt");
    accountList.clear();
    string name;
    int number;

    if (!ifs){
        cout << "The file could not be opened";
        exit(1);
    }

    while (ifs >> name >> number){
        accountList.push_back(AccountC(name, number));
    }

    for (AccountC account: accountList){
        cout << account << endl;
    }


}

void task2e(ifstream& ifs, vector<AccountC>& accountList){
    ifs.open("accounts.txt");
    accountList.clear();
    string name;
    int number;

    if (!ifs){
        cout << "The file could not be opened";
        exit(1);
    }

    while (ifs >> name >> number){
        accountList.emplace_back(name, number);
    }

    for (AccountC account: accountList){
        cout << account << endl;
    }


}

void task3(ifstream& ifs, vector<AccountC>& accountList) {
    accountList.clear();
    string action;
    string accName;
    int accNumber;
    int transactionAmount;

    while(ifs >> action){
        if(action == "Account"){
            ifs >> accName >> accNumber;
            accountList.emplace_back(accName, accNumber);
        }
        else if(action == "Deposit"){
            ifs >> accNumber >> transactionAmount;
            for(AccountC& account : accountList){
                if(account.getNumber() == accNumber){
                    account.deposit(transactionAmount);
                }
            }
        }
        else{
            ifs >> accNumber >> transactionAmount;
            for(AccountC& account : accountList){
                if(account.getNumber() == accNumber){
                    if(account.balance - transactionAmount > 0){
                        account.withdraw(transactionAmount);
                    }
                    else{
                        cerr << "You cannot withdraw this much, try again." << endl;
                    }
                }
            }
        }
    }

    for (const AccountC& account: accountList){
        cout << account << endl;
    }

}


