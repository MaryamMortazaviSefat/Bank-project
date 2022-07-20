#include "employee.h"
#include "ui_employee.h"
#include "fstream"
#include "qmessagebox.h"

//...........................<<<< constructor >>>>.......................................

Employee::Employee(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Employee)
{
    ui->setupUi(this);
}

Employee::Employee(string _first_name, string _last_name, string _natinal_code, Date _birthday, float _bacic_salary_recevived)
{
    //construct object
    personal_id=set_personal_id();
    first_name= _first_name;
    last_name=_last_name;
    birthday= _birthday;
    basic_salary_received=_bacic_salary_recevived;
    user_name=_first_name;
    password=_natinal_code;
    leave_hours=0;
    overtime_hours=0;
    salary=_bacic_salary_recevived;

    //add object to file
    add_employee_to_file();
}

//...........................<<<< distructor >>>>........................................

Employee::~Employee()
{
    delete ui;
}

//..........................<<<< signal & slot >>>>......................................

void Employee::on_pushButton_apply_leave_4_clicked()
{
    //change -->object of employee
    leave_hours += ui->leave_hour_4->text().toInt();
    calculate_salary();
    //set employee to -->file
    change_employee_info_in_file();

    //set new info in --> ui
    set_info_in_employee_ui();

    //show message box
    QMessageBox error;
    error.setWindowTitle("نتیجه درخواست");
    string message="با درخواست شما موافقت شد؛\n مرخصی شما تا کنون: ";

    string hour_st=to_string(leave_hours);
    for(int i=0;i<hour_st.size();i++)
    {
        message.push_back(hour_st[i]);
    }

    message.push_back('h');

    error.setText(QString::fromStdString(message));
    error.exec();

    //make & add report
    string report=first_name;
    string temp="(employee) get ";
    for(int i=0;i<temp.size();i++)
    {
        report.push_back(temp[i]);
    }
    temp=to_string(ui->leave_hour_4->text().toInt());
    for(int i=0;i<temp.size();i++)
    {
        report.push_back(temp[i]);
    }
    temp=" hours leavetime";
    for(int i=0;i<temp.size();i++)
    {
        report.push_back(temp[i]);
    }
    add_report(report);

}

void Employee::on_pushButton_apply_overtime_4_clicked()
{
    bool flag=true;

    if((overtime_hours+ ui->overtime_hour_4->text().toInt())>12)
    {
        flag=false;

        QMessageBox error_ceiling;
        error_ceiling.setWindowTitle("خطا");
        string message=" درخواست شما معتبر نمی باشد؛\n اضافه کار شما تا کنون: ";

        string hour_st=to_string(overtime_hours);
        for(int i=0;i<hour_st.size();i++)
        {
            message.push_back(hour_st[i]);
        }

        message.push_back('h');

        error_ceiling.setText(QString::fromStdString(message));
        error_ceiling.exec();
    }

    if(flag)
    {
        //change -->object of employee
        overtime_hours += ui->overtime_hour_4->text().toInt();
        calculate_salary();

        //set employee to -->file
        change_employee_info_in_file();

        //set new info in --> ui
        set_info_in_employee_ui();

        //show message box
        QMessageBox error;
        error.setWindowTitle("نتیجه درخواست");
        string message="با درخواست شما موافقت شد؛\n اضافه کار شما تا کنون: ";

        string hour_st=to_string(overtime_hours);
        for(int i=0;i<hour_st.size();i++)
        {
            message.push_back(hour_st[i]);
        }

        message.push_back('h');

        error.setText(QString::fromStdString(message));
        error.exec();

        //make & add report
        string report=first_name;
        string temp="(employee) get ";
        for(int i=0;i<temp.size();i++)
        {
            report.push_back(temp[i]);
        }
        temp=to_string(ui->overtime_hour_4->text().toInt());
        for(int i=0;i<temp.size();i++)
        {
            report.push_back(temp[i]);
        }
        temp=" hours overtime";
        for(int i=0;i<temp.size();i++)
        {
            report.push_back(temp[i]);
        }
        add_report(report);
    }


}

void Employee::on_pushButton_show_customer_info_4_clicked()
{
    string natinal_code=ui->cumtomer_natinal_code_show_info_4->text().toStdString();
    Customer current;
    bool flag=true;

    //find current
    fstream file{"E:/fi/customers_info.txt"};
    while(flag && file>>current)
    {
        if(current.get_natinal_code()==natinal_code)
        {
            flag=false;
        }
    }
    file.close();

    //customer not found
    if(flag)
    {
        QMessageBox result;
        result.setWindowTitle("خطا");
        string message=" مشتری مورد نظر یافت نشد. ";
        result.setText(QString::fromStdString(message));
        result.exec();
    }
    //customer found
    else if (!flag)
    {
        ui->customer_info_4->clear();
        ui->customer_info_4->insertPlainText(QString::fromStdString("\nنام:  "));
        ui->customer_info_4->insertPlainText(QString::fromStdString(current.get_firstname()));
        ui->customer_info_4->insertPlainText(QString::fromStdString("\nنام خانوادگی:  "));
        ui->customer_info_4->insertPlainText(QString::fromStdString(current.get_lastname()));
        ui->customer_info_4->insertPlainText(QString::fromStdString("\nشماره ملی:  "));
        ui->customer_info_4->insertPlainText(QString::fromStdString(current.get_natinal_code()));
        ui->customer_info_4->insertPlainText(QString::fromStdString("\nتاریخ تولد:  "));
        ui->customer_info_4->insertPlainText(QString::fromStdString(current.get_birthday().date_to_string()));
        ui->customer_info_4->insertPlainText(QString::fromStdString("\nنام کاربری:  "));
        ui->customer_info_4->insertPlainText(QString::fromStdString(to_string(current.get_username())));
        ui->customer_info_4->insertPlainText(QString::fromStdString("\nگذرواژه:  "));
        ui->customer_info_4->insertPlainText(QString::fromStdString(current.get_password()));
        ui->customer_info_4->insertPlainText(QString::fromStdString("\n"));

        string show_account_st = current.convert_account_st_ui_with_balance();
        ui->customer_info_4->insertPlainText(QString::fromStdString(show_account_st));

        //make & add report
        string report=first_name;
        string temp="(employee) saw the info of ";
        for(int i=0;i<temp.size();i++)
        {
            report.push_back(temp[i]);
        }
        temp=current.get_firstname();
        for(int i=0;i<temp.size();i++)
        {
            report.push_back(temp[i]);
        }
        temp="(customer) ";
        for(int i=0;i<temp.size();i++)
        {
            report.push_back(temp[i]);
        }
        add_report(report);
    }

}

void Employee::on_pushButton_open_account_4_clicked()
{
    Customer current;
    bool found=false;

    string natinal_code=ui->cumtomer_natinal_code_open_account_7->text().toStdString();

    //search customer from file
    fstream file;
    file.open("E:/fi/customers_info.txt");
    while(!found && file>>current)
    {
        if(current.get_natinal_code()==natinal_code)
        {
            found=true;
        }
    }
    file.close();

    //this customer is new customer
    if(!found)
    {
        New_customer* mg=new New_customer;
        mg->show();
    }

    if(found)
    {
        //check cash
        if(ui->cumtomer_money_for_open_account_8->text().toInt()<50000)
        {
            QMessageBox result;
            result.setWindowTitle("خطا");
            string message="مبلغ وارد شده کمتر از 000 50 تومان است.";
            result.setText(QString::fromStdString(message));
            result.exec();
        }
        else if(ui->cumtomer_money_for_open_account_8->text().toInt()>=50000)
        {
            //create new account
            Account new_account(current.get_username(),ui->cumtomer_money_for_open_account_8->text().toInt(),current.get_the_counts_of_customer_accounts()+1);

            //show message
            QMessageBox result;
            result.setWindowTitle("نتیجه درخواست");
            string message=" افتتاح حساب با موفقیت انجام شد\n شماره حساب : ";
            //account number
            string st =to_string(new_account.get_accountnumber());
            for(int i=0;i<st.size();i++)
            {
                message.push_back(st[i]);
            }
            //account balance
            st="\n موجودی حساب: ";
            for(int i=0;i<st.size();i++)
            {
                message.push_back(st[i]);
            }
            st =to_string(new_account.get_balance_account());
            for(int i=0;i<st.size();i++)
            {
                message.push_back(st[i]);
            }
            result.setText(QString::fromStdString(message));
            result.exec();


            //make & add report
            string report=first_name;
            string temp="(employee) opened the acconunt whit ";
            for(int i=0;i<temp.size();i++)
            {
                report.push_back(temp[i]);
            }
            temp=to_string (new_account.get_accountnumber()) ; //bayad dorost bbeshe
            for(int i=0;i<temp.size();i++)
            {
                report.push_back(temp[i]);
            }
            temp=" account number for ";
            for(int i=0;i<temp.size();i++)
            {
                report.push_back(temp[i]);
            }
            temp=current.get_firstname();
            for(int i=0;i<temp.size();i++)
            {
                report.push_back(temp[i]);
            }
            temp="(customer) ";
            for(int i=0;i<temp.size();i++)
            {
                report.push_back(temp[i]);
            }

            add_report(report);
        }

    }

}

void Employee::on_pushButton_delete_account_4_clicked()
{
    Customer current;
    bool found=false;

    string customer_natinalcode=ui->cumtomer_natinal_code_delete_account_4->text().toStdString();
    int account_number=ui->account_num_delete_account_2->text().toInt();

    //search customer from file
    fstream file;
    file.open("E:/fi/customers_info.txt");
    while(!found && file>>current)
    {
        if(current.get_natinal_code()==customer_natinalcode)
        {
            found=true;
        }
    }
    file.close();

    //not found customer
    if(!found)
    {
        QMessageBox error;
        error.setWindowTitle("خطا");
        string message=" مشتری مورد نظر یافت نشد! ";
        error.setText(QString::fromStdString(message));
        error.exec();
    }

    //found customer
    else if (found)
    {
        //delete account(chane customer info in file)
        if(current.delete_account_number(account_number))
        {
            //show message
            QMessageBox result;
            result.setWindowTitle("نتیجه درخواست");
            string message=" عملیات با موفقیت انجام شد. ";
            result.setText(QString::fromStdString(message));
            result.exec();

            //make & add report
            string report=first_name;
            string temp="(employee) deleted the acconunt whit ";
            for(int i=0;i<temp.size();i++)
            {
                report.push_back(temp[i]);
            }
            temp=to_string(account_number);
            for(int i=0;i<temp.size();i++)
            {
                report.push_back(temp[i]);
            }
            temp=" account number for ";
            for(int i=0;i<temp.size();i++)
            {
                report.push_back(temp[i]);
            }
            temp=current.get_firstname();
            for(int i=0;i<temp.size();i++)
            {
                report.push_back(temp[i]);
            }
            temp="(customer) ";
            for(int i=0;i<temp.size();i++)
            {
                report.push_back(temp[i]);
            }

            add_report(report);
        }

        else
        {
            QMessageBox error;
            error.setWindowTitle("خطا");
            string message=" حساب مورد نظر یافت نشد! ";
            error.setText(QString::fromStdString(message));
            error.exec();
        }

    }


}

//..............................<<<<operators>>>>........................................

istream & operator>>(istream & in,Employee &e){

    in>>e.personal_id>>e.first_name>>e.last_name>>e.basic_salary_received>>e.birthday>>e.user_name>>e.password>>e.leave_hours>>e.overtime_hours>>e.salary;

    return in;
}

ostream & operator<<(ostream & out, Employee &e){
    out<<e.personal_id<<" "<<e.first_name<<" "<<e.last_name<<" "<<e.basic_salary_received<<" "<<e.birthday<<" "<<e.user_name<<" "<<e.password<<" "<<e.leave_hours<<" "<<e.overtime_hours<<" "<<e.salary<<"\n";

    return out;

}

Employee& Employee::operator=(const Employee &e){

    first_name= e.first_name;
    last_name=e.last_name;
    personal_id=e.personal_id;
    birthday= e.birthday;
    basic_salary_received=e.basic_salary_received;
    user_name=e.first_name;
    password=e.password;
    leave_hours=e.leave_hours;
    overtime_hours=e.overtime_hours;
    salary=e.salary;


    return *this;
}

//..................................<<<functions>>>......................................

void Employee::show(int number){

    ifstream in_file;
    in_file.open("E:/fi/employees_info.txt",ios::in);
    if(!in_file)
    {
    exit(EXIT_FAILURE);
    }

    for(int i=0;i<=number;i++)
    {
       in_file >> *this;
    }

    set_info_in_employee_ui();


    QWidget::show();


}

void Employee::calculate_salary(){

    salary=basic_salary_received;

    float temp=0;
    if(leave_hours>15)
    {
        temp=leave_hours - 15;
        salary-=(temp*100000);
    }

    salary+=(overtime_hours*120000);

}

void Employee::change_employee_info_in_file(){

    int line_number=personal_id-99;  //it begin from 1
    string befor;
    string after;
    string tempst;
    Employee temp;

    fstream file{"E:/fi/employees_info.txt"};

    int i=0;
    for(i=1;i<line_number;i++)
    {
        file>>temp;
        tempst=temp.employee_to_string();
        for(int j=0;j<tempst.size();j++)
        {
        befor.push_back(tempst[j]);
        }
    }

    file>>temp; //current object in last mode

    while(file>>temp)
    {
        tempst=temp.employee_to_string();
        for(int j=0;j<tempst.size();j++)
        {
        after.push_back(tempst[j]);
        }

    }

    //seekp
    file.close();
    file.open("E:/fi/employees_info.txt");


    file<<befor<<*this<<after;
    file.close();

}

string Employee::employee_to_string(){

    string result;
    result.resize(0);

    string temp;
    temp.resize(0);

    //add personal id
    result=to_string(personal_id);
    result.push_back(' ');

    //add first name
    for(int j=0;j<first_name.size();j++)
    {
    result.push_back(first_name[j]);
    }
    result.push_back(' ');

    //add last name
    for(int j=0;j<last_name.size();j++)
    {
    result.push_back(last_name[j]);
    }
    result.push_back(' ');

    //add basic salary
    temp=to_string(basic_salary_received);
    for(int j=0;j<temp.size();j++)
    {
    result.push_back(temp[j]);
    }
    result.push_back(' ');

    //add birthday
    temp=birthday.date_to_file_string();
    for(int j=0;j<temp.size();j++)
    {
    result.push_back(temp[j]);
    }
    result.push_back(' ');

    //add username
    for(int j=0;j<user_name.size();j++)
    {
    result.push_back(user_name[j]);
    }
    result.push_back(' ');

    //add password
    for(int j=0;j<password.size();j++)
    {
    result.push_back(password[j]);
    }
    result.push_back(' ');

    //add leave time
    temp=to_string(leave_hours);
    for(int j=0;j<temp.size();j++)
    {
    result.push_back(temp[j]);
    }
    result.push_back(' ');

    //add overtime time
    temp=to_string(overtime_hours);
    for(int j=0;j<temp.size();j++)
    {
    result.push_back(temp[j]);
    }
    result.push_back(' ');

    //add salary
    temp=to_string(salary);
    for(int j=0;j<temp.size();j++)
    {
    result.push_back(temp[j]);
    }
    result.push_back('\n');

    return result;
}

void Employee::add_report(string &new_report){

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

//..........................<<<utility functions>>>......................................

/*void Employee::string_on_char(string input,const int n, char _char[])
{

    for(int i=0;i<input.size();i++)
    {
        _char[i]=input[i];
    }

    if((n-input.size())>0)
    {
        for(int i=input.size();i<n;i++)
        {
            _char[i]='\0';
        }
    }

}
*/
/*string Employee::char_to_string(int n, char _char[])
{
    string result;

    for(int i=0;i<n;i++)
    {
        result.push_back(_char[i]);
    }


    return result;
}*/
void Employee::add_employee_to_file(){

    ofstream app_file;
    app_file.open("E:/fi/employees_info.txt",ios::app);

    if(!app_file)
    {
        exit(EXIT_FAILURE);
    }

    app_file<<*this;
    app_file.close();
}

//....................................<<<seters>>>........................................

void Employee::set_info_in_employee_ui(){
    //leave hours
    ui->employee_firstname->setText(QString::fromStdString(first_name));
    ui->employee_lastname->setText(QString::fromStdString(last_name));

    //overtime hours
    ui->employee_firstname_2->setText(QString::fromStdString(first_name));
    ui->employee_lastname_2->setText(QString::fromStdString(last_name));

    ui->employee_info_4->clear();
    ui->employee_info_4->insertPlainText(QString::fromStdString("\nنام:  "));
    ui->employee_info_4->insertPlainText(QString::fromStdString(first_name));
    ui->employee_info_4->insertPlainText( QString::fromStdString("\nنام خانوادگی:  "));
    ui->employee_info_4->insertPlainText(QString::fromStdString(last_name));
    ui->employee_info_4->insertPlainText( QString::fromStdString("\nکد پرسنلی:  "));
    ui->employee_info_4->insertPlainText(QString::fromStdString(to_string(personal_id)));
    ui->employee_info_4->insertPlainText( QString::fromStdString("\nتاریخ تولد:  "));
    ui->employee_info_4->insertPlainText(QString::fromStdString(birthday.date_to_string()));
    ui->employee_info_4->insertPlainText( QString::fromStdString("\nپایه حقوقی:  "));
    ui->employee_info_4->insertPlainText(QString::fromStdString(to_string(basic_salary_received)));
    ui->employee_info_4->insertPlainText( QString::fromStdString("\nنام کاربری:  "));
    ui->employee_info_4->insertPlainText(QString::fromStdString(user_name));
    ui->employee_info_4->insertPlainText( QString::fromStdString("\nگذرواژه:  "));
    ui->employee_info_4->insertPlainText(QString::fromStdString(password));
    ui->employee_info_4->insertPlainText( QString::fromStdString("\nساعات مرخصی:  "));
    ui->employee_info_4->insertPlainText(QString::fromStdString(to_string(leave_hours)));
    ui->employee_info_4->insertPlainText( QString::fromStdString("\nساعات اضافه کار:  "));
    ui->employee_info_4->insertPlainText(QString::fromStdString(to_string(overtime_hours)));
    ui->employee_info_4->insertPlainText( QString::fromStdString("\n\nحقوق دریافتی:  "));
    ui->employee_info_4->insertPlainText(QString::fromStdString(to_string(salary)));

}
int Employee::set_personal_id(){
    int result=0;

    ifstream in_file{"E:/fi/employees_info.txt",ios::in};


    //find number
    while (in_file>>*this)
    {
        result++;
    }

    in_file.close();

    result+= 100;
    return result;
}
void Employee::set_leave_hours(const int& new_hours){
    leave_hours=new_hours;
}
void Employee::set_overtime_hours(const int& new_hours){
    overtime_hours=new_hours;
}

//......................................<<<geters>>>......................................

string Employee::get_first_name()const{
    return first_name;
}
string Employee::get_last_name() const{
    return last_name;
}
int Employee::get_personal_id() const{
    return personal_id;
}
Date Employee::get_birthday() const{
    return birthday;
}
long int Employee::get_basic_salary_received() const{
    return basic_salary_received;
}
string Employee::get_username()  const{
    return user_name;
}
string Employee::get_password() const{
    return password;
}
int Employee::get_leave_hours() const{
    return leave_hours;
}
int Employee::get_overtime_hours() const{
    return overtime_hours;
}
long int Employee::get_salary() const{
    return salary;
}



