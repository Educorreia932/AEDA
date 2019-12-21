#ifndef SUP_SCHOOL_TEACHER_H
#define SUP_SCHOOL_TEACHER_H

#include "Activity.h"

#include <vector>

/** @defgroup group_teacher Teacher */

/** @ingroup group_teacher */

class Staff {
protected:
    string name;
    unsigned int id;
    static unsigned int last_id;
    vector<Activity *> PastActivities;
    vector<Activity *> ScheduledActivities;
};

class Technician : Staff{
public:
    Technician();
    Technician(string name);



};
class Teacher: Staff {
public:
    Teacher();
    Teacher(string name);

    void setID(const unsigned int id);
    unsigned getID()const ;
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
    //string name;
    //unsigned int id;
    //static unsigned int last_id;
    //vector<Activity *> PastActivities;
    //vector<Activity *> ScheduledActivities;
};

/*! \cond */

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