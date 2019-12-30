#ifndef SUP_SCHOOL_TEACHER_H
#define SUP_SCHOOL_TEACHER_H

#include "Activity.h"

#include <vector>
#include <unordered_set>



/** @defgroup group_teacher Teacher */

/** @ingroup group_teacher */

class Teacher {
public:
    Teacher();
    Teacher(string name);

    void setID(const unsigned int id);
    unsigned getID()const ;
    bool getCurrentlyEmployed() const;
    void setCurrentlyEmployed(bool currentlyEmployed);
    static unsigned int getLastID( );
    static void setLastID(const unsigned int id);
    void setName(string name);
    string getName() const;
    void addActivity(Activity* activity, bool past);
    bool isOcuppied(const Time startTime, const Time endTime);
    string getPastActivitiesID() const;
    string getScheduledActivitiesID() const;
    vector<Activity*> getScheduledActivities() const;
    vector<Activity*> getScheduleActivitiesByDate(Time Date) const;

    friend ostream& operator<<(ostream& out, const Teacher& C);
private:
    string name;
    unsigned int id;
    static unsigned int last_id;
    vector<Activity *> PastActivities;
    vector<Activity *> ScheduledActivities;
    bool currentlyEmployed;
};

/*! \cond */

struct teacherHash
{
    int operator() (const Teacher * t) const
    {
        return t->getID();
    }

    bool operator() (const Teacher * t1, const Teacher * t2) const
    {
        return t1->getID() == t2->getID();
    }
};

typedef unordered_set<Teacher*, teacherHash, teacherHash> TeacherHashTable;


class teacherHasActivityAtSameTime : std::exception {
public:
    unsigned teacherId;
    unsigned int activityId;
    teacherHasActivityAtSameTime(unsigned int teacherId,unsigned int activityId){this->teacherId = teacherId;this->activityId = activityId;};
};

ostream & operator <<(ostream &out,const teacherHasActivityAtSameTime &ids);

class teacherAlreadHasActivity : std::exception {
public:
    unsigned teacherId;
    unsigned int activityId;
    teacherAlreadHasActivity(unsigned int teacherId,unsigned int activityId){this->teacherId = teacherId;this->activityId = activityId;};
};

ostream & operator <<(std::ostream &out,const teacherAlreadHasActivity &ids);

/*! \endcond */

#endif //SUP_SCHOOL_TEACHER_H