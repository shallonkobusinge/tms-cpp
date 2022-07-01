//
// Created by kobsh on 01/07/2022.
//

#include "headers.h"
#include "models.cpp"


class TmsService {
public:
    static tm now() {
        time_t now = time(0);
        return *localtime(&now);
    }
    static ostream& formatDateTime(ostream& out, const tm& t, const char* fmt) {
        const time_put<char>& dateWriter = use_facet<time_put<char> >(out.getloc());
        int n = strlen(fmt);
        if (dateWriter.put(out, out, ' ', &t, fmt, fmt + n).failed()) {
            throw runtime_error("failure to format date time");
        }
        return out;
    }
    static string dateTimeToString(const tm& t, const char* format) {
        stringstream s;
        formatDateTime(s, t, format);
        return s.str();
    }
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
    static Transaction findTransactionByAccountId(int number){
        Transaction transaction;
        ifstream file("transaction.txt");
        string line;
        while (getline(file, line)) {
            if (line.find(to_string(number)) != string::npos) {
                transaction = getSingleTransaction(line);
            }
        }
        return transaction;
    }
    static bool checkIfTransactionExistsByAccountId(int number){
        ifstream file("transaction.txt");
        string line;
        while (getline(file, line)) {
            if (line.find(to_string(number)) != string::npos) {
                return true;
            }
        }
        return false;

    }
    static double deposit(double amount, Transaction &transaction){
        cout<< "Depositing amount..." <<(transaction.getBalance()+amount)<< endl;
//        transaction.balance+=amount;
//        cout<<"Deposit Successful"<<transaction.balance<<" dd "<<transaction.getBalance()<<endl;
        return transaction.getBalance();
//        transaction.setBalance(amount++);
    }
    static double returnBalance(Transaction transaction){
        return transaction.getBalance();
    }
    static void withdraw(double amount, Transaction transaction){
        transaction.balance-=amount;
    }
    static void depositOrWithDrawAmount(int accountNumber, bool isDeposit){
    Transaction transaction;
    ofstream file;
    string dt= dateTimeToString(now(),"%Y-%m-%d-%H:%M:%S");
    file.open("transaction.txt",ios::app);
        bool isAccountExists = checkIfAccountExists(accountNumber);
    if(isAccountExists){
        bool isTransactionExists = checkIfTransactionExistsByAccountId(accountNumber);
        if(isTransactionExists){
             transaction = findTransactionByAccountId(accountNumber);
             if(isDeposit){
                 int depositAmount;
                 cout<<"Enter amount to deposit"<<endl;
                    cin>>depositAmount;
                 transaction.balance+=depositAmount;
                 transaction.setTransactionType("DEPOSIT");
                 cout<<" Deposteddd amount "<<transaction.balance<< endl;
                    file<<accountNumber<< " " << " " <<transaction.getBalance()<<" "<<transaction.getTransactionType()<<"   " <<dt<<endl;
             }
             if(!isDeposit){
                 int withdrawAmount;
                    cout<<"Enter amount to withdraw"<<endl;
                    cin>>withdrawAmount;
                    if(transaction.getBalance() < withdrawAmount){
                        cout<<"Insufficient balance"<<endl;

                    }else{
                        transaction.balance -= withdrawAmount;
                        transaction.transactionType = "WITHDRAW";
                        file<<accountNumber<< " " << " " <<transaction.getBalance()<<"   "<<transaction.getTransactionType()<<"   "<<dt<<endl;
                    }
             }
            cout<<" already exists "<<transaction.getBalance()<<endl;
        }else{
            cout<<" There is no transaction for this account! SO!"<<endl;
            double amount;
            cout<<"Enter amount to deposit"<<endl;
            cin>>amount;
            transaction.balance = 0.00+amount;
            transaction.transactionType = "DEPOSIT";
            transaction.accountId = accountNumber;
            file << transaction.accountId << " " << " " << transaction.balance << " " << transaction.transactionType<<"  "<<dt << endl;
            cout<<" balance "<<transaction.getBalance()<<endl;
        }
    }else{
        cout<<"Account not found"<<endl;
    }
    file.close();
    }
    static Transaction getSingleTransaction(const string &line){
        stringstream ss(line);
        Transaction transaction;
        int i = 0;

        for (string rowElement; ss >> rowElement;) {
            if (reinterpret_cast<const char *>(rowElement[rowElement.length() - 1]) == "")
                rowElement.pop_back();
            if (i == 0) transaction.accountId = stoi(rowElement);
            else if (i == 1) transaction.balance = stoi(rowElement);
            else if (i == 2) transaction.transactionType = rowElement;
            else if(i == 3) transaction.date = rowElement;
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






