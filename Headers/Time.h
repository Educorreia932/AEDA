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
        Time(unsigned short day, unsigned short month, unsigned short year);
        Time(unsigned short day, unsigned short month, unsigned short year, unsigned short hours, unsigned short minutes);

        //Getters
        unsigned short getYear() const;
        unsigned short getMonth() const;
        unsigned short getDay() const;
        string getWeekday() const;
        unsigned short getHours() const;
        unsigned short getMinutes() const;

        //Setters
        void setHours(const unsigned short hours);
        void setMinutes(const unsigned short minutes);
    private:
        unsigned short year, month, day, hours, minutes;

        int numberOfdays() const;
        bool isBissextile() const;
        int dayOfweek() const;

        //Operators
        friend ostream & operator<<(ostream &out, Time t);
        friend bool operator >(Time const t1, Time const t2);
        friend bool operator <(Time const t1, Time const t2);
        friend bool operator ==(Time const t1, Time const t2);
};

class ImpossibleTimeDiference : std::exception {
        public:
            Time startTime;
            Time endTime;
            ImpossibleTimeDiference(Time startTime, Time endTime);
};

ostream &operator<<(ostream &out, const ImpossibleTimeDiference &times);

#endif