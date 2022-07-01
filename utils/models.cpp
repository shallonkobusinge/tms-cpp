//
// Created by kobsh on 01/07/2022.
//
#include "headers.h"


enum TransactionType{
    DEPOSIT,
    WITHDRAW
};


class Account{
public:
    string firstName;
    string lastName;
    string email;
    string accountPassCode;
    int accountNumber;
    string address;

};


class Transaction{
public:
    int accountId;
    TransactionType transactionType;
    double balance;

};