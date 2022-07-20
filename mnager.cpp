#include "mnager.h"
#include "ui_mnager.h"

//...........................<<<< constructor >>>>.......................................

Mnager::Mnager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Mnager)
{
    ui->setupUi(this);
}

//...........................<<<< distructor >>>>........................................

Mnager::~Mnager()
{
    delete ui;
}

//..........................<<<< signal & slot >>>>......................................

void Mnager::on_pushButton_apply_leave_4_clicked()
{
    //change -->object of manager
    manager.set_leave_hours(manager.get_leave_hours()+ ui->leave_hour_4->text().toInt());
    manager.calculate_salary();

    //set manager to -->file
    set_new_manger_in_file();

    //set new info in --> ui
    set_info_in_manager_ui();

    //show message box
    QMessageBox error;
    error.setWindowTitle("نتیجه درخواست");
    string message="با درخواست شما موافقت شد؛\n مرخصی شما تا کنون: ";

    string hour_st=to_string(manager.get_leave_hours());
    for(int i=0;i<hour_st.size();i++)
    {
        message.push_back(hour_st[i]);
    }

    message.push_back('h');

    error.setText(QString::fromStdString(message));
    error.exec();

    //make & add report
    string report=manager.get_first_name();
    string temp="(manager) get ";
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

void Mnager::on_pushButton_apply_overtime_4_clicked()
{
    bool flag=true;

    if((manager.get_overtime_hours()+ ui->overtime_hour_4->text().toInt())>12)
    {
        flag=false;

        QMessageBox error_ceiling;
        error_ceiling.setWindowTitle("خطا");
        string message="با درخواست شما معتبر نمی باشد؛\n اضافه کار شما تا کنون: ";

        string hour_st=to_string(manager.get_overtime_hours());
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
        //change -->object of manager
        manager.set_overtime_hours(manager.get_overtime_hours()+ ui->overtime_hour_4->text().toInt());
        manager.calculate_salary();

        //set manager to -->file
        set_new_manger_in_file();

        //set new info in --> ui
        set_info_in_manager_ui();

        //show message box
        QMessageBox error;
        error.setWindowTitle("نتیجه درخواست");
        string message="با درخواست شما موافقت شد؛\n اضافه کار شما تا کنون: ";

        string hour_st=to_string(manager.get_overtime_hours());
        for(int i=0;i<hour_st.size();i++)
        {
            message.push_back(hour_st[i]);
        }

        message.push_back('h');

        error.setText(QString::fromStdString(message));
        error.exec();

        //make & add report
        string report=manager.get_first_name();
        string temp="(manager) get ";
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

void Mnager::on_pushButton_show_customer_info_4_clicked()
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
        string report=manager.get_first_name();
        string temp="(manager) saw the info of ";
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

void Mnager::on_pushButton_open_account_4_clicked()
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

           // ui->cumtomer_money_for_open_account_8->setText(QString::fromStdString(to_string (current.get_username())));

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
            string report=manager.get_first_name();
            string temp="(manager) opened the acconunt whit ";
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

void Mnager::on_pushButton_delete_account_4_clicked()
{
    Customer current;
    bool found=false;

    string customer_natinalcode=ui->cumtomer_natinal_code_delete_account_4->text().toStdString();
    int account_number=ui->cumtomer_money_for_delete_account->text().toInt();

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
            string report=manager.get_first_name();
            string temp="(manager) deleted the acconunt whit ";
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

void Mnager::on_Button_show_employee_info_clicked()
{
    //it begin from 1
    int line_number =ui->input_employees_personalcode->text().toInt()-99;
    Employee temp;
    string info;
    bool found=false;

    //open file
    fstream file{"E:/fi/employees_info.txt"};

    for(int i=0;i<line_number;i++)
    {
        file>>temp;
    }

    //clear last info
    ui->employee_info_formanager->clear();

    if(temp.get_personal_id()==0)
    {
        show_exeption_employee_layout();
    }
    else if(temp.get_personal_id()!=0)
    {

        //set employee info on ui
        ui->employee_info_formanager->insertPlainText(QString::fromStdString("\nنام:  "));
        ui->employee_info_formanager->insertPlainText(QString::fromStdString(temp.get_first_name()));
        ui->employee_info_formanager->insertPlainText( QString::fromStdString("\nنام خانوادگی:  "));
        ui->employee_info_formanager->insertPlainText(QString::fromStdString(temp.get_last_name()));
        ui->employee_info_formanager->insertPlainText( QString::fromStdString("\nکد پرسنلی:  "));
        ui->employee_info_formanager->insertPlainText(QString::fromStdString(to_string(temp.get_personal_id())));
        ui->employee_info_formanager->insertPlainText( QString::fromStdString("\nتاریخ تولد:  "));
        ui->employee_info_formanager->insertPlainText(QString::fromStdString(temp.get_birthday().date_to_string()));
        ui->employee_info_formanager->insertPlainText( QString::fromStdString("\nپایه حقوقی:  "));
        ui->employee_info_formanager->insertPlainText(QString::fromStdString(to_string(temp.get_basic_salary_received())));
        ui->employee_info_formanager->insertPlainText( QString::fromStdString("\nنام کاربری:  "));
        ui->employee_info_formanager->insertPlainText(QString::fromStdString(temp.get_username()));
        ui->employee_info_formanager->insertPlainText( QString::fromStdString("\nگذرواژه:  "));
        ui->employee_info_formanager->insertPlainText(QString::fromStdString(temp.get_password()));
        ui->employee_info_formanager->insertPlainText( QString::fromStdString("\nساعات مرخصی:  "));
        ui->employee_info_formanager->insertPlainText(QString::fromStdString(to_string(temp.get_leave_hours())));
        ui->employee_info_formanager->insertPlainText( QString::fromStdString("\nساعات اضافه کار:  "));
        ui->employee_info_formanager->insertPlainText(QString::fromStdString(to_string(temp.get_overtime_hours())));
        ui->employee_info_formanager->insertPlainText( QString::fromStdString("\n\nحقوق دریافتی:  "));
        ui->employee_info_formanager->insertPlainText(QString::fromStdString(to_string(temp.get_salary())));

    }

    //close file
    file.close();

    //make & add report
    string report=manager.get_first_name();
    string st ="(manager) saw the info of ";
    for(int i=0;i<st.size();i++)
    {
        report.push_back(st[i]);
    }
    st=temp.get_first_name();
    for(int i=0;i<st.size();i++)
    {
        report.push_back(st[i]);
    }
    st="(employee) ";
    for(int i=0;i<st.size();i++)
    {
        report.push_back(st[i]);
    }
    add_report(report);
}

void Mnager::on_pushButton_add_employee_clicked()
{
   string employee_natinal_code=ui->employee_natinal_code->text().toStdString();
   if(employee_natinal_code.size()==10)
{
       string employee_first_name=ui->employee_firstname_3->text().toStdString();
       string employee_last_name=ui->employee_lastname_3->text().toStdString();
       int day=ui->employee_birthday_day->text().toInt();
       int month=ui->employee_birthday_month->text().toInt();
       int year=ui->employee_birthday_year->text().toInt();
       Date employee_birthday(day,month,year);



       //construct new employee add in file
       Employee new_employee(employee_first_name,employee_last_name,employee_natinal_code,employee_birthday,4000000);

       string employee_personal_id=to_string(new_employee.get_personal_id());
       string employee_user_name=new_employee.get_username();
       string employee_password=new_employee.get_password();



       //message for personal id , username & password

       //personal id
       string message="  کد پرسنلی شما: ";
       string temp=employee_personal_id;
       for(int i=0;i<temp.size();i++)
       {
           message.push_back(temp[i]);
       }

       //user name
       temp="\n  نام کاربری شما: ";
       for(int i=0;i<temp.size();i++)
       {
           message.push_back(temp[i]);
       }
       temp=employee_user_name;
       for(int i=0;i<temp.size();i++)
       {
           message.push_back(temp[i]);
       }

       //password
       temp="\n  گذرواژه شما: ";
       for(int i=0;i<temp.size();i++)
       {
           message.push_back(temp[i]);
       }
       temp=employee_password;
       for(int i=0;i<temp.size();i++)
       {
           message.push_back(temp[i]);
       }

      show_message_add_employee(message,new_employee);
   }
   else if(employee_natinal_code.size()!=10)
   {
       QMessageBox error;
       error.setWindowTitle("خطا");
       error.setText("کدملی وارد شده نامعتبر می باشد.");
       error.exec();
   }

}

void Mnager::on_Button_layingout_clicked()
{
    int line_number= ui->input_employees_personalcode_layingout->text().toInt()- 99;  //it begin from 1
    string befor;
    string after;
    string tempst;
    Employee temp;
    Employee current_in_last_mode;

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

    file>>current_in_last_mode; //current object in last mode

    if(temp.get_personal_id()==0)
    {
        show_exeption_employee_layout();
    }
    else if(temp.get_personal_id()!=0)
    {
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
        file.open("E:/fi/employees_info.txt" , ios::out);

        file<<befor<<0<<" n n "<<0<<" "<<0<<" "<<0<<" "<<0<<" n n "<<" "<<0<<" "<<0<<" "<<0<<"\n"<<after;

        //show message box
        QMessageBox result;
        result.setWindowTitle("نتیجه درخواست");
        result.setText("عملیات با موفقیت انجام شد.");
        result.exec();


        //make & add report
        string report=manager.get_first_name();
        string st="(manager) dismissed ";
        for(int i=0;i<st.size();i++)
        {
            report.push_back(st[i]);
        }
        st=current_in_last_mode.get_first_name();
        for(int i=0;i<st.size();i++)
        {
            report.push_back(st[i]);
        }
        st="(employee) with ";
        for(int i=0;i<st.size();i++)
        {
            report.push_back(st[i]);
        }
        st=current_in_last_mode.get_password();
        for(int i=0;i<st.size();i++)
        {
            report.push_back(st[i]);
        }
        st=" natinal code from bank ";
        for(int i=0;i<st.size();i++)
        {
            report.push_back(st[i]);
        }

        add_report(report);


    }

    file.close();

}

//..................................<<<functions>>>......................................

void Mnager::show_message_add_employee(string message, const Employee &new_employee){
    QMessageBox error;
    error.setWindowTitle("نتیجه درخواست");
    error.setText(QString::fromStdString(message));
    error.exec();

    //make & add report
    string report=manager.get_first_name();
    string st="(manager) hired ";
    for(int i=0;i<st.size();i++)
    {
        report.push_back(st[i]);
    }
    st=new_employee.get_first_name();
    for(int i=0;i<st.size();i++)
    {
        report.push_back(st[i]);
    }
    st=" as an employee with ";
    for(int i=0;i<st.size();i++)
    {
        report.push_back(st[i]);
    }
    st=new_employee.get_password();
    for(int i=0;i<st.size();i++)
    {
        report.push_back(st[i]);
    }
    st=" natinal code in bank ";
    for(int i=0;i<st.size();i++)
    {
        report.push_back(st[i]);
    }

    add_report(report);
}

void Mnager::show(int number){

    if(number==-1)
    {
        set_info_in_manager_ui();
        QWidget::show();
    }
}

void Mnager::show_exeption_employee_layout(){

    QMessageBox error;
    error.setWindowTitle("خطا");
    error.setText("این کارمند اخراج شده است.");
    error.exec();
}

void Mnager::add_report(string new_report){

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

//....................................<<<seters>>>........................................

void Mnager::set_info_in_manager_ui(){

    ifstream in_file;
    in_file.open("E:/fi/manager_info.txt",ios::in);
    if(!in_file)
    {
        exit(EXIT_FAILURE);
    }
    in_file>>manager;
    in_file.close();

    //leave hours
    ui->employee_firstname->setText(QString::fromStdString(manager.get_first_name()));
    ui->employee_lastname->setText(QString::fromStdString(manager.get_last_name()));

    //overtime hours
    ui->employee_firstname_2->setText(QString::fromStdString(manager.get_first_name()));
    ui->employee_lastname_2->setText(QString::fromStdString(manager.get_last_name()));

    ui->employee_info_4->clear();
    ui->employee_info_4->insertPlainText(QString::fromStdString("\nنام:  "));
    ui->employee_info_4->insertPlainText(QString::fromStdString(manager.get_first_name()));
    ui->employee_info_4->insertPlainText( QString::fromStdString("\nنام خانوادگی:  "));
    ui->employee_info_4->insertPlainText(QString::fromStdString(manager.get_last_name()));
    ui->employee_info_4->insertPlainText( QString::fromStdString("\nکد پرسنلی:  "));
    ui->employee_info_4->insertPlainText(QString::fromStdString(to_string( manager.get_personal_id())));
    ui->employee_info_4->insertPlainText( QString::fromStdString("\nتاریخ تولد:  "));
    ui->employee_info_4->insertPlainText(QString::fromStdString(manager.get_birthday().date_to_string()));
    ui->employee_info_4->insertPlainText( QString::fromStdString("\nپایه حقوقی:  "));
    ui->employee_info_4->insertPlainText(QString::fromStdString(to_string(manager.get_basic_salary_received())));
    ui->employee_info_4->insertPlainText( QString::fromStdString("\nنام کاربری:  "));
    ui->employee_info_4->insertPlainText(QString::fromStdString(manager.get_username()));
    ui->employee_info_4->insertPlainText(QString::fromStdString("\nگذرواژه:  "));
    ui->employee_info_4->insertPlainText(QString::fromStdString(manager.get_password()));
    ui->employee_info_4->insertPlainText(QString::fromStdString("\nساعات مرخصی:  "));
    ui->employee_info_4->insertPlainText(QString::fromStdString(to_string(manager.get_leave_hours())));
    ui->employee_info_4->insertPlainText( QString::fromStdString("\nساعات اضافه کار:  "));
    ui->employee_info_4->insertPlainText(QString::fromStdString(to_string(manager.get_overtime_hours())));
    ui->employee_info_4->insertPlainText( QString::fromStdString("\n\nحقوق دریافتی:  "));
    ui->employee_info_4->insertPlainText(QString::fromStdString(to_string(manager.get_salary())));

}

void Mnager::set_new_manger_in_file(){

     manager.calculate_salary();
     ofstream out_file;
     out_file.open("E:/fi/manager_info.txt",ios::out);
     if(!out_file)
     {
         exit(EXIT_FAILURE);
     }

     out_file<<manager;
     out_file.close();

}








