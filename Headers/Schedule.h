#ifndef SUP_SCHOOL_SCHEDULE_H
#define SUP_SCHOOL_SCHEDULE_H

#include "Activity.h"

#include <map>
#include <vector>

struct CharacterCodes {
    unsigned char topRight = 187, topLeft = 201, downRight = 188, downLeft = 200;
    unsigned char topDownSimple = 205, topSeparation = 203, downSeparation = 202;
    unsigned char leftRightSimple = 186, leftSeparation = 204, rightSeparation = 185;
    unsigned char centreSeparation = 206;
};

class Schedule {
    public:
        Schedule();
        Schedule(vector <Activity*> Activities);
        void view();
    private:
        vector<vector<unsigned short>> Activities;
};

#endif //SUP_SCHOOL_SCHEDULE_H
