#include "../Headers/Activity.h"

using namespace std;

unsigned int Activity::last_id = 0;

Activity::Activity() {

}

Activity::Activity(Time startTime, Time endTime, string name) {
    this->startTime = startTime;
    this->endTime = endTime;
    this->id = Activity::last_id++;
}

string Activity::getName() const {
    return name;
}

Time Activity::getStartTime() {
    return startTime;
}

Time Activity::getEndTime() {
    return endTime;
}

unsigned int Activity::getId() const {
    return this->id;
}

void Activity::setName(string name) {
    this->name = name;
}

void Activity::setID(unsigned int id) {
    this->id = id;
}

void Activity::setStartTime(string time) {
    startTime = Time(time);
}

void Activity::setEndTime(string time) {
    endTime = Time(time);
}

unsigned int Activity::CalcCost() const {
    return 0;
}

unsigned int Lesson::CalcCost() const {
    return 0;
}

unsigned int Ride::CalcCost() const {
    return cost;
}


std::ostream &operator<<(std::ostream &out, const activityNonExistant &activity) {
    out << "Activity with ID \"" << activity.id << "\" does not exist." << endl;
    return out;
}
