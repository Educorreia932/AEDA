#include "../Headers/Teacher.h"

unsigned int Teacher::last_id = 0;

Teacher::Teacher(){
    this->id = last_id++;
    Activities = {};
}

Teacher::Teacher(string name){
    this->id = last_id++;
    this->name = name;
    Activities = {};
}

void Teacher::setID(const unsigned int id) {
    this->id = id;
}

void Teacher::setName(string name) {
    this->name = name;
}


ostream &operator<<(ostream &out, const Teacher &T) {

    out << "ID: " << T.id << endl;
    out << "Name: " << T.name << endl;

    if(T.Activities.size() == 0)
        out << "No activities associated" << endl;
    else {
        out << "Associated activities: ";

        for (auto a : T.Activities){
            out << a->getId() << " ";
        }
    }
    out << endl;

    return out;
}

unsigned int Teacher::getLastID() {
    return last_id;
}

void Teacher::setLastID(unsigned int id) {
    last_id = id;
}

bool Teacher::isOcuppied(const Time startTime, const Time endTime) {
    for (const auto &ac : this->Activities) {
        if(ac->getStartTime() == startTime)
            return true;

        if(ac->getEndTime() == endTime)
            return true;

        if(ac->getStartTime() < startTime && startTime < ac->getEndTime())
            return true;

        if(endTime > ac->getStartTime() && endTime < ac->getEndTime())
            return true;
    }

    return false;
}


void Teacher::addActivity(Activity* activity) {

    for (const auto &ac : Activities)
        if (ac->getId() == activity->getId())
            throw teacherAlreadHasActivity(this->id,activity->getId()); //Not catching

    if(isOcuppied(activity->getStartTime(), activity->getEndTime()))
        throw teacherHasActivityAtSameTime(this->id,activity->getId());

    Activities.push_back(activity);
}

unsigned Teacher::getID() const {
    return id;
}

string Teacher::getName() const {
    return name;
}

string Teacher::getActivitiesID() const {
    stringstream result;

    for (auto a : Activities)
        result << a->getId() << " ";

    return result.str();
}

vector<Activity *> Teacher::getScheduledActivities() const {
    return Activities;
}

vector<Activity *> Teacher::getScheduleActivitiesByDate(Time Date) const {
    vector<Activity *> result;

    for (auto a : Activities)
        if (a->getStartTime().sameDate(Date))
            result.push_back(a);

    return result;
}


ostream &operator<<(ostream &out, const teacherHasActivityAtSameTime &ids) {
    out << "Teacher with ID \"" << ids.teacherId << "\" already has an activity at the same time as activity with ID \"" << ids.activityId << "\"." << endl;
    return out;
}

ostream &operator<<(std::ostream &out, const teacherAlreadHasActivity &ids) {
    out << "Teacher with ID \"" << ids.teacherId << "\" already is already assigned to an activity with ID \"" << ids.activityId << "\"." << endl;
    return out;
}

