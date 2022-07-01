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



int main() {
    int number;
    char option;
    Account account;
    TmsService service;
    do{
        cout<<                     " TRANSACTION MANAGEMENT SYSTEM                        "<<endl;
        cout<<"                   1. CREATE NEW ACCOUNT                                   "<<endl;
        cout<<"                   2. DISPLAY ACCOUNT BY ACCOUNT NUMBER                    "<<endl;
        cout<<"                   3. DEPOSIT AMOUNT                                       "<<endl;
        cout<<"                   4. WITHDRAW AMOUNT                                      "<<endl;
        cout<<"                   5. CLOSE ACCOUNT                                        "<<endl;
        cout<<"                   6. DISPLAY ALL ACCOUNTS                                 "<<endl;
        cout<<"                   7. UPDATE ACCOUNT                                       "<<endl;
        cout<<"                   8. EXIT                                                 "<<endl;
        cin>>option;
        switch (option) {
            case '1':
                newAccountCreation();
                break;
            case '2':
                findByAccountNumber();
                break;
            case '3':
                service.depositAmount();
                break;
            case '4':
                service.withDrawAmount();
                break;
            case '5':
                service.closeAccount();
                break;
            case '6':
                service.getAllAccounts();
                break;
            case '7':
                service.updateAccount();
                break;
            case '8':
                break;
            default:
                cout<<"Invalid option"<<endl;
                break;
    }
    }while(option!='8');
    return 0;
}
