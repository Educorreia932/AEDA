#ifndef AEDA_SUPSCHOOL_MASTER_TIME_H
#define AEDA_SUPSCHOOL_MASTER_TIME_H

#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Time{
    public:
        //Constructors
        Time(); //Today's Date
        Time(const string &t); //const In format DD/MM/AAAA hh:mm
        Time(short day, short month, short year);
        Time(short day, short month, short year, short hours, short minutes);

        //Getters
        short getYear() const;
        short getMonth() const;
        short getDay() const;
        string getWeekday() const;
        short getHours() const;
        short getMinutes() const;

        //Setters
        void setYear(const short year);
        void setMonth(const short month);
        void setDay(const short day);
        void setHours(const short hours);
        void setMinutes(const short minutes);

        bool sameDate(Time Date) const;
        string toString() const;

        Time operator++(int);
    private:
        short year, month, day, hours, minutes;

        int numberOfdays() const;
        bool isBissextile() const;
        int dayOfweek() const;

        //Operators
        friend ostream & operator<<(ostream &out, Time t);
        friend bool operator >(Time const t1, Time const t2);
        friend bool operator <(Time const t1, Time const t2);
        friend bool operator ==(Time const t1, Time const t2);
        friend Time operator -(Time const startTime, Time const endTime);
};

/*! \cond */

class InvalidDate : exception {
    string msg;
public:
    InvalidDate(string msg){this->msg = msg;}
    string getMsg() const{return msg;}
};

class ImpossibleTimeDifference: std::exception{
    Time startTime;
    Time endTime;
public:
    ImpossibleTimeDifference(Time startTime, Time endTime){
        this->startTime = startTime;
        this->endTime = endTime;
    }
    Time getStartTime() const{
        return startTime;
    }
    Time getEndTime() const{
        return endTime;
    }
};


#endif