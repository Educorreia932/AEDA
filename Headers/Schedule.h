#ifndef SUP_SCHOOL_SCHEDULE_H
#define SUP_SCHOOL_SCHEDULE_H

#include "Activity.h"
#include "Auxiliary.h"

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

class Schedule {
    public:
        Schedule();
        Schedule(const vector<Activity*> &Activities);
        Schedule(map <Time, Activity*> Activities);
        void view(Time Date, int width);
    private:
        map <Time, Activity*> Activities;
};

#endif //SUP_SCHOOL_SCHEDULE_H
