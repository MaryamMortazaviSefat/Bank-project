#ifndef DATE_H
#define DATE_H


#include "iostream"
using namespace std;
class Date
{
    friend istream & operator>>(istream & in,Date &d);
    friend ostream & operator<<(ostream & in,Date &d);

public:
    //costructor
    Date();
    Date(int _day,int _month,int _year);

    //fuctions
    string date_to_string()const;   //for showing on ui  exp:2020/2/4
    string date_to_file_string()const;     //like operator <<

private:
    int day;
    int month;
    int year;
};

#endif // DATE_H
