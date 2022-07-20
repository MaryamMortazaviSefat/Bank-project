#include "date.h"

//...........................<<<< constructor >>>>.......................................

Date::Date()
{

}

//...........................<<<< distructor >>>>........................................

Date::Date(int _day,int _month,int _year){

    //check dates whith seter

    day=_day;
    month=_month;
    year=_year;
}

//..............................<<<<operators>>>>........................................

istream & operator>>(istream & in,Date &d){
    in>>d.year>>d.month>>d.day;
    return in;
}

ostream & operator<<(ostream & out,Date &d){
    out<<d.year<<" "<<d.month<<" "<<d.day;
    return out;
}

//..................................<<<functions>>>......................................

string Date::date_to_string()const{
    string result;
    //set year to result
    string st=to_string(year);
    result=st;

    //push back month to result
    result.push_back('/');
    st=to_string(month);
    for(int i=0;i<st.size();i++)
    {
        result.push_back(st[i]);
    }

    //push back day to result
    result.push_back('/');
    st=to_string(day);
    for(int i=0;i<st.size();i++)
    {
        result.push_back(st[i]);
    }

    return result;
}

string Date::date_to_file_string()const{
    string result;
    //set year to result
    string st=to_string(year);
    result=st;

    //push back month to result
    result.push_back(' ');
    st=to_string(month);
    for(int i=0;i<st.size();i++)
    {
        result.push_back(st[i]);
    }

    //push back day to result
    result.push_back(' ');
    st=to_string(day);
    for(int i=0;i<st.size();i++)
    {
        result.push_back(st[i]);
    }

    return result;
}
