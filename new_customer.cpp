#include "new_customer.h"
#include "ui_new_customer.h"
#include "qmessagebox.h"
#include "fstream"
//...........................<<<< constructor >>>>.......................................

New_customer::New_customer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::New_customer)
{
    ui->setupUi(this);
}

//...........................<<<< distructor >>>>........................................

New_customer::~New_customer()
{
    delete ui;
}

//..........................<<<< signal & slot >>>>......................................

void New_customer::on_pushButton_newcutomer_clicked()
{
    string customer_natinal_code=ui->customer_natinal_code->text().toStdString();
    if(customer_natinal_code.size()==10)
    {
        string customer_first_name=ui->customer_firstname->text().toStdString();
        string customer_last_name=ui->customer_lastname->text().toStdString();
        int day=ui->customer_birthday_day->text().toInt();
        int month=ui->customer_birthday_month->text().toInt();
        int year=ui->customer_birthday_year->text().toInt();
        Date customer_birthday(day,month,year);

        //construct new customer add in file
        Customer new_customer(customer_first_name,customer_last_name,customer_natinal_code,customer_birthday);

        string customer_user_name=to_string (new_customer.get_username());
        string customer_password=new_customer.get_password();


        //message for username & password

        string temp;
        string message;

        temp=" مشتری با موفقیت ثبت شد ";
        for(int i=0;i<temp.size();i++)
        {
            message.push_back(temp[i]);
        }

        //user name
        temp="\n\n  نام کاربری : ";
        for(int i=0;i<temp.size();i++)
        {
            message.push_back(temp[i]);
        }
        temp=customer_user_name;
        for(int i=0;i<temp.size();i++)
        {
            message.push_back(temp[i]);
        }

        //password
        temp="\n  گذرواژه: ";
        for(int i=0;i<temp.size();i++)
        {
            message.push_back(temp[i]);
        }
        temp=customer_password;
        for(int i=0;i<temp.size();i++)
        {
            message.push_back(temp[i]);
        }

        show_message_add_customer(message,new_customer);
        QWidget::close();
    }
    else if(customer_natinal_code.size()!=10)
    {
        QMessageBox error;
        error.setWindowTitle("خطا");
        error.setText("کدملی وارد شده نامعتبر می باشد.");
        error.exec();
    }

}

//..................................<<<functions>>>......................................

void New_customer::show_message_add_customer(string message, Customer &new_customer)
{
    QMessageBox error;
    error.setWindowTitle("نتیجه درخواست");
    error.setText(QString::fromStdString(message));
    error.setButtonText(error.Ok,"   بازگشت و ادامه فرآیند   ");
    error.exec();

    //make & add report
    string report=new_customer.get_firstname();
    string st=" with natinal code ";
    for(int i=0;i<st.size();i++)
    {
        report.push_back(st[i]);
    }
    st=new_customer.get_natinal_code();
    for(int i=0;i<st.size();i++)
    {
        report.push_back(st[i]);
    }
    st=" was added to the bank's customer ";
    for(int i=0;i<st.size();i++)
    {
        report.push_back(st[i]);
    }

    add_report(report);
}

void New_customer::add_report(string new_report){

    //time of now
    time_t now = time(0);

    //convert now to string form
    char* dt = ctime(&now);

    //add end of file
    ofstream app_file;
    app_file.open("E:/fi/reports.txt",ios::app);
    if(!app_file)
    {
        exit(EXIT_FAILURE);
    }

    app_file<<new_report<<" at "<< dt << endl;
    app_file.close();
}

