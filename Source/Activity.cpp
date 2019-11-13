#include "../Headers/Activity.h"

#include <vector>
using namespace std;

unsigned int Activity::last_id = 0;

Activity::Activity() {
    this->id = Activity::last_id++;
}

Activity::Activity(Time startTime, Time endTime, string name) {
    this->name = name;
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

ostream &operator<<(ostream &out, const Activity &A) {
    cout << "Name: " << A.name << endl;
    cout << "ID: " << A.id << endl;
    cout << "Start Time: " << A.startTime << endl;
    cout << "End Time: " << A.endTime << endl;
    return out;
}
ostream &operator<<(ostream &out, const Ride &R){
    cout << "Name: " << R.name << endl;
    cout << "ID: " << R.id << endl;
    cout << "Start Time: " << R.startTime << endl;
    cout << "End Time: " << R.endTime << endl;
    cout << "Cost: " << R.cost << endl;
}
unsigned int Activity::getLastID() {
    return last_id;
}

Lesson::Lesson() {
    this->id = Activity::last_id++;
}

unsigned int Lesson::CalcCost() const {
    return 0;
}

Ride::Ride() {
    this->id = Activity::last_id++;
}

void Ride::SetCost(unsigned int cost){
    this->cost = cost;
}

unsigned int Ride::CalcCost() const {
    return cost;
}

void Ride::setCost(unsigned int i) {

}


std::ostream &operator<<(std::ostream &out, const activityNonExistent &activity) {
    out << "Activity with ID \"" << activity.id << "\" does not exist." << endl;
    return out;
}


vector<Activity*> eraseAndReturnVector(vector<Activity*> vec,unsigned int i){
    vec.erase(vec.begin() + i);
    return vec;
}

