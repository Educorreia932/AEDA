#include "../Headers/Time.h"

Time::Time(){ //Monday at midnight
    this->hours = 0;
    this->minutes = 0;
    this->day = Weekday(0);
}

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
        default:
            return "";
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



ImpossibleTimeDiference::ImpossibleTimeDiference(Time startTime, Time endTime){
    startTime = startTime;
    endTime = endTime;
}

ostream &operator<<(ostream &out, const ImpossibleTimeDiference &times) {
    out << "The starting time of " << times.startTime << " is after " << times.endTime << endl;
    return out;
}


