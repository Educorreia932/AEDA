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

Time::Time(short day, short month, short year) {
    this->day = day;
    this->month = month;
    this->year = year;
    hours = 0;
    minutes = 0;
}

Time::Time(short day, short month, short year, short hours, short minutes) {
    this->day = day;
    this->month = month;
    this->year = year;
    this->hours = hours;
    this->minutes = minutes;
    //Check if it's valid date
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
    return t1.getDay() > t2.getDay() || 60 * t1.getHours() + t1.getMinutes() > 60 * t2.getHours() + t2.getMinutes();
}

bool operator <(Time const t1, Time const t2) {
    return t1.getDay() < t2.getDay() || 60 * t1.getHours() + t1.getMinutes() < 60 * t2.getHours() + t2.getMinutes();
}

bool operator ==(Time const t1, Time const t2) {
    return (t1.getDay() == t2.getDay() &&
            t1.getHours() == t2.getHours() &&
            t1.getMinutes() == t2.getMinutes() &&
            t1.getMonth() == t2.getMonth() &&
            t1.getYear() == t2.getYear() &&
            t1.getWeekday() == t2.getWeekday());
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
    /*
    short day = endTime.getDay() -  startTime.getDay();
    short month = endTime.getMonth() - startTime.getMonth();
    short year = endTime.getYear() - startTime.getYear();

    short time[5] = {};
    time[4] = minutes;
    time[3] = hours;
    time[2] = day;
    time[1] = month;
    time[0] = year;

    for(int i = 0; i < 4; i++){
        //i+1
        if(time[i] < 0 && time[i + 1] > 0){
            time[i]++;
            if(i == 0)
                time[i + 1] -= 12;
            else if(i == 1)
                time[i + 1] -= startTime.numberOfdays();
            else if(i == 2)
                time[i + 1] -= 24;
            else if(i == 3)
                time[i + 1] -= 60;
            continue;
        }
        else if(time[i] > 0 && time[i + 1] < 0) {
            time[i]--;
            if(i == 0)
                time[i + 1] += 12;
            else if(i == 1)
                time[i + 1] += startTime.numberOfdays();
            else if(i == 2)
                time[i + 1] += 24;
            else if(i == 3)
                time[i + 1] += 60;
            continue;
        }

        if(i >= 4){
            continue;
        }
        //i+2
        if(time[i] > 0 && time[i + 1] == 0){
            time[i]--;
            if(time[i + 2] < 0){
                if(i == 0) {
                    time[i + 1] += 11;
                    time[i + 2] += startTime.numberOfdays();
                    continue;
                }
                if(i == 1){
                    time[i + 1] += startTime.numberOfdays() - 1;
                    time[i + 2] += 24;
                    continue;
                }
                if(i == 2){
                    time[i + 1] += 23;
                    time[i + 2] += 60;
                    continue;
                }

            }
        }
        else if(time[i] < 0 && time[i + 1] == 0){
            if(time[i + 2] > 0){
                time[i]++;
                if(i == 0){
                    time[i + 1] -= 11;
                    time[i + 2] -= startTime.numberOfdays() - 1;
                    time[i + 3] -= 24;
                    continue;
                }
                if(i == 1){
                    time[i + 2] -= startTime.numberOfdays() - 1;
                    time[i + 3] -= 23;
                    time[i + 4] -= 60;
                    continue;
                }
            }
        }

        if(i >= 3){
            continue;
        }
        //i + 3
        if(time[i] > 0 && time[i + 1] == 0){
            if(time[i] > 0 && time[i + 2] == 0){
                if(time[i + 3] < 0){
                    time[i]--;
                    time[i + 1] += 11;
                    time[i + 2] += startTime.numberOfdays() - 1;
                    time[i + 3] += 23;
                    time[i + 4] += 60;
                    continue;
                }
            }
        }

        if(time[i] < 0 && time[i + 1] == 0){
            if(time[i] < 0 && time[i + 2] == 0){
                if(time[i + 3] > 0){
                    time[i]++;
                    time[i + 1] -= 11;
                    time[i + 2] -= startTime.numberOfdays() - 1;
                    time[i + 3] -= 23;
                    time[i + 4] -= 60;
                    continue;
                }
            }
        }

        if(i >= 2){
            continue;
        }
        //i + 4
        if(time[i] > 0 && time[i + 1] == 0){
            if(time[i + 2] == 0){
                if(time[i + 3] == 0){
                    if(time[i + 4] < 0){
                        time[i]--;
                        time[i + 1] += 11;
                        time[i + 2] += startTime.numberOfdays() - 1;
                        time[i + 3] += 23;
                        time[i + 4] += 60;
                        continue;
                    }
                }
            }
        }

        if(time[i] < 0 && time[i + 1] == 0){
            if(time[i + 2] == 0){
                if(time[i + 3] == 0){
                    if(time[i + 4] > 0){
                        time[i]++;
                        time[i + 1] -= 11;
                        time[i + 2] -= startTime.numberOfdays() - 1;
                        time[i + 3] -= 23;
                        time[i + 4] -= 60;
                        continue;
                    }
                }
            }
        }
    }
    deltaTime.setMinutes(time[4]);
    deltaTime.setHours(time[3]);
    deltaTime.setDay(time[2]);
    deltaTime.setMonth(time[1]);
    deltaTime.setYear(time[0]);
    return deltaTime;

    /*
    if(year < 0 &&  month > 0){
        year++;
        month -= 12;
    }
    if(year > 0 && month < 0){
        year--;
        month += 12;
    }
    if(month < 0 && day > 0){
        month++;
        day -= startTime.numberOfdays();
    }
    if(month > 0 && day < 0){
        month--;
        day -= startTime.numberOfdays();
    }
    if(day < 0 && hours > 0){
        day++;
        hours += 24;
    }
    if(day > 0 && hours < 0){
        day--;
        hours -= 24;
    }
    if(hours > 0 && minutes < 0){
        hours--;
        minutes -= 60;
    }
    if(hours > 0 && minutes < 0){
        hours--;
        minutes -= 60;
    }
    deltaTime.setMinutes(minutes);
    deltaTime.setHours(hours);
    deltaTime.setDay(day);
    deltaTime.setMonth(month);
    deltaTime.setYear(year);
    return deltaTime;

    if(minutes < 0){
        minutes += 60;
        hours--;
    }
    deltaTime.setMinutes(minutes);
    if(hours < 0){
        hours += 24;
        day--;
    }
    deltaTime.setHours(hours);

    if (day == 0){
        if(startTime.getMonth() == 1) {
            Time monthBeforestartTime = Time(1, 12, startTime.getYear() - 1, 0, 0);
            day = monthBeforestartTime.numberOfdays();
        }
        else{
            Time monthBeforestartTime = Time(1, startTime.getMonth() - 1, startTime.getYear(), 0, 0);
            day = monthBeforestartTime.numberOfdays();
        }
        month--;
    }
    deltaTime.setDay(day);

    if(month == 0){
        month += 12;
        year--;
    }
    deltaTime.setMonth(month);

    deltaTime.setYear(year);


    return deltaTime;*/
}
