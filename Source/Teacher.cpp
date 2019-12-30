#include "../Headers/Teacher.h"

unsigned int Staff::last_id = 0;

void Staff::setID(const unsigned int id) {
    this->id = id;
}

void Staff::setLastID(unsigned int id) {
    last_id = id;
}

unsigned int Staff::getLastID() {
    return last_id;
}

unsigned Staff::getID() const {
    return id;
}

Technician::Technician(){
    this->id = last_id++;
    PastFixes = {};
    ScheduledFixes = {};
}

Teacher::Teacher(){
    this->id = last_id++;
    PastActivities = {};
    ScheduledActivities = {};
    this->currentlyEmployed = true;
}

Teacher::Teacher(string name){
    this->id = last_id++;
    this->name = name;
    ScheduledActivities = {};
    PastActivities = {};
    this->currentlyEmployed = true;
}

void Teacher::setName(string name) {
    this->name = name;
}

ostream &operator<<(ostream &out, const Teacher &T) {
    out << "ID: " << T.id << endl;
    out << "Name: " << T.name << endl;

    if (T.ScheduledActivities.empty())
        out << "No activities associated";

    else {
        out << "Scheduled activities: ";

        for (auto a : T.ScheduledActivities)
            out << a->getId() << " ";
    }
    out << endl;

    return out;
}

bool Teacher::isOcuppied(const Time startTime, const Time endTime) {
    for (const auto &ac : this->ScheduledActivities) {
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

void Teacher::addActivity(Activity* activity, bool past) {
    if (past)
        PastActivities.push_back(activity);

    else {
        for (const auto &ac : ScheduledActivities)
            if (ac->getId() == activity->getId())
                throw teacherAlreadHasActivity(id,activity->getId()); //Not catching

        if(isOcuppied(activity->getStartTime(), activity->getEndTime()))
            throw teacherHasActivityAtSameTime(this->id,activity->getId());

        ScheduledActivities.push_back(activity);
    }
}

bool Teacher::getCurrentlyEmployed() const {
    return currentlyEmployed;
}

string Teacher::getName() const {
    return name;
}

string Teacher::getScheduledActivitiesID() const {
    stringstream result;

    for (auto a : ScheduledActivities)
        result << a->getId() << " ";

    return result.str();
}

string Teacher::getPastActivitiesID() const {
    stringstream result;

    for (auto a : PastActivities)
        result << a->getId() << " ";

    return result.str();
}

vector<Activity *> Teacher::getScheduledActivities() const {
    return ScheduledActivities;
}

vector<Activity *> Teacher::getScheduleActivitiesByDate(Time Date) const {
    vector<Activity *> result;

    for (auto a : ScheduledActivities)
        if (a->getStartTime().sameDate(Date))
            result.push_back(a);

    return result;
}

void Teacher::setCurrentlyEmployed(bool currentlyEmployed) {
    this->currentlyEmployed = currentlyEmployed;
}

ostream &operator<<(ostream &out, const teacherHasActivityAtSameTime &ids) {
    out << "Teacher with ID \"" << ids.teacherId << "\" already has an activity at the same time as activity with ID \"" << ids.activityId << "\"." << endl;
    return out;
}

ostream &operator<<(ostream &out, const teacherAlreadHasActivity &ids) {
    out << "Teacher with ID \"" << ids.teacherId << "\" already is already enrolled in activity with ID \"" << ids.activityId << "\"." << endl;
    return out;
}
