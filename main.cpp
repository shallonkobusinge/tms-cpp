#include "utils/headers.h"
#include "utils/models.cpp"
#include "utils/services.cpp"

void newAccountCreation(){
    int number;
    Account account;
    cout<<" HOW MANY ACCOUNTS DO YOU WANT TO CREATE "<<endl;
    cin>>number;
    for(int i=1; i<=number; i++){
        cout<<"DETAILS FOR THE "<<i<<"  ACCOUNT "<<endl;
        cout<<"Enter first name: "<<endl;
        cin>>account.firstName;
        cout<<"Enter last name: "<<endl;
        cin>>account.lastName;
        cout<<"Enter email: "<<endl;
        cin>>account.email;
        cout<<"Enter account number: "<<endl;
        cin>>account.accountNumber;
        cout<<"Enter account pass code: "<<endl;
        cin>>account.accountPassCode;
        TmsService::createAccount(account);
    }
}

void findByAccountNumber(){
    string accountNumber;
    cout<<"Enter account number: "<<endl;
    cin>>accountNumber;
    TmsService::getAccountDetailsByName(accountNumber);
}

void displayAccounts(vector<Account> account){
    cout<<"ACCOUNT DETAILS"<<endl;
    cout<<"     FIRST NAME       |     LAST NAME       |     EMAIL       |     ACOUNT NUMBER       |     ACCOUNT PASS CODE       |"<<endl;
    cout<<"----------------------------------------------------------------------------------------------------------------------"<<endl;
    for(int i=0; i<account.size(); i++){
    cout<<"       "<<account[i].firstName<<"                "<<account[i].lastName<<"               "<<account[i].email<<"                "<<account[i].accountNumber<<"           "<<account[i].accountPassCode<<"       "<<endl;
    }
    cout<<"----------------------------------------------------------------------------------------------------------------------"<<endl;
}

void displaySingleAccount(){
    string number;
    cout<<"Enter account number: "<<endl;
    getline(cin,number);
    Account account = TmsService::findByAccountNumber(number);
    cout<<"     FIRST NAME       |     LAST NAME       |     EMAIL       |     ACOUNT NUMBER       |     ACCOUNT PASS CODE       |"<<endl;
    cout<<"----------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"       "<<account.firstName<<"                "<<account.lastName<<"               "<<account.email<<"                "<<account.accountNumber<<"           "<<account.accountPassCode<<"       "<<endl;
    cout<<"----------------------------------------------------------------------------------------------------------------------"<<endl;
}

void closeAccount(){
    int accountNumber;
    cout<<"Enter account number: "<<endl;
    cin>>accountNumber;
    Account account = TmsService::removeAccount(accountNumber);
    cout<<"Account for "<<account.firstName<<" "<<account.lastName<<" closed successfully"<<endl;
}

void deleteFromFile(){
    string accountNumber;
    cout<<"Enter account number: "<<endl;
    cin>>accountNumber;
    TmsService::deleteAccountFromAFile(accountNumber);
}

void modifyAccount(){
    string accountNumber;
    cout<<" Enter the account number that you want to update "<<endl;
    cin>>accountNumber;
    cout<<" Enter the new details "<<endl;
    Account account;
    cout<<"Enter first name: "<<endl;
    cin>>account.firstName;
    cout<<"Enter last name: "<<endl;
    cin>>account.lastName;

    cout<<"Enter email: "<<endl;
    cin>>account.email;

//    cout<<"Enter account number: "<<endl;
//    cin>>account.accountNumber;
//    cout<<"Enter account pass code: "<<endl;
//    cin>>account.accountPassCode;

    Account NewAccount = TmsService::updateAccount(accountNumber,account);
    cout<<"Account for "<<NewAccount.firstName<<" "<<NewAccount.lastName<<" updated successfully"<<endl;
}


void depositOrDrawAmount(){
    int accountNumber;
    int amount;
    char depositOrDraw;

    cout<<"Enter account number: "<<endl;
    cin>>accountNumber;
    cout<<"Enter amount: "<<endl;
    cin>>amount;
    cout<<"Enter 1 for deposit or 2 for withdraw: "<<endl;
    cin>>depositOrDraw;
    switch (depositOrDraw) {
        case '1':
            TmsService::depositOrWithDrawAmount(accountNumber,amount, true);
            break;
        case '2':
            TmsService::depositOrWithDrawAmount(accountNumber,amount, false);
            break;
            default:
                cout<<"Invalid input"<<endl;
                break;
    }
}

void displayAllTransactions(vector<Transaction> transactions){
    cout<<"TRANSACTIONS"<<endl;
    cout<<"           ACCOUNT NUMBER           |           AMOUNT           |           TYPE       |"<<endl;
    cout<<"-----------------------------------------------------------------------------------------"<<endl;
    for(int i=0; i<transactions.size(); i++){
        cout<<"           "<<transactions[i].getAccountId()<<"           "<<transactions[i].getBalance()<<"           "<<transactions[i].getTransactionType()<<endl;
        cout<<"-------------------------------------------------------------------------------------"<<endl;
    }
}



int main() {
    int number;
    char option;
    Account account;
    TmsService service;
    do{
        cout<<                     " TRANSACTION MANAGEMENT SYSTEM                        "<<endl;
        cout<<"                   1. CREATE NEW ACCOUNT                                   "<<endl;
        cout<<"                   2. DISPLAY ACCOUNT BY A LINE IN A FILE                  "<<endl;
        cout<<"                   3. DEPOSIT OR WITHDRAW AMOUNT                           "<<endl;
        cout<<"                   4. LIST ALL TRANSACTIONS                                "<<endl;
        cout<<"                   5. CLOSE ACCOUNT                                        "<<endl;
        cout<<"                   6. DISPLAY ALL ACCOUNTS                                 "<<endl;
        cout<<"                   7. UPDATE ACCOUNT                                       "<<endl;
        cout<<"                   8. FIND BY ACCOUNT NUMBER                               "<<endl;
        cout<<"                   9. EXIT                                                 "<<endl;
        cin>>option;
        switch (option) {
            case '1':
                newAccountCreation();
                break;
            case '2':
                findByAccountNumber();
                break;
            case '3':
                depositOrDrawAmount();
                break;
            case '4':
                displayAllTransactions(service.returnAllTransactions());
                break;
            case '5':
                deleteFromFile();
                break;
            case '6':
                displayAccounts(service.returnAllAccounts());
                break;
            case '7':
                modifyAccount();
                break;
            case '8':
                displaySingleAccount();
                break;
            case '9':
                break;
            default:
                cout<<"Invalid option"<<endl;
                break;
    }
    }while(option!='8');
    return 0;
}
