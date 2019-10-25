#ifndef SUP_SCHOOL_ACTIVITY_H
#define SUP_SCHOOL_ACTIVITY_H

#include "Time.h"

class Activity {
    private:
        Time startTime;
        Time endTime;
        static unsigned int id;
    public:
        Activity(Time startTime,Time endTime);
        Time getStartTime();
        Time getEndTime();
        virtual int calcCost() const = 0;
        unsigned int getId() const;
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

class activityNonExistant : std::exception {
public:
    unsigned int id;
    activityNonExistant(unsigned int id){id = id;};
};

std::ostream & operator <<(std::ostream &out,const activityNonExistant &activity);

#endif //SUP_SCHOOL_ACTIVITY_H
