//
// Created by kobsh on 01/07/2022.
//

#include "headers.h"
#include "models.cpp"


class TmsService{
public:
    static void createAccount(Account account){
    ofstream file;
    file.open("accounts.txt",ios::app);
    file << " FIRSTNAME : "<< account.firstName << " LASTNAME : " << account.lastName << " EMAIL :  " << account.email << " ACCOUNT NUMBER : "<< account.accountNumber << " ACCOUNT PASSCODE : "<< account.accountPassCode << endl;
    file.close();
    cout<< "Account for  "<<account.firstName <<" " <<account.lastName<<" created successfully" << endl;

    };
    static void depositAmount(){
        cout<<"Depositing amount..."<<endl;
    };
    static void withDrawAmount(){
        cout<<"Withdrawing amount..."<<endl;
    };
    static void closeAccount(){
        cout<<"Closing account..."<<endl;
    };
    static void getAccountDetailsByName(string accountNumber){
        ifstream file("accounts.txt");
        string line;
        bool found = false;
        while (getline(file,line) && !found){
            if(line.find(accountNumber) != string::npos){
                found = true;
                cout<<line<<endl;
            }
        }
        if(!found){
            cout<<"Account not found"<<endl;
        }
    };
    static void updateAccount(){
        cout<<"Updating account..."<<endl;
    };
    static void getAllAccounts(){
        cout<<"Getting all accounts..."<<endl;
//        vector<Account> accounts;
//        return accounts;
    };


};



