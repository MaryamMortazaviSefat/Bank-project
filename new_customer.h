#ifndef NEW_CUSTOMER_H
#define NEW_CUSTOMER_H
#include "customer.h"
#include <QMainWindow>
#include <iostream>

using namespace std;

namespace Ui {
class New_customer;
}

class New_customer : public QMainWindow
{
    Q_OBJECT

public:
    //constuctor
    explicit New_customer(QWidget *parent = nullptr);

    //distructor
    ~New_customer();

    //function
    void show_message_add_customer(string message,Customer& new_customer);
    void add_report(string report);

private slots:
    void on_pushButton_newcutomer_clicked();

private:
    Ui::New_customer *ui;
};

#endif // NEW_CUSTOMER_H
