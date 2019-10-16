#include "../Headers/Time.h"

Time::Time(Weekday day, unsigned short hours, unsigned short minutes) {
    this->hours = hours;
    this->minutes = minutes;
    this->day = day;
}

unsigned short Time::getHours() const {
    return hours;
}

unsigned short Time::getMinutes() const {
    return minutes;
}

Weekday Time::getDay() const {
    return day;
}

//Can you do it without a switch case?
string Time::getDayString() const {
    switch (day) {
        case Monday:
            return "Monday";
        case Tuesday:
            return "Tuesday";
        case Wednesday:
            return "Wednesday";
        case Thursday:
            return "Thursday";
        case Friday:
            return "Friday";
        case Saturday:
            return "Saturday";
        case Sunday:
            return "Sunday";
    }
}

void Time::setHours(const unsigned short hours) {
    this->hours = hours;
}

void Time::setMinutes(const unsigned short minutes) {
    this->minutes = minutes;
}

bool operator >(Time const t1, Time const t2){
    return t1.getDay() > t2.getDay() || 60 * t1.getHours() + t1.getMinutes() > 60 * t2.getHours() + t2.getMinutes();
}

bool operator <(Time const t1, Time const t2){
    return t1.getDay() < t2.getDay() || 60 * t1.getHours() + t1.getMinutes() < 60 * t2.getHours() + t2.getMinutes();
}

ostream &operator<<(ostream &out, Time t) {
    out << t.getDayString() << " - " << t.getHours() << "h" << t.getMinutes() << "m";

    return out;
}
