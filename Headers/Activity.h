#ifndef SUP_SCHOOL_ACTIVITY_H
#define SUP_SCHOOL_ACTIVITY_H

#include "Time.h"

class Activity {
    private:
        Time startTime;
        Time endTime;
    public:
        Activity(Time startTime,Time endTime);
        Time getStartTime();
        Time getEndTime();
};

class Ride : public Activity {
};

class Lesson : public Activity {
};

class StandUpPaddle : public Lesson {
};

class Surf : public Lesson {
};

class Windsurf : public Lesson {
};

#endif //SUP_SCHOOL_ACTIVITY_H
