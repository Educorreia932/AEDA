#ifndef SUP_SCHOOL_ACTIVITY_H
#define SUP_SCHOOL_ACTIVITY_H

#include "Time.h"

class Activity {
    private:
        Time startTime;
        Time endTime;
        static unsigned int id;
        string name;
    public:
        Activity(Time startTime,Time endTime,string name);
        Time getStartTime();
        Time getEndTime();
        virtual int calcCost() const = 0;
        unsigned int getId() const;
};

class Ride : public Activity {
    public:
        Ride(Time startTime,Time endTime,string name) : Activity(startTime,endTime,name){};
        int CalcCost() const;
};

class Lesson : public Activity {
    public:
    Lesson(Time startTime,Time endTime,string name) : Activity(startTime,endTime,name){};
    int CalcCost() const;
};

class StandUpPaddle : public Lesson {
    public:
        int CalcCost() const;
        StandUpPaddle(Time startTime,Time endTime,string name) : Lesson(startTime,endTime,name){};
};

class Surf : public Lesson {
    public:
        int CalcCost() const;
        Surf(Time startTime,Time endTime,string name) : Lesson(startTime,endTime,name){};
};

class Windsurf : public Lesson {
    public:
        int CalcCost() const;
        Windsurf(Time startTime,Time endTime,string name) : Lesson(startTime,endTime,name){};
};

class activityNonExistant : std::exception {
public:
    unsigned int id;
    activityNonExistant(unsigned int id){id = id;};
};

std::ostream & operator <<(std::ostream &out,const activityNonExistant &activity);

#endif //SUP_SCHOOL_ACTIVITY_H
