#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QMainWindow>
#include <iostream>
#include "date.h"
#include "fstream"
#include "account.h"
#include "qmessagebox.h"
using namespace std;

namespace Ui {
class Customer;
}

class Customer : public QMainWindow
{
    Q_OBJECT

    //nonmember function operators
    friend istream & operator>>(istream & in,Customer &e);
    friend ostream & operator<<(ostream & out,Customer &e);

public:
    //constructor
    explicit Customer(QWidget *parent = nullptr);
    Customer(string _first_name,string _last_name,string _natinal_code,Date _birthday);

    //distructor
    ~Customer();

    //functions
    void show(int number);      //invoked by logging in of customer for show this new window
    void add_customer_in_file();  //invoked by cunstroctor
    void add_report(string &new_report);
    string convert_account_to_st_for_ui_showinfo(); //without balance
    string convert_account_st_ui_with_balance();
    bool change_balance_in_current_object(string accountnumber,int change);
    void edit_object_in_file();
    string customer_to_string();
    string return_account_info(string accountnumber);
    bool delete_account_number(int _account_number);


    //seters
    int set_username();
    void set_info_in_customer_ui_show();
    void set_info_in_customer_ui_deposit();
    void set_info_in_customer_ui_withdraw();
    void set_accounts(string &_accounts);

    //geters
    string get_firstname() const;
    string get_lastname() const;
    int get_username() const;
    string get_password() const;
    string get_natinal_code() const;
    Date get_birthday() const;
    string get_accounts() const;
    int get_the_counts_of_customer_accounts() ;

private slots:
    void on_show_clicked();

    void on_withdraw_clicked();

    void on_deposit_clicked();

private:
    Ui::Customer *ui;
    int username;
    string firstname;
    string lastname;
    string natinalcode;
    Date birthday;
    string password;
    string accounts;

};

#endif // CUSTOMER_H
