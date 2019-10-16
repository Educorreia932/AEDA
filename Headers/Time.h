#ifndef AEDA_SUPSCHOOL_MASTER_TIME_H
#define AEDA_SUPSCHOOL_MASTER_TIME_H

#define stringify(name) # name

#include <iomanip>
#include <iostream>

using namespace std;

enum Weekday {
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
};

class Time{
    public:
        Time(Weekday day, unsigned short hours, unsigned short minutes);

        //Getters
        unsigned short getHours() const;
        unsigned short getMinutes() const;
        Weekday getDay() const;
        string getDayString() const;

        //Setters
        void setHours(const unsigned short hours);
        void setMinutes(const unsigned short minutes);
    private:
        unsigned short hours, minutes;
        Weekday day;
        friend ostream & operator<<(ostream &out, Time t);
        friend bool operator >(Time const t1, Time const t2);
        friend bool operator <(Time const t1, Time const t2);
};

#endif