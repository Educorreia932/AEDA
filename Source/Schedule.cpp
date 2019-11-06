#include "../Headers/Schedule.h"

vector<string> Times = {"07:00", "07:45", "08:30", "09:15", "10:00", "10:45", "11:30", "12:15", "13:00", "13:45",
                        "14:30", "15:15", "16:00", "16:45", "17:30", "18:15", "19:00", "19:45", "20:30"};

Schedule::Schedule() {

}

Schedule::Schedule(const vector<Activity *> &Activities) {
    for (auto a : Activities) {;
        //Use different positions for different times of the day
        this->Activities[a->getStartTime()] = a;
    }
}

Schedule::Schedule(map <Time, Activity*> Activities) {
    this->Activities = Activities;
}

//Overload << operator
void Schedule::view(Time Date, int width) {
    CharacterCodes Chars;

    for (int i = 0; i < 20; i++) {
        if (!i) //First row
            cout << setw(8) << Chars.topLeft << string(width, Chars.topDownSimple) << Chars.topRight << endl
                 << setw(8) << Chars.leftRightSimple << setw(width) << centerString(width, Date.getWeekday()) << Chars.leftRightSimple << endl
                 << setw(7) << Times[i] << Chars.leftSeparation << string(width, Chars.topDownSimple) << Chars.rightSeparation << endl;

        else if (i < 19) {
            stringstream t1("");
            Time t2("18/10/2019 " + Times[i]);

            if (Activities.count(t2))
                t1 << Activities[t2]->getName() << ' ' << Activities[t2]->getId();

            cout << setw(8) << Chars.leftRightSimple << centerString(width, t1.str()) << Chars.leftRightSimple << endl
                 << setw(7) << Times[i]  <<Chars.leftSeparation << string(width, Chars.topDownSimple) << Chars.rightSeparation << endl;
        }

        else //Last row
            cout << setw(8) << Chars.leftRightSimple << setw(width + 1) << Chars.leftRightSimple << endl
                 << setw(8) << Chars.downLeft << string(width, Chars.topDownSimple) << Chars.downRight << endl;
    }
}
