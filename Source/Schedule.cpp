#include "../Headers/Schedule.h"


vector<string> Times = {"07:00", "07:45", "08:30", "09:15", "10:00", "10:45", "11:30", "12:15", "13:00", "13:45",
                        "14:30", "15:15", "16:00", "16:45", "17:30", "18:15", "19:00", "19:45", "20:30"};

Schedule::Schedule() {

}

Schedule::Schedule(const vector<Activity *> &Activities) {
    for (Activity* a : Activities) {
        Time t_aux = a->getStartTime(); //Use pointer/Macro
        Time t(t_aux.getDay(), t_aux.getMonth(), t_aux.getYear());

        //Use different positions for different times of the day
        this->Activities[t].push_back(a);
    }
}

Schedule::Schedule(map <Time, vector<Activity*>> Activities) {
    this->Activities = Activities;
}

//Overload << operator
void Schedule::view(Time Date) {
    CharacterCodes Chars;

    for (int i = 0; i < 20; i++) {
        if (!i) //First row
            cout << setw(8) << Chars.topLeft << string(50, Chars.topDownSimple) << Chars.topRight << endl
                 << setw(8) << Chars.leftRightSimple << setw(50) << Date.getWeekday() << Chars.leftRightSimple << endl
                 << setw(8) << Chars.leftSeparation << string(50, Chars.topDownSimple) << Chars.rightSeparation << endl;

        else if (i < 19)
            cout << setw(7) << Times[i - 1] <<Chars.leftRightSimple << setw(51) << Chars.leftRightSimple << endl
                 << setw(8) <<Chars.leftSeparation << string(50, Chars.topDownSimple) << Chars.rightSeparation << endl;

        else //Last row
            cout << setw(7) << Times[i - 1] << Chars.leftRightSimple << setw(51) << Chars.leftRightSimple << endl
                 << setw(8) << Chars.downLeft << string(50, Chars.topDownSimple) << Chars.downRight << endl;
    }

}
