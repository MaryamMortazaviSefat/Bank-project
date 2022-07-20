#include "customer.h"
#include "ui_customer.h"

//...........................<<<< constructor >>>>.......................................

Customer::Customer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Customer)
{
    ui->setupUi(this);
}

Customer::Customer(string first_name,string last_name,string natinal_code,Date _birthday){

    username =set_username();
    firstname= first_name;
    lastname= last_name;
    natinalcode= natinal_code;
    birthday= _birthday;
    password= natinal_code;
    accounts="/";
    add_customer_in_file();
}

//...........................<<<< distructor >>>>........................................

Customer::~Customer()
{
    delete ui;
}

//..........................<<<< signal & slot >>>>......................................

void Customer::on_withdraw_clicked()
{
    string _account_number=ui->acc_num_withdraw->text().toStdString();
    int withdrawi=ui->mablagh_withdraw->text().toInt();

    bool check=false ;

    if(_account_number=="0")
    {
        check=false;
    }
    else if(_account_number!="0")
    {
        check = change_balance_in_current_object(_account_number,-withdrawi);
    }

    if(check){
    edit_object_in_file();
    QMessageBox error;
    error.setWindowTitle("نتیجه درخواست");
    string message="عملیات با موفقیت انجام شد\n  مبلغ برداشتی: ";

    string withdraw=to_string(withdrawi);
    for(int i=0;i<withdraw.size();i++)
    {
        message.push_back(withdraw[i]);
    }
    string tempp=" تومان ";
    for(int i=0;i<tempp.size();i++)
    {
        message.push_back(tempp[i]);
    }

    error.setText(QString::fromStdString(message));
    error.exec();
    set_info_in_customer_ui_withdraw();
    set_info_in_customer_ui_deposit();

    //add report
    string report=firstname;
    string temp="(customer) widthdrawed from account ";
    for(int i=0;i<temp.size();i++)
    {
        report.push_back(temp[i]);
    }
    temp=_account_number;
    temp.push_back(' ');
            //bayad dorost bbeshe
    for(int i=0;i<temp.size();i++)
    {
        report.push_back(temp[i]);
    }
    temp= to_string(withdrawi);
    for(int i=0;i<temp.size();i++)
    {
        report.push_back(temp[i]);
    }
    temp=" toman ";
    for(int i=0;i<temp.size();i++)
    {
        report.push_back(temp[i]);
    }

    add_report(report);


    }else if(!check)
    {
        QMessageBox error;
        error.setWindowTitle("نتیجه درخواست");
        string message="عملیات ناموفق\n  درخواست شما نا معتبر می باشد ";
        error.setText(QString::fromStdString(message));
        error.exec();
    }
}

void Customer::on_deposit_clicked()
{
    string _account_number=ui->acc_num_deposit->text().toStdString();
    int depositi=ui->mablagh_deposit->text().toInt();
    //set_accoun();

    bool check=false ;

    if(_account_number=="0")
    {
        check=false;
    }
    else if(_account_number!="0")
    {
        check = change_balance_in_current_object(_account_number,depositi);
        if(depositi>200000)
        {
            check=false;
        }
    }

    if(check)
    {
        edit_object_in_file();
        QMessageBox error;
        error.setWindowTitle("نتیجه درخواست");
        string message="عملیات با موفقیت انجام شد\n  مبلغ واریزی: ";

        string deposit=to_string(depositi);
        for(int i=0;i<deposit.size();i++)
        {
            message.push_back(deposit[i]);
        }
        string tempp=" تومان ";
        for(int i=0;i<tempp.size();i++)
        {
            message.push_back(tempp[i]);
        }

        error.setText(QString::fromStdString(message));
        error.exec();

        //add report
        string report=firstname;
        string temp="(customer) deposit to account ";
        for(int i=0;i<temp.size();i++)
        {
            report.push_back(temp[i]);
        }
        temp=_account_number;
        temp.push_back(' ');
        //bayad dorost bbeshe
        for(int i=0;i<temp.size();i++)
        {
            report.push_back(temp[i]);
        }
        temp= to_string(depositi);
        for(int i=0;i<temp.size();i++)
        {
            report.push_back(temp[i]);
        }
        temp=" toman ";
        for(int i=0;i<temp.size();i++)
        {
            report.push_back(temp[i]);
        }
        add_report(report);

        set_info_in_customer_ui_deposit();
        set_info_in_customer_ui_withdraw();
    }
    else if(!check)
    {
        QMessageBox error;
        error.setWindowTitle("نتیجه درخواست");
        string message="عملیات ناموفق\n  درخواست شما نا معتبر می باشد ";
        error.setText(QString::fromStdString(message));
        error.exec();
    }


}

void Customer::on_show_clicked()
{
    string _account_number=ui->show_acc->text().toStdString();
    ui->text_show->clear();
    ui->text_show->setPlainText(QString::fromStdString(return_account_info(_account_number)));
}

//..............................<<<<operators>>>>........................................

istream & operator>>(istream & in,Customer &e){

    in>>e.username>>e.firstname >>e.lastname>>e.natinalcode>>e.birthday>>e.password>>e.accounts;
    return in;
}

ostream & operator<<(ostream & out,Customer &e){

    out<<e.username<<" "<<e.firstname<<" "<<e.lastname<<" "<<e.natinalcode<<" "<<e.birthday<<" "<<e.password<<" "<<e.accounts<<"\n";
    return out;
}

//..................................<<<functions>>>......................................

void Customer::show(int number)
{
    ifstream in_file;
    in_file.open("E:/fi/customers_info.txt",ios::in);
    if(!in_file)
    {
    exit(EXIT_FAILURE);
    }

    for(int i=0;i<=number;i++)
    {
       in_file >> *this;
    }

    set_info_in_customer_ui_show();
    set_info_in_customer_ui_deposit();
    set_info_in_customer_ui_withdraw();
    QWidget::show();
}

void Customer::add_customer_in_file(){
    ofstream app_file;
    app_file.open("E:/fi/customers_info.txt",ios::app);

    if(!app_file)
    {
        exit(EXIT_FAILURE);
    }

    app_file<<*this;
    app_file.close();
}

void Customer::add_report(string &new_report){

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

string Customer::convert_account_to_st_for_ui_showinfo(){
    string result;
    result.resize(0);
    int count=0;
    string temp;
    for (int i=0;i<accounts.size();i++) {
        if(i==accounts.size()-1){
            return result;
        }
        //find number of accounts
        if(accounts[i]== '/' ){
                count++;
                temp="حساب ";
                for (int j=0;j<temp.size();j++) {
                    result.push_back(temp[j]);
                }
                temp=to_string(count);
                for (int j=0;j<temp.size();j++) {
                    result.push_back(temp[j]);
                }
                result.push_back('\n');
                //add account number of each account at result
                i++;
                temp.resize(0);
                temp="شماره حساب: ";
                for (int j=0;j<temp.size();j++) {
                    result.push_back(temp[j]);
                }
          temp.resize(0);
          while (accounts[i]!=',') {
              temp.push_back(accounts[i]);
              i++;
          }
          if(temp=="0")
          {
              temp="delete account";
          }
          for (int j=0;j<temp.size();j++) {
              result.push_back(temp[j]);
          }
            temp.resize(0);
            result.push_back('\n');
    }
    }
    return result;
}

string Customer::convert_account_st_ui_with_balance(){
    string result;
    result.resize(0);
    int count=0;
    string temp;
    for (int i=0;i<accounts.size();i++) {
        if(i==accounts.size()-1){
            return result;
        }
        //find number of accounts
        if(accounts[i]== '/' ){
                count++;
                temp="حساب ";
                for (int j=0;j<temp.size();j++) {
                    result.push_back(temp[j]);
                }
                temp=to_string(count);
                for (int j=0;j<temp.size();j++) {
                    result.push_back(temp[j]);
                }
                result.push_back('\n');
                //add account number of each account at result
                i++;
          temp.resize(0);
          temp="شماره حساب: ";
          for (int j=0;j<temp.size();j++) {
              result.push_back(temp[j]);
          }
          temp.resize(0);
          while (accounts[i]!=',') {
              temp.push_back(accounts[i]);
              i++;
          }
          if(temp=="0")
          {
              temp="delete account";
          }
          for (int j=0;j<temp.size();j++) {
              result.push_back(temp[j]);
          }
          result.push_back('\n');
            //add balance of each account at result
            temp.resize(0);
            i++;
            temp="موجودی حساب: ";
            for (int j=0;j<temp.size();j++) {
                result.push_back(temp[j]);
            }
            temp.resize(0);
            while (accounts[i]!=',') {
                temp.push_back(accounts[i]);
                i++;
            }
            for (int j=0;j<temp.size();j++) {
                result.push_back(temp[j]);
            }
            result.push_back('\n');
            //add status each account at result
            temp.resize(0);
            i++;
            temp="وضعیت حساب: ";
            for (int j=0;j<temp.size();j++) {
                result.push_back(temp[j]);
            }
            temp.resize(0);
            while (accounts[i]!='/') {
                temp.push_back(accounts[i]);
                i++;
            }
            i--;
            if(temp=="1"){
                temp="فعال";
            }else if(temp=="0"){
                temp="غیر فعال";
            }
            for (int j=0;j<temp.size();j++) {
                result.push_back(temp[j]);

            }
            temp.resize(0);
            result.push_back('\n');

    }
    }
    return result;
}

bool Customer::change_balance_in_current_object(string accountnumber,int change){
    int balance;
    string temp,result;
    bool flag=false;


    for (int i=0;i<accounts.size() && flag==false ;i++) {
        //find number of accounts
        if(accounts[i]== '/' ){
                //add account number of each account at result
                i++;
                temp.resize(0);
          while (accounts[i]!=',') {
              temp.push_back(accounts[i]);
              i++;
          }
              if(temp==accountnumber){
                  flag=true;
                  result.resize(0);
                  for (int j=0;j<=i;j++) {
                      result.push_back(accounts[j]);    //add befor
                  }
              }
            //add balance of each account at result

            temp.resize(0);
            i++;

            if(flag==true){
            while (accounts[i]!=',') {
                temp.push_back(accounts[i]);
                i++;
            }
                    balance=QString::fromStdString(temp).toInt();
                    balance+=change;
                    if(balance<0){return false;}
                    temp=to_string(balance);  //add current
                    for (int j=0;j<temp.size();j++) {
                        result.push_back(temp[j]);
                    }
                    for (int j=i;j<accounts.size();j++) {   //add after
                        result.push_back(accounts[j]);
                    }
            }
    }
    }

    if(flag)
    {
        accounts = result;
    }
        return flag;

}

void Customer::edit_object_in_file(){
    int line_number = username-999;
    string befor;
    string after;
    string tempst;
    Customer temp;

    fstream file{"E:/fi/customers_info.txt"};

    int i=0;
    for(i=1;i<line_number;i++)
    {
        file>>temp;
        tempst=temp.customer_to_string();
        for(int j=0;j<tempst.size();j++)
        {
        befor.push_back(tempst[j]);
        }
    }

    file>>temp; //currunt object in last mode

        while(file>>temp)
        {
            tempst=temp.customer_to_string();
            for(int j=0;j<tempst.size();j++)
            {
            after.push_back(tempst[j]);
            }

        }

        //seekp
        file.close();
        file.open("E:/fi/customers_info.txt" , ios::out);

        file<<befor<<*this<<after;


}

string Customer::customer_to_string(){

    string result;
    result.resize(0);

    string temp;
    temp.resize(0);

    //add personal id
    result=to_string(username);
    result.push_back(' ');

    //add first name
    for(int j=0;j<firstname.size();j++)
    {
    result.push_back(firstname[j]);
    }
    result.push_back(' ');

    //add last name
    for(int j=0;j<lastname.size();j++)
    {
    result.push_back(lastname[j]);
    }
    result.push_back(' ');

    //add natinalcode
    for(int j=0;j<natinalcode.size();j++)
    {
    result.push_back(natinalcode[j]);
    }
    result.push_back(' ');

    //add birthday
    temp=birthday.date_to_file_string();
    for(int j=0;j<temp.size();j++)
    {
    result.push_back(temp[j]);
    }
    result.push_back(' ');

    //add password
    for(int j=0;j<password.size();j++)
    {
    result.push_back(password[j]);
    }
    result.push_back(' ');

    //add acounsts
    for(int j=0;j<accounts.size();j++)
    {
    result.push_back(accounts[j]);
    }
    result.push_back('\n');

    return result;
}

string Customer::return_account_info(string accountnumber){
    string result;
    result.resize(0);
    int count=0;
    string temp;
    for (int i=0;i<accounts.size();i++) {
        if(i==accounts.size()-1){
            return result;
        }
        //find number of accounts
        if(accounts[i]== '/' ){
                count++;
                //add account number of each account at result
                i++;
          temp.resize(0);
          while (accounts[i]!=',') {
              temp.push_back(accounts[i]);
              i++;
          }
          if(temp==accountnumber){

              temp="حساب ";
              for (int j=0;j<temp.size();j++) {
                  result.push_back(temp[j]);
              }
              temp=to_string(count);
          for (int j=0;j<temp.size();j++) {
              result.push_back(temp[j]);
          }
          result.push_back('\n');
          temp="شماره حساب: ";
          for (int j=0;j<temp.size();j++) {
              result.push_back(temp[j]);
          }
          for (int j=0;j<accountnumber.size();j++) {
              result.push_back(accountnumber[j]);
          }
          result.push_back('\n');
            //add balance of each account at result
            temp.resize(0);
            i++;
            temp="موجودی حساب: ";
            for (int j=0;j<temp.size();j++) {
                result.push_back(temp[j]);
            }
            temp.resize(0);
            while (accounts[i]!=',') {
                temp.push_back(accounts[i]);
                i++;
            }
            for (int j=0;j<temp.size();j++) {
                result.push_back(temp[j]);
            }
            result.push_back('\n');
            //add status each account at result
            temp.resize(0);
            i++;
            temp="وضعیت حساب: ";
            for (int j=0;j<temp.size();j++) {
                result.push_back(temp[j]);
            }
            temp.resize(0);
            while (accounts[i]!='/') {
                temp.push_back(accounts[i]);
                i++;
            }
            i--;
            if(temp=="1"){
                temp="فعال";
            }else if(temp=="0"){
                temp="غیر فعال";
            }
            for (int j=0;j<temp.size();j++) {
                result.push_back(temp[j]);

            }
            temp.resize(0);
            result.push_back('\n');
                return result;
          }
    }
    }

}

bool Customer::delete_account_number(int _account_number){

    string temp,result;
    bool flag=false;
    for (int i=0;i<accounts.size() && flag==false ;i++) {
        if(i==accounts.size()-1){
        }
        //find number of accounts
        result.resize(0);
        for (int j=0;j<=i;j++) {
            result.push_back(accounts[j]);    //add befor
        }
        if(accounts[i]== '/' ){
                //find account number,check and delete
                i++;
                temp.resize(0);
          while (accounts[i]!=',') {
              temp.push_back(accounts[i]);
              i++;
          }
              if(temp==to_string(_account_number)){
                  flag=true;
                  temp.resize(0);
                  temp=to_string(0);
                  for (int j=0;j<temp.size();j++) {
                      result.push_back(temp[j]);
                  }
                  result.push_back(',');
              }
            //delete balance
            temp.resize(0);
            i++;
            if(flag==true){
            while (accounts[i]!=',') {
                temp.push_back(accounts[i]);
                i++;
            }
                    temp=to_string(0);
                    for (int j=0;j<temp.size();j++) {
                        result.push_back(temp[j]);
                    }
                    result.push_back(',');
                    // delete status
                    while (accounts[i]!='/') {
                        temp.push_back(accounts[i]);
                        i++;
                    }
                    temp.resize(0);
                    temp=to_string(0);
                    for (int j=0;j<temp.size();j++) {
                        result.push_back(temp[j]);
                    }
                    for (int j=i;j<accounts.size();j++) {   //add after
                        result.push_back(accounts[j]);
                    }
            }
    }
    }
    accounts = result;
    edit_object_in_file();
    return flag;

}

//....................................<<<seters>>>........................................

int Customer::set_username(){
    int result=0;

    ifstream in_file{"E:/fi/customers_info.txt",ios::in};


    //find number
    while (in_file>>*this)
    {
        result++;
    }

    in_file.close();

    result+= 1000;
    return result;
}

void Customer::set_info_in_customer_ui_show(){

    ui->text_show->clear();
    ui->text_show->insertPlainText(QString::fromStdString("\nنام:  "));
    ui->text_show->insertPlainText(QString::fromStdString(firstname));
    ui->text_show->insertPlainText( QString::fromStdString("\nنام خانوادگی:  "));
    ui->text_show->insertPlainText(QString::fromStdString(lastname));
    ui->text_show->insertPlainText( QString::fromStdString("\nشماره ملی:  "));
    ui->text_show->insertPlainText(QString::fromStdString(natinalcode));
    ui->text_show->insertPlainText( QString::fromStdString("\nتاریخ تولد:  "));
    ui->text_show->insertPlainText(QString::fromStdString(birthday.date_to_string()));
    ui->text_show->insertPlainText( QString::fromStdString("\nنام کاربری:  "));
    ui->text_show->insertPlainText(QString::fromStdString(to_string(username)));
    ui->text_show->insertPlainText( QString::fromStdString("\nگذرواژه:  "));
    ui->text_show->insertPlainText(QString::fromStdString(password));
    ui->text_show->insertPlainText( QString::fromStdString("\n"));
    string show_account_st = convert_account_to_st_for_ui_showinfo();
    ui->text_show->insertPlainText(QString::fromStdString(show_account_st));
}

void Customer::set_info_in_customer_ui_deposit(){
    ui->text_deposit->clear();
    string show_account_st = convert_account_st_ui_with_balance();
    ui->text_deposit->insertPlainText(QString::fromStdString(show_account_st));
}

void Customer::set_info_in_customer_ui_withdraw(){
    ui->text_withdraw->clear();
    string show_account_st = convert_account_st_ui_with_balance();
    ui->text_withdraw->insertPlainText(QString::fromStdString(show_account_st));
}

void Customer::set_accounts(string &_accounts){
    accounts=_accounts;
}

//......................................<<<geters>>>......................................

string Customer::get_firstname() const{
    return firstname;
}
string Customer::get_lastname() const{
    return lastname;
}
int Customer::get_username() const{
    return username;
}
string Customer::get_password() const{
    return password;
}
string Customer::get_natinal_code() const{
    return natinalcode;
}
Date Customer::get_birthday() const{
    return birthday;
}
string Customer::get_accounts() const{
    return accounts;
}
int Customer::get_the_counts_of_customer_accounts() {

    int count=0;

    for(int i=0;i<accounts.size();i++)
    {
        if(accounts[i]=='/')
        {
            count++;
        }
    }

    return count-1;
}



