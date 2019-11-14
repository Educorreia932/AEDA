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
        /*! @name Constructors */
        ///@{
        Activity();
        Activity(Time startTime,Time endTime,string name);
        ///@}

        /*! @name Getters */
        ///@{
        Time getStartTime();
        Time getEndTime();
        string getName() const;
        unsigned int getId() const;
        static unsigned int getLastID();
        /*! @returns The type of activity, either Ride (R) or Lesson (L). */
        virtual char getType() const;
        ///@}

        /*! @name Setters */
        ///@{
        void setName(string name);
        void setID(unsigned int id);
        void setStartTime(string time);
        void setEndTime(string time);
        ///@}

        virtual unsigned int CalcCost() const;

        friend ostream& operator<<(ostream& out, const Activity& A);
};

class Ride : public Activity {
    protected:
        unsigned int cost;
    public:
        Ride();
        Ride(Time startTime,Time endTime,string name) : Activity(startTime,endTime,name){};
        unsigned int CalcCost() const;
        virtual char getType() const;
};

class Lesson : public Activity {
    public:
        Lesson();
        Lesson(Time startTime,Time endTime,string name) : Activity(startTime,endTime,name){};
        unsigned int CalcCost() const;
        virtual char getType() const;
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

vector<Activity*> eraseAndReturnVector(vector<Activity*> vec, unsigned int i);

/*! @cond */

class activityNonExistent : exception {
public:
    unsigned int id;
    activityNonExistent(unsigned int id){id = id;};
};

ostream & operator <<(ostream &out, const activityNonExistent &activity);

/*! @endcond */

#endif //SUP_SCHOOL_ACTIVITY_H
