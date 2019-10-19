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
        virtual int calcCost() const = 0;
};

class Ride : public Activity {
    public:
        Ride(Time startTime,Time endTime) : Activity(startTime,endTime){};
        int CalcCost() const;
};

class Lesson : public Activity {
    public:
    Lesson(Time startTime,Time endTime) : Activity(startTime,endTime){};
    int CalcCost() const;
};

class StandUpPaddle : public Lesson {
    public:
        int CalcCost() const;
        StandUpPaddle(Time startTime,Time endTime) : Lesson(startTime,endTime){};
};

class Surf : public Lesson {
    public:
        int CalcCost() const;
        Surf(Time startTime,Time endTime) : Lesson(startTime,endTime){};
};

class Windsurf : public Lesson {
    public:
        int CalcCost() const;
        Windsurf(Time startTime,Time endTime) : Lesson(startTime,endTime){};
};

#endif //SUP_SCHOOL_ACTIVITY_H
