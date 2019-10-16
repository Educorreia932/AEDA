#ifndef AEDA_SUPSCHOOL_MASTER_TIME_H
#define AEDA_SUPSCHOOL_MASTER_TIME_H

#include <iomanip>
#include <iostream>

enum Weekday {

};

class Time{
    public:
        Time(unsigned short hours, unsigned short minutes);
        unsigned short GetHours() const;
        unsigned short GetMinutes() const;
        void SetHours(const unsigned short hours);
        void SetMinutes(const unsigned short minutes);
    private:
        unsigned short hours, minutes;
        Weekday day;
        friend ostream & operator<<(ostream &out, Time t);
        friend bool operator >(Time const t1, Time const t2);
        friend bool operator <(Time const t1, Time const t2);
};

bool operator >(Time const t1, Time const t2){
    return 60 * t1.GetHours() + t1.GetMinutes() > 60 * t2.GetHours() + t2.GetMinutes();
}

bool operator <(Time const t1, Time const t2){
    return 60 * t1.GetHours() + t1.GetMinutes() < 60 * t2.GetHours() + t2.GetMinutes();
}