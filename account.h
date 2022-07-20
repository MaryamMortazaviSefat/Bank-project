#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <iostream>
#include "customer.h"

using namespace std;

class Account
{
public:
    //costructor
    Account();
    Account(int username, int _balance , int count);

    //functions
    void add_account_to_object_of_customer(int username);

    //geters
    int get_balance_account() const;
    int get_accountnumber() const;

private:
    int account_number;
    int balance;
    int status;
};

#endif // ACCOUNT_H
