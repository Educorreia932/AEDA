#ifndef SUP_SCHOOL_ACTIVITY_H
#define SUP_SCHOOL_ACTIVITY_H

#include "Time.h"

class Activity {
    private:
        string name;
        unsigned int id;
        static unsigned int last_id;
        Time startTime;
        Time endTime;

    public:
        Activity();
        Activity(Time startTime,Time endTime,string name);

        //Getters
        Time getStartTime();
        Time getEndTime();
        string getName() const;
        unsigned int getId() const;

        //Setters
        void setName(string name);
        void setID(unsigned int id);
        void setStartTime(string time);
        void setEndTime(string time);

        virtual unsigned int CalcCost() const;
};

class Ride : public Activity {
    protected:
        unsigned int cost;
    public:
        Ride(Time startTime,Time endTime,string name) : Activity(startTime,endTime,name){};
        unsigned int CalcCost() const;
};

class Lesson : public Activity {
    public:
    Lesson(Time startTime,Time endTime,string name) : Activity(startTime,endTime,name){};
    unsigned int CalcCost() const;
};

class StandUpPaddle : public Lesson {
    public:
    unsigned int CalcCost() const;
    StandUpPaddle(Time startTime,Time endTime,string name) : Lesson(startTime,endTime,name){};
};

class Surf : public Lesson {
    public:
        Surf(Time startTime,Time endTime,string name) : Lesson(startTime,endTime,name){};
};

class Windsurf : public Lesson {
    unsigned int CalcCost() const;
        Windsurf(Time startTime,Time endTime,string name) : Lesson(startTime,endTime,name){};
};

//Exceptions

class activityNonExistant : std::exception {
public:
    unsigned int id;
    activityNonExistant(unsigned int id){id = id;};
};

std::ostream & operator <<(std::ostream &out,const activityNonExistant &activity);

#endif //SUP_SCHOOL_ACTIVITY_H
