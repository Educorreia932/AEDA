#ifndef SUP_SCHOOL_TEACHER_H
#define SUP_SCHOOL_TEACHER_H

#include "Activity.h"

#include <vector>
#include <unordered_set>

/** @defgroup group_teacher Teacher */

/** @ingroup group_teacher */

class Staff {
    public:
        void setID(const unsigned int id);
        unsigned getID()const ;
        static unsigned int getLastID( );
        static void setLastID(const unsigned int id);
    protected:
        string name;
        unsigned int id;
        static unsigned int last_id;

        vector<Activity *> PastActivities;
        vector<Activity *> ScheduledActivities;
        bool currentlyEmployed;
};

class Technician : public Staff {
    public:
        Technician();
        Technician(string name);
        void setName(string name);

        string getName() const;
        vector<Fixing *> PastFixes;
        vector<Fixing *> ScheduledFixes;

        friend bool operator <(Technician t1, Technician t2);
};

class Teacher: public Staff {
    public:
        Teacher();
        Teacher(string name);

        void setName(string name);
        string getName() const;
        void addActivity(Activity* activity, bool past);
        bool isOcuppied(const Time startTime, const Time endTime);
        string getPastActivitiesID() const;
        string getScheduledActivitiesID() const;
        vector<Activity*> getScheduledActivities() const;
        vector<Activity*> getScheduleActivitiesByDate(Time Date) const;

        friend ostream& operator<<(ostream& out, const Teacher& C);

        void setCurrentlyEmployed(bool currentlyEmployed);

    private:
            string name;
            vector<Activity *> PastActivities;
            vector<Activity *> ScheduledActivities;
            bool currentlyEmployed;
            bool getCurrentlyEmployed() const;
};

/*! \cond */

struct teacherHash
{
    int operator() (const Teacher * t) const {
        return t->getID();
    }

    bool operator() (const Teacher * t1, const Teacher * t2) const {
        return t1->getID() == t2->getID();
    }
};

typedef unordered_set<Teacher*, teacherHash, teacherHash> TeacherHashTable;


class teacherHasActivityAtSameTime : exception {
public:
    unsigned teacherId;
    unsigned int activityId;
    teacherHasActivityAtSameTime(unsigned int teacherId,unsigned int activityId){this->teacherId = teacherId;this->activityId = activityId;};
};

ostream & operator <<(ostream &out,const teacherHasActivityAtSameTime &ids);

class teacherAlreadHasActivity : exception {
public:
    unsigned teacherId;
    unsigned int activityId;
    teacherAlreadHasActivity(unsigned int teacherId,unsigned int activityId){this->teacherId = teacherId;this->activityId = activityId;};
};

ostream & operator <<(ostream &out,const teacherAlreadHasActivity &ids);

/*! \endcond */

#endif //SUP_SCHOOL_TEACHER_H