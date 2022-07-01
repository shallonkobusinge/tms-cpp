//
// Created by kobsh on 01/07/2022.
//
#include "iostream"
#pragma once
using namespace std;


enum TransactionTypeEnum {
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
};


class Transaction{
public:
    int accountId;
    string transactionType;
    double balance;
    string date;
public:
    int getAccountId() {
        return accountId;
    }
    void setAccountId(int accountId) {
        this->accountId = accountId;
    }
    string getTransactionType() {
        return transactionType;
    }
    void setTransactionType(string transactionType) {
        this->transactionType = transactionType;
    }
    double getBalance() {
        return balance;
    }
    void setBalance(double balance) {
        this->balance = balance;
    }

};