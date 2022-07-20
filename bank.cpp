#include "ui_bank.h"
#include "bank.h"
#include "fstream"
#include <qmessagebox.h>


//...........................<<<< constructor >>>>.......................................

Bank::Bank(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Bank)
{
    //employees.resize(0);
    ui->setupUi(this);

    //set branch info
    set_brach_info();

    //set manager info
    set_manger();

    //set employees' info
    set_employees();

    //set customers' info
    set_customers();

}

//...........................<<<< distructor >>>>........................................

Bank::~Bank()
{
    for(int i=0;i<employee_num;i++)
    {
        delete [] employees;
    }
    delete employees;

    delete ui;
}

//..........................<<<< signal & slot >>>>......................................

void Bank::on_button_login_employee_2_clicked()
{
    string input_username =ui->input_username_2->text().toStdString();
    string input_password =ui->input_password_2->text().toStdString();

    int number=-2;  //-1: manager | -2: exeption | others: employees
    number=search_employee(input_username,input_password);

    if(number==-1)
    {
        //make & add report
        string report=manager.get_first_name();
        string st="(manager) with natinal code ";
        for(int i=0;i<st.size();i++)
        {
            report.push_back(st[i]);
        }
        st=manager.get_password();
        for(int i=0;i<st.size();i++)
        {
            report.push_back(st[i]);
        }
        st=" logged in to the bank program ";
        for(int i=0;i<st.size();i++)
        {
            report.push_back(st[i]);
        }
        add_report(report);

        Mnager* mg=new Mnager;
        mg->show(-1);

    }
    else if (number!=-1 && number!=-2)
    {
        //make & add report
        string report=employees[number].get_first_name();
        string st="(employee) with natinal code ";
        for(int i=0;i<st.size();i++)
        {
            report.push_back(st[i]);
        }
        st=employees[number].get_password();
        for(int i=0;i<st.size();i++)
        {
            report.push_back(st[i]);
        }
        st=" logged in to the bank program ";
        for(int i=0;i<st.size();i++)
        {
            report.push_back(st[i]);
        }
        add_report(report);

        Employee* employee_ui=new Employee(this);
        employee_ui->show(number);
    }
    else if(number==-2)
    {
        QMessageBox error;
        error.setWindowTitle("خطا");
        error.setText("گذرواژه یا نام کاربری اشتباه است" );
        error.exec();
    }

}

void Bank::on_button_login_customer_clicked()
{
    string input_username =ui->input_username_customer->text().toStdString();
    string input_password =ui->input_password_customer->text().toStdString();

    int number=-1;  //-1: exeption |  others: customers
    number=search_customer(input_username,input_password);

    if(number==-1)
    {
        QMessageBox error;
        error.setWindowTitle("خطا");
        error.setText("گذرواژه یا نام کاربری اشتباه است" );
        error.exec();
    }
    else if(number!=-1)
    {
        //make & add report
        string report=customers[number].get_firstname();
        string st="(customer) with natinal code ";
        for(int i=0;i<st.size();i++)
        {
            report.push_back(st[i]);
        }
        st=customers[number].get_natinal_code();
        for(int i=0;i<st.size();i++)
        {
            report.push_back(st[i]);
        }
        st=" logged in to the bank program ";
        for(int i=0;i<st.size();i++)
        {
            report.push_back(st[i]);
        }
        add_report(report);

        Customer* customer_ui=new Customer(this);
        customer_ui->show(number);
    }

}

//..................................<<<functions>>>......................................

void Bank::add_report(string &new_report){

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

int Bank::search_employee(string username,string password){

    if(username==manager.get_username() && password==manager.get_password())
    {
    return -1;
    }

    if(username=="n" && password=="n")
    {
        return -2;
    }

    for(int i=0;i<employee_num;i++)
    {
        if(employees[i].get_username()==username && employees[i].get_password()==password)
        {
            return i;
        }
    }

    return -2;
}

int Bank::search_customer(string username, string password){

    for(int i=0;i<customer_num;i++)
    {
        if(to_string(customers[i].get_username())==username && customers[i].get_password()==password)
        {
            return i;
        }
    }

    return -1;

}

//....................................<<<seters>>>........................................

void Bank::set_brach_info(){

    ifstream in_file;

    in_file.open("E:/fi/bank_brach_info.txt",ios::in);
    if(!in_file)
    {
        exit(EXIT_FAILURE);
    }
    in_file>>branchId>>branchName;
    in_file.close();

    ui->branch_code->setText(QString::fromStdString(branchId));
    ui->branchname->setText(QString::fromStdString(branchName));


}

void Bank::set_manger(){

    ifstream in_file;

    in_file.open("E:/fi/manager_info.txt",ios::in);
    if(!in_file)
    {
        exit(EXIT_FAILURE);
    }
    in_file>>manager;
    in_file.close();
}

void Bank::set_employees()
{
    employee_num=0;

    ifstream in_file{"E:/fi/employees_info.txt",ios::in};
    if(!in_file)
    {
    exit(EXIT_FAILURE);
    }
    Employee temp;


    //find number
    while (in_file>>temp)
   {
       employee_num++;
   }

   in_file.close();
   in_file.open("E:/fi/employees_info.txt",ios::in);

   employees=new Employee[employee_num];

   int i=0;
   while (i<employee_num)
   {
       in_file>>employees[i];
       i++;
   }

    in_file.close();
}

void Bank::set_customers(){

    customer_num=0;

    ifstream in_file{"E:/fi/customers_info.txt",ios::in};
    if(!in_file)
    {
    exit(EXIT_FAILURE);
    }
    Customer temp;

    //find number
    while (in_file>>temp)
   {
       customer_num++;
   }

   in_file.close();
   in_file.open("E:/fi/customers_info.txt",ios::in);

   customers=new Customer[customer_num];

   int i=0;
   while (i<customer_num)
   {
       in_file>>customers[i];
       i++;
   }

    in_file.close();

}
