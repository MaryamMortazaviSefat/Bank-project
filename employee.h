#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QMainWindow>
#include "date.h"
#include "customer.h"
#include "new_customer.h"
#include <iostream>
#include "ctime"

using namespace std;
namespace Ui {
class Employee;
}

class Employee : public QMainWindow
{
    Q_OBJECT

    //nonmember function operators
    friend istream & operator>>(istream & in,Employee &e);
    friend ostream & operator<<(ostream & out, Employee &e);

public:
    //constructor
    explicit Employee(QWidget *parent=nullptr);
    Employee(string _first_name,string _last_name,string _natinal_code,Date _birthday,float _bacic_salary_recevived);

    //distructor
    ~Employee();

    //member function operators
    Employee& operator=(const Employee& e);

    //functions
    void show(int number);      //invoked by logging in of employee for show this new window
    void calculate_salary();
    void change_employee_info_in_file();   //invoed even the overtime or leavetime are changing
    string employee_to_string();     //this like to_string(Employee)
    void add_report(string &new_report);

    //seters
    void set_info_in_employee_ui(); //set info in ui from file
    int set_personal_id(); //for new employees
    void set_leave_hours(const int& new_hours);
    void set_overtime_hours(const int& new_hours);

    //geters
    string get_first_name()const;
    string get_last_name() const;
    int get_personal_id() const;
    Date get_birthday() const;
    long int get_basic_salary_received() const;
    string get_username() const;
    string get_password() const;
    int get_leave_hours() const;
    int get_overtime_hours() const;
    long int get_salary() const;

    //signals & slots
private slots:
    void on_pushButton_apply_leave_4_clicked(); //ok
    void on_pushButton_apply_overtime_4_clicked();  //ok
    void on_pushButton_show_customer_info_4_clicked();
    //personal info set at the beging  //ok
    void on_pushButton_open_account_4_clicked();
    void on_pushButton_delete_account_4_clicked();

    //utillity functions    
private:
    //string char_to_string(int n,char _char[n]);  //it can use for binary file on the future
    //void string_on_char(string input,const int n,char _char[]);
    void add_employee_to_file();  //for the new customers

private:
    Ui::Employee *ui;
    string first_name;
    string last_name;
    int personal_id;
    Date birthday;
    long int basic_salary_received;
    string user_name;
    string password;
    int leave_hours;
    int overtime_hours;
    long int salary;

};

#endif // EMPLOYEE_H
