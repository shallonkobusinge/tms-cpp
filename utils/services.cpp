//
// Created by kobsh on 01/07/2022.
//

#include "headers.h"
#include "models.cpp"


class TmsService{
    public:
    static void createAccount(Account account){
        ofstream file;
        file.open("accounts.txt", ios::app);
        file << account.firstName << "," << account.lastName << "," << account.email << "," << account.accountPassCode << "," << account.accountNumber << "," << account.address << endl;
        file.close();
    }

    static void createTransaction(Transaction transaction){
        ofstream file;
        file.open("transactions.txt", ios::app);
        file << transaction.accountId << "," << transaction.transactionType << "," << transaction.balance << endl;
        file.close();
    }

    static vector<Account> getAccounts(){
        vector<Account> accounts;
        ifstream file;
        file.open("accounts.txt");
        string line;
        while(getline(file, line)){
            stringstream ss(line);
            string firstName, lastName, email, accountPassCode, accountNumber, address;
            getline(ss, firstName, ',');
            getline(ss, lastName, ',');
            getline(ss, email, ',');
            getline(ss, accountPassCode, ',');
            getline(ss, accountNumber, ',');
            getline(ss, address, ',');
            Account account;
            account.firstName = firstName;
            account.lastName = lastName;
            account.email = email;
            account.accountPassCode = accountPassCode;
            account.accountNumber = stoi(accountNumber);
            account.address = address;
            accounts.push_back(account);
        }
        file.close();
        return accounts;
    }

    static vector<Transaction> getTransactions(){
        vector<Transaction> transactions;
        ifstream file;
        file.open("transactions.txt");
        string line;
        while(getline(file, line)) {
            stringstream ss(line);
            string accountId, transactionType, balance;

            getline(ss, accountId, ',');
        }
        }

};



