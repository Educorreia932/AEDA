#ifndef SUP_SCHOOL_SCHEDULE_H
#define SUP_SCHOOL_SCHEDULE_H

#include "Activity.h"
#include "Auxiliary.h"
#include "Client.h"
#include "Teacher.h"

#include <map>

struct CharacterCodes {
    unsigned char topRight = 187, //╗
                  topLeft = 201, //╔
                  downRight = 188, //╝
                  downLeft = 200, //╚
                  topDownSimple = 205, //═
                  topSeparation = 203, //╦
                  downSeparation = 202, //╩
                  leftRightSimple = 186, //║
                  leftSeparation = 204, //╠
                  rightSeparation = 185, //╣
                  centreSeparation = 206; //╬
};

template <class T>
class Schedule {
    public:
        Schedule();
        Schedule(Time BeginDate, Time EndDate, const T *c);
        vector<map <Time, Activity*>> getActivities() const;
        Time getBeginDate() const;
        template <class T1>
        friend ostream &operator<<(ostream &out, const Schedule<T1> &s);
    private:
        Time BeginDate, EndDate;
        vector<map <Time, Activity*>> Activities;
};

#endif //SUP_SCHOOL_SCHEDULE_H
