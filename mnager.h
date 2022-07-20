#ifndef MNAGER_H
#define MNAGER_H
#include "employee.h"
#include "fstream"
#include "qmessagebox.h"
#include <QMainWindow>
#include "ctime"

using namespace std;

namespace Ui {
class Mnager;
}

class Mnager : public QMainWindow
{
    Q_OBJECT

public:
    //costructor
    explicit Mnager(QWidget *parent = nullptr);

    //distructor
    ~Mnager();

    //functions
    void show(int number);      //invoked by logging in of customer for show this new window
    void show_message_add_employee(string st,const Employee& new_employee);
    void show_exeption_employee_layout();
    void add_report(string new_report);

    //seters
    void set_info_in_manager_ui();
    void set_new_manger_in_file();  //for change manager info

    //signals & slots
private slots:
    void on_pushButton_apply_leave_4_clicked(); //ok
    void on_pushButton_apply_overtime_4_clicked();  //ok
    void on_pushButton_show_customer_info_4_clicked();
    //personal info set at the beging  //ok
    void on_pushButton_open_account_4_clicked();
    void on_pushButton_delete_account_4_clicked();
    void on_pushButton_add_employee_clicked(); //ok
    void on_Button_show_employee_info_clicked();  //ok
    void on_Button_layingout_clicked();  //ok

private:
    Ui::Mnager *ui;
    Employee manager;
};

#endif // MNAGER_H
