#include "../Headers/Time.h"

Time::Time() { //Today's date and hour
    time_t now = time(0);
    tm *ltm = localtime(&now);

    year = ltm->tm_year + 1900;
    month = ltm->tm_mon + 1;
    day = ltm->tm_mday;
    hours = ltm->tm_hour;
    minutes = ltm->tm_min;
}

Time::Time(const string& t) {
    char separator;

    stringstream s(t);
    //What about space " " ?
    s >> day >> separator >> month >> separator >> year >> hours >> separator >> minutes;

    //Check if it's valid date
    try {
        if (year < 0) {
            throw InvalidDate("Invalid string.\n");
        }
        if(month <= 0 || month > 12){
            throw InvalidDate("Invalid string.\n");
        }
        if(day <= 0 || day > numberOfdays()){
            throw InvalidDate("Invalid string.\n");
        }
        if(hours < 0 || hours >= 24){
            throw InvalidDate("Invalid string.\n");
        }
        if(minutes < 0 || minutes >= 60){
            throw InvalidDate("Invalid string.\n");
        }
    }
    catch(InvalidDate &e) {
        throw e;
    }
}

Time::Time(short day, short month, short year) {
    this->day = day;
    this->month = month;
    this->year = year;
    hours = 0;
    minutes = 0;
    //Check if it's valid date
    try{
        if (year < 0) {
            throw InvalidDate("Invalid year.\n");
        }
        if(month <= 0 || month > 12){
            throw InvalidDate("Invalid Month.\n");
        }
        if(day <= 0 || day > numberOfdays()){
            throw InvalidDate("Invalid Day.\n");
        }
    }
    catch(InvalidDate &a){
        cerr << a.getMsg();
    }
}

Time::Time(short day, short month, short year, short hours, short minutes) {
    this->day = day;
    this->month = month;
    this->year = year;
    this->hours = hours;
    this->minutes = minutes;
    //Check if it's valid date
    try {
        if (year < 0) {
            throw InvalidDate("Invalid year.\n");
        }
        if(month <= 0 || month > 12){
            throw InvalidDate("Invalid Month.\n");
        }
        if(day <= 0 || day > numberOfdays()){
            throw InvalidDate("Invalid Day.\n");
        }
        if(hours < 0 || hours >= 24){
            throw InvalidDate("Invalid Hour.\n");
        }
        if(minutes < 0 || minutes >= 60){
            throw InvalidDate("Invalid Minute.\n");
        }
    }
    catch(InvalidDate &a){
        cerr << a.getMsg();
    }
}

short Time::getYear() const {
    return year;
}

short Time::getMonth() const {
    return month;
}

short Time::getDay() const {
    return day;
}

//Implement as map?
string Time::getWeekday() const {
    switch(dayOfweek()) {
        case 0:
            return "Saturday";
        case 1:
            return "Sunday";
        case 2:
            return "Monday";
        case 3:
            return "Tuesday";
        case 4:
            return "Wednesday";
        case 5:
            return "Thursday";
        case 6:
            return "Friday";
    }

    return "N/A";
}

short Time::getHours() const {
    return hours;
}

short Time::getMinutes() const {
    return minutes;
}

void Time::setYear(const short year) {
    this->year = year;
}

void Time::setMonth(const short month) {
    this->month = month;
}

void Time::setDay(const short day) {
    this->day = day;
}

void Time::setHours(const short hours) {
    this->hours = hours;
}

void Time::setMinutes(const short minutes) {
    this->minutes = minutes;
}

bool Time::isBissextile() const {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int Time::numberOfdays() const {
    switch (month) {
        case 2:
            if (isBissextile())
                return 29;
            else
                return 28;
        case 4:
            return 30;
        case 6:
            return 30;
        case 9:
            return 30;
        case 11:
            return 31;
        default:
            return 31;
    }
}

int Time::dayOfweek() const {
    int c;

    switch (month) {
        case 1:
            if (isBissextile()) {
                c = 6;
                break;
            }

            else {
                c = 0;
                break;
            }

        case 2:
            if (isBissextile()) {
                c = 2;
                break;
            }

            else {
                c = 3;
                break;
            }

        case 3:
            c = 3;
            break;

        case 4:
            c = 6;
            break;

        case 5:
            c = 1;
            break;

        case 6:
            c = 4;
            break;

        case 7:
            c = 6;
            break;

        case 8:
            c = 2;
            break;

        case 9:
            c = 5;
            break;

        case 10:
            c = 0;
            break;

        case 11:
            c = 3;
            break;

        case 12:
            c = 5;
            break;

        default:
            break;
    }

    int a = year % 100;
    int s = year / 100;

    return ((int)((5 * a) / 4) + c + day - 2 * (s % 4)) % 7;
}

bool operator >(Time const t1, Time const t2) { //Include year/day/month
    return !(t1 < t2) && !(t1 == t2);
}

bool operator <(Time const t1, Time const t2) {
    if (t1.getYear() < t2.getYear())
        return true;

    else if (t1.getYear() == t2.getYear() && t1.getMonth() < t2.getMonth())
        return true;

    else if (t1.getYear() == t2.getYear() && t1.getMonth() == t2.getMonth() && t1.getDay() < t2.getDay())
        return true;

    else if (t1.getYear() == t2.getYear() && t1.getMonth() == t2.getMonth() && t1.getDay() == t2.getDay() && t1.getHours() < t2.getHours())
        return true;

    else if (t1.getYear() == t2.getYear() && t1.getMonth() == t2.getMonth() && t1.getDay() == t2.getDay() && t1.getHours() == t2.getHours() && t1.getMinutes() < t2.getMinutes())
        return true;

    return false;
}

bool operator ==(Time const t1, Time const t2) {
    return (t1.getDay() == t2.getDay() &&
            t1.getHours() == t2.getHours() &&
            t1.getMinutes() == t2.getMinutes() &&
            t1.getMonth() == t2.getMonth() &&
            t1.getYear() == t2.getYear());
}

ostream &operator<<(ostream &out, Time t) {
    out << setfill('0') << setw(2) << t.getDay() << '/' // Day
        << setfill('0') << setw(2) << t.getMonth() <<  '/' // Month
        << t.getYear() // Year
        << ' ' << setfill('0') << setw(2) << t.getHours()
        << ':' << setfill('0') << setw(2) << t.getMinutes(); // Hours and Minutes

    return out;
}

Time operator -(Time const startTime, Time const endTime) {

    Time deltaTime;
    short minutes = endTime.getMinutes() - startTime.getMinutes();
    short hours = endTime.getHours() - startTime.getHours();

    if (hours > 0 && minutes < 0) {
        hours--;
        minutes += 60;
    }
    if (hours < 0 && minutes > 0) {
        hours++;
        minutes -= 60;
    }
    deltaTime.setYear(0);
    deltaTime.setMonth(0);
    deltaTime.setDay(1);
    deltaTime.setHours(hours);
    deltaTime.setMinutes(minutes);
    return deltaTime;
}

bool Time::sameDate(Time Date) const {
    return day == Date.getDay() && month == Date.getMonth() && year == Date.getYear();
}

string Time::toString() const {
    stringstream result;

    result << day << '/' << month << '/' << year;

    return result.str();
}

Time Time::operator++(int) {
    if (day == numberOfdays()) {
        day = 1;

        if (month == 12) {
            month = 1;
            year++;
        }

        else
            month++;
    }

    else {
        day++;
    }

    return *this;
}

