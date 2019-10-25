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
}

Time::Time(unsigned short day, unsigned short month, unsigned short year) {
    this->day = day;
    this->month = month;
    this->year = year;
    hours = 0;
    minutes = 0;
}

Time::Time(unsigned short day, unsigned short month, unsigned short year, unsigned short hours, unsigned short minutes) {
    this->day = day;
    this->month = month;
    this->year = year;
    this->hours = hours;
    this->minutes = minutes;
    //Check if it's valid date
}

unsigned short Time::getYear() const {
    return year;
}

unsigned short Time::getMonth() const {
    return month;
}

unsigned short Time::getDay() const {
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

unsigned short Time::getHours() const {
    return hours;
}

unsigned short Time::getMinutes() const {
    return minutes;
}

void Time::setHours(const unsigned short hours) {
    this->hours = hours;
}

void Time::setMinutes(const unsigned short minutes) {
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
    return t1.getDay() > t2.getDay() || 60 * t1.getHours() + t1.getMinutes() > 60 * t2.getHours() + t2.getMinutes();
}

bool operator <(Time const t1, Time const t2) {
    return t1.getDay() < t2.getDay() || 60 * t1.getHours() + t1.getMinutes() < 60 * t2.getHours() + t2.getMinutes();
}

ostream &operator<<(ostream &out, Time t) {
    out << t.getDay() << '/' << t.getMonth() << '/' << t.getYear() << ' ' << t.getHours() << ':' << t.getMinutes();
                                                                            //Include leading zeros
    return out;
}

ImpossibleTimeDiference::ImpossibleTimeDiference(Time startTime, Time endTime){
    startTime = startTime;
    endTime = endTime;
}

ostream &operator<<(ostream &out, const ImpossibleTimeDiference &times) {
    out << "ERROR: The starting time of " << times.startTime << " is after " << times.endTime << endl;
    return out;
}
