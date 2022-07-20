#ifndef BANK_H
#define BANK_H

#include <QMainWindow>

#include "mnager.h"
#include "employee.h"
#include "customer.h"

#include <string>
#include <vector>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class Bank;
             }
QT_END_NAMESPACE

class Bank : public QMainWindow
{
    Q_OBJECT

public:

    //constructor
    Bank(QWidget *parent = nullptr);

    //distructor
    ~Bank();

    //functions
    void add_report(string &st);
    int search_employee(string username,string password);
    int search_customer(string username,string password);

    //seters
    void set_brach_info();
    void set_manger();
    void set_employees();
    void set_customers();

    //slots
private slots:
    void on_button_login_employee_2_clicked();
    void on_button_login_customer_clicked();

private:
    Ui::Bank *ui;

    int employee_num;
    Employee* employees;

    int customer_num;
    Customer* customers;

    string branchName;
    string branchId;

    Employee manager;
};
#endif // BANK_H
