#ifndef AEDA_SUPSCHOOL_MASTER_TIME_H
#define AEDA_SUPSCHOOL_MASTER_TIME_H

#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class Time{
public:
    //Constructors
    Time(); //Today's Date
    Time (const string &t); //const In format DD/MM/AAAA hh:mm
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

class ImpossibleTimeDiference : std::exception {
public:
    Time startTime;
    Time endTime;
    ImpossibleTimeDiference(Time startTime, Time endTime);
};

ostream &operator<<(ostream &out, const ImpossibleTimeDiference &times);

#endif