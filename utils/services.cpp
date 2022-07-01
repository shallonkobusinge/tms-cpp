//
// Created by kobsh on 01/07/2022.
//

#include "headers.h"
#include "models.cpp"


class TmsService {
public:
    static void createAccount(Account account) {
        ofstream file;
        file.open("accounts.txt", ios::app);
        bool existingAccount = checkIfAccountExists(account.accountNumber);
        if (!existingAccount) {
            file << account.firstName << "  " << account.lastName << "  " << account.email << "  "
                 << account.accountNumber << "  " << account.accountPassCode << "  " << endl;
            file.close();
            cout << "Account for  " << account.firstName << " " << account.lastName << " created successfully" << endl;
        } else {
            cout << "Account already exists" << endl;
        }
    };

    static void depositAmount() {
        cout << "Depositing amount..." << endl;
    };

    static void withDrawAmount() {
        cout << "Withdrawing amount..." << endl;
    };

    static void closeAccount() {
        cout << "Closing account..." << endl;
    };

    static void getAccountDetailsByName(string accountNumber) {
        ifstream file("accounts.txt");
        string line;
        bool found = false;
        while (getline(file, line) && !found) {
            if (line.find(accountNumber) != string::npos) {
                found = true;
                cout << line << endl;
            }
        }
        if (!found) {
            cout << "Account line not found" << endl;
        }
    };

    static void updateAccount() {
        cout << "Updating account..." << endl;
    };

    static vector<Account> returnAllAccounts() {
        vector<Account> accounts;
        ifstream file("accounts.txt");
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            Account account = getSingleAccount(line);
            accounts.push_back(account);
        }
        return accounts;
    };

    static Account getSingleAccount(const string &line) {
        stringstream ss(line);
        Account account;
        int i = 0;
        for (string rowElement; ss >> rowElement;) {
            if (reinterpret_cast<const char *>(rowElement[rowElement.length() - 1]) == "")
                rowElement.pop_back();
            if (i == 0) account.firstName = rowElement;
            else if (i == 1) account.lastName = rowElement;
            else if (i == 2) account.email = rowElement;
            else if (i == 3) account.accountNumber = stoi(rowElement);
            else if (i == 4) account.accountPassCode = rowElement;
            i++;
        }
        return account;
    }


    static bool checkIfAccountExists(int accountNumber) {
        vector<Account> accounts = returnAllAccounts();
        for (int i = 0; i < accounts.size(); i++) {
            if (accounts[i].accountNumber == accountNumber) {
                return true;
            }
        }
        return false;
    }

    static Account findByAccountNumber(string accountNumber) {
        vector<Account> accounts = returnAllAccounts();
        Account account;
        for (int i = 0; i < accounts.size(); i++) {
            if (accounts[i].accountNumber == stoi( accountNumber )|| accounts[i].accountPassCode == accountNumber) {
                account = accounts[i];
            } else {
                cout << "Account not found" << endl;
            }
        }
        return account;
    };
    static Account removeAccount(int accountNumber) {
        vector<Account> accounts = returnAllAccounts();
        Account account;
        for (int i = 0; i < accounts.size(); i++) {
            if (accounts[i].accountNumber == accountNumber) {
                account = accounts[i];
                accounts.erase(accounts.begin() + i);
            } else {
                cout << "Account not found" << endl;
            }
        }
        return account;
    };
    static void deleteAccountFromAFile(string accountPassCode) {
        ofstream temp;
        temp.open("temp.txt");
        ifstream file("accounts.txt");
        string line;
        while (getline(file, line)) {
            if (line.find(accountPassCode) != string::npos) {
                cout <<"the one" <<line << endl;
            } else{
                temp<<line<<endl;
            }
        }
        file.close();
        temp.close();
        remove("accounts.txt");
        rename("temp.txt","accounts.txt");
    };
    static Account findAccountByAccountNumberFromAFile(int accountNumber){
        Account account;
        ifstream file("accounts.txt");
        string line;
        while (getline(file, line)) {
            if (line.find(to_string(accountNumber)) != string::npos) {
                account = getSingleAccount(line);
            }
        }
        return account;
    }
    static Account updateAccount(string accountNumber,Account newBody) {

    Account account =  findByAccountNumber(accountNumber);
        ofstream temp;
        temp.open("temp.txt");
        ifstream file("accounts.txt");
        string line;
        while (getline(file, line)) {
            if (line.find(accountNumber) != string::npos) {
                cout <<"the one" <<line << endl;
            } else{
                temp<<line<<endl;
            }

        }
        temp<< newBody.firstName << "  " << newBody.lastName << "  " << newBody.email << "  "
            << account.accountNumber << "  " << account.accountPassCode << "  " << endl;
        file.close();
        temp.close();
        remove("accounts.txt");
        rename("temp.txt","accounts.txt");
        return account;

    };
    static Transaction depositOrWithDrawAmount(int accountNumber, double amount, bool isDeposit) {
        bool account = checkIfAccountExists(accountNumber);
        Account existingAccount = findAccountByAccountNumberFromAFile(accountNumber);
        ofstream file;
        file.open("transaction.txt", ios::app);
        file<<"         ACCOUNT ID |         AMOUNT |         TYPE "<<endl;
        if(account){
            Transaction transaction;
            if(isDeposit) {
                transaction.setTransactionType("DEPOSIT");
                transaction.balance += amount;
                transaction.setAccountId(existingAccount.accountNumber);
                file <<"         "<< transaction.getTransactionType() << "         " << transaction.balance << "         " << transaction.getAccountId() << endl;

            }else{
                transaction.transactionType = "WITHDRAW";
                transaction.balance -= amount;
                transaction.accountId = existingAccount.accountNumber;
                file << transaction.transactionType << "  " << transaction.balance << "  " << transaction.accountId << endl;
            }
            file.close();
            return transaction;

        }
    };
    static Transaction getSingleTransaction(const string &line){
        stringstream ss(line);
        Transaction transaction;
        int i = 0;

        for (string rowElement; ss >> rowElement;) {
            if (reinterpret_cast<const char *>(rowElement[rowElement.length() - 1]) == "")
                rowElement.pop_back();
            if (i == 0) transaction.transactionType = rowElement;
            else if (i == 1) transaction.balance = stod(rowElement);
            else if (i == 2) transaction.accountId = stoi(rowElement);
            i++;
        }
        return transaction;

    }
    static vector<Transaction> returnAllTransactions() {
        vector<Transaction> transactions;
        ifstream file("transaction.txt");
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            Transaction transaction = getSingleTransaction(line);
            transactions.push_back(transaction);
        }
        return transactions;
    };


};






