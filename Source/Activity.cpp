
#include "../Headers/Activity.h"

using namespace std;

unsigned int Activity::id = 0;

Activity::Activity() {

}

Activity::Activity(Time startTime, Time endTime,string name) {
    this->startTime = startTime;
    this->endTime = endTime;
    this->id = Activity::id++;
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

int Activity::calcCost() const {
    return 0;
}

std::ostream &operator<<(std::ostream &out, const activityNonExistant &activity) {
    out << "Activity with ID \"" << activity.id << "\" does not exist." << endl;
    return out;
}
