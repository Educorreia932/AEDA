#include "../Headers/Schedule.h"

vector<string> Times = {"07:00", "07:45", "08:30", "09:15", "10:00", "10:45", "11:30", "12:15", "13:00", "13:45",
                        "14:30", "15:15", "16:00", "16:45", "17:30", "18:15", "19:00", "19:45", "20:30"};

Schedule::Schedule() {

}

Schedule::Schedule(Time BeginDate, Time EndDate, const Client *c) {
    map <Time, Activity*> day;
    this->BeginDate = BeginDate;
    this->EndDate = EndDate; // Could put ++ here?

    EndDate++;

    while (!BeginDate.sameDate(EndDate)) {
        for (auto a : c->getScheduleActivitiesByDate(BeginDate))
            day[a->getStartTime()] = a;

        BeginDate++;
        Activities.push_back(day);
        day.clear();
    }
}

vector<map<Time, Activity *>> Schedule::getActivities() const {
    return Activities;
}

Time Schedule::getBeginDate() const {
    return BeginDate;
}

ostream &operator<<(ostream &out, const Schedule &s) {
    CharacterCodes Chars;
    int width = 35;

    /*for (auto a : s.getActivities())
        if (a.second->getName().size() > width)
            width = a.second->getName().size();*/

    for (int i = 0; i <= 40; i++) {
        Time CurrentDate = s.getBeginDate();

        for (int j = 0; j < s.getActivities().size(); j++) {
            stringstream t1("");
            Time* t2;

            if (!j) {
                if (i % 2 == 0 && i != 0 && i != 40)
                    out << setfill (' ') << setw(7);

                else
                    out << setfill (' ') << setw(8);
            }

            switch (i) {
                case 0:
                    if (!j && j < s.getActivities().size() - 1)
                        out << Chars.topLeft << string(width, Chars.topDownSimple) << Chars.topSeparation;

                    else if (!j && j == s.getActivities().size() - 1)
                        out << Chars.topLeft << string(width, Chars.topDownSimple) << Chars.topRight << endl;

                    else if (j < s.getActivities().size() - 1)
                        out << Chars.topDownSimple << string(width, Chars.topDownSimple) << Chars.topSeparation;

                    else
                        out << Chars.topDownSimple << string(width, Chars.topDownSimple) << Chars.topRight << endl;

                    break;
                case 1:
                    if (!j)
                        out << Chars.leftRightSimple << setw(width) << centerString(width, CurrentDate.getWeekday()) << Chars.leftRightSimple;

                    else
                        out << setw(width + 1) << centerString(width, CurrentDate.getWeekday()) << Chars.leftRightSimple;

                    if (j == s.getActivities().size() - 1)
                        out << endl;
                    break;
                case 2:
                case 4:
                case 6:
                case 8:
                case 10:
                case 12:
                case 14:
                case 16:
                case 18:
                case 20:
                case 22:
                case 24:
                case 26:
                case 28:
                case 30:
                case 32:
                case 34:
                case 36:
                case 38:
                    if (!j)
                        out << Times[i / 2 - 1] << Chars.leftSeparation << string(width, Chars.topDownSimple);

                    else
                        out << string(width + 1, Chars.topDownSimple);

                    if (j < s.getActivities().size() - 1)
                        out << Chars.centreSeparation;

                    else
                        out << Chars.rightSeparation << endl;

                    break;
                case 3:
                case 5:
                case 7:
                case 9:
                case 11:
                case 13:
                case 15:
                case 17:
                case 19:
                case 21:
                case 23:
                case 25:
                case 27:
                case 29:
                case 31:
                case 33:
                case 35:
                case 37:
                case 39:
                    out << Chars.leftRightSimple;

                    t2 = new Time(CurrentDate.toString() + ' ' + Times[i / 2- 1]);

                    if (s.getActivities()[j].count(*t2))
                        t1 << s.getActivities()[j][*t2]->getName();

                    if (!j)
                         out << centerString(width, t1.str());

                    else
                        out << centerString(width + 1, t1.str());

                    if (j == s.getActivities().size() - 1)
                        out << Chars.leftRightSimple << endl;

                    break;
                case 40:
                    if (!j && j != s.getActivities().size() - 1)
                        out << Chars.downLeft << string(width, Chars.topDownSimple) << Chars.downSeparation;

                    else if (!j && j == s.getActivities().size() - 1)
                        out << Chars.downLeft << string(width, Chars.topDownSimple) << Chars.downRight << endl;

                    else if (j < s.getActivities().size() - 1)
                        out << string(width + 1, Chars.topDownSimple) << Chars.downSeparation;

                    else
                        out << string(width + 1, Chars.topDownSimple) << Chars.downRight << endl;

                    break;
            }

            CurrentDate++;
        }
    }

    return out;
}




