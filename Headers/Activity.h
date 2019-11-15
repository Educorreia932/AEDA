#ifndef SUP_SCHOOL_ACTIVITY_H
#define SUP_SCHOOL_ACTIVITY_H

#include "Time.h"
#include <vector>
class Activity {
    protected:
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
        static unsigned int getLastID();
        virtual string getType() const = 0;
        //Setters
        void setName(string name);
        void setID(unsigned int id);
        void setStartTime(string time);
        void setEndTime(string time);

        virtual unsigned int CalcCost() const = 0;
        virtual void print(ostream& out) const = 0;

        void setStartTime(Time time);
        void setEndTime(Time time);
};
ostream& operator<<(ostream& out, const Activity& A);
class Ride : public Activity {
    protected:
        unsigned int cost;
    public:
        Ride(); //DO NOT USE WHEN READING
        Ride(unsigned int id); //For use when reading
        Ride(Time startTime,Time endTime,string name) : Activity(startTime,endTime,name){this->cost = cost;}
        void SetCost(unsigned int cost);
        unsigned int CalcCost() const;
        void setCost(unsigned int cost);
        string getType() const;
        bool operator>(Ride b);
        void print(ostream& out) const;

        //void setStartTime(Time time);
        //void setEndTime(Time time);
};
ostream& operator<<(ostream& out, const Ride& R);
class Lesson : public Activity {
    public:
    Lesson();
    Lesson(unsigned int id);
    Lesson(Time startTime, Time endTime, string name) : Activity(startTime, endTime, name){};
    unsigned int CalcCost() const;
    string getType() const;
    void print(ostream& out) const;

    //void setStartTime(Time time);
    //void setEndTime(Time time);

};
ostream& operator<<(ostream& out, const Lesson& L);
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

vector<Activity*> eraseAndReturnVector(vector<Activity*> vec,unsigned int i);

/*! \cond */

class activityNonExistent : std::exception {
public:
    unsigned int id;
    activityNonExistent(unsigned int id){id = id;};
};

std::ostream & operator <<(std::ostream &out,const activityNonExistent &activity);



/*! \endcond */

#endif //SUP_SCHOOL_ACTIVITY_H
