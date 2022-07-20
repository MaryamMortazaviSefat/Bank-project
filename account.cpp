#include "account.h"

//...........................<<<< constructor >>>>.......................................

Account::Account(){
    balance=0;
    status=1;
    account_number=0;
}

Account::Account(int username, int _balance , int count)
{
    //construct object
    balance=_balance;
    status=1;
    account_number = username*100000+count;
    //add object to customer object
    add_account_to_object_of_customer(username);
}

//..................................<<<functions>>>......................................

void Account::add_account_to_object_of_customer(int username){

    int line_number=username-999;
    string st;
    ifstream in_file{"E:/fi/customers_info.txt",ios::in};
    Customer current;

    for(int i=0;i<line_number;i++)
    {
     in_file>>current;
    }

    in_file.close();

    string accounts=current.get_accounts();


    //add string of new account to local string of all accounts
    st=to_string(account_number);
    for(int i=0;i<st.size();i++)
    {
        accounts.push_back(st[i]);
    }
    accounts.push_back(',');
    st=to_string(balance);
    for(int i=0;i<st.size();i++)
    {
        accounts.push_back(st[i]);
    }
    accounts.push_back(',');
    st=to_string(status);
    for(int i=0;i<st.size();i++)
    {
        accounts.push_back(st[i]);
    }
    accounts.push_back('/');

    current.set_accounts(accounts);

    current.edit_object_in_file();

    in_file.close();
}

//......................................<<<geters>>>......................................

int Account::get_balance_account() const{
    return balance;
}

int Account::get_accountnumber() const{
    return account_number;
}

