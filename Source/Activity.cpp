#include "../Headers/Activity.h"

#include <vector>

using namespace std;

unsigned int Activity::last_id = 0;
unsigned int Fixing::last_fixid = 0;
Activity::Activity() {
    this->id = Activity::last_id++;
}

Activity::Activity(Time startTime, Time endTime, string name) {
    this->name = name;
    this->startTime = startTime;
    this->endTime = endTime;
    this->id = ++Activity::last_id;
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

void Activity::setStartTime(Time time) {
    this->startTime = time;
}

void Activity::setEndTime(Time time) {
    this->endTime = time;
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

unsigned int Activity::getLastID() {
    return last_id;
}
ostream& operator<<(ostream& out, const Activity& A){
    A.print(out);
    return out;
}
Lesson::Lesson(){
    this->id = Activity::last_id;
}

Lesson::Lesson(unsigned int id){
    this->id = id;
    if(id > Activity::last_id){
        Activity::last_id = id;
    }
}

string Lesson::getType() const {
    return "L";
}

unsigned int Lesson::CalcCost() const {
    return 0;
}

void Lesson::print(ostream& out) const{
    cout << "Name: " << name << endl;
    cout << "ID: " << id << endl;
    cout << "Start Time: " << startTime << endl;
    cout << "End Time: " << endTime << endl;
}

ostream &operator<<(ostream &out, const Ride &R){
    R.print(out);
    return out;
}

Ride::Ride(){
    this->id = Activity::last_id;
}

Ride::Ride(unsigned int id){
    this->id = id;
    if(id > Activity::last_id){
        Activity::last_id = id;
    }
}

string Ride::getType() const{
    return "R";
}

unsigned int Ride::CalcCost() const {
    return cost;
}

void Ride::setCost(unsigned int i) {
    this->cost = i;
}

bool Ride::operator>(Ride r){
    return this->id > r.id;
}



ostream &operator<<(ostream &out, const Lesson &L){
    L.print(out);
    return out;
}

void Ride::print(ostream& out) const{
    cout << "Name: " << name << endl;
    cout << "ID: " << id << endl;
    cout << "Start Time: " << startTime << endl;
    cout << "End Time: " << endTime << endl;
    cout << "Cost: " << cost << endl;
}

Fixing::Fixing(){
    this->fixid = Fixing::last_fixid;
}

Fixing::Fixing(unsigned int fixid){
    this->fixid = id;
    if(fixid > Fixing::last_fixid){
        Fixing::last_fixid = fixid;
    }
}

Fixing::Fixing(Time startTime, Time endTime, string name){
    this->name = name;
    this->startTime = startTime;
    this->endTime = endTime;
    this->fixid = ++Fixing::last_fixid;
}

unsigned int Fixing::CalcCost() const{
    return 0;
}

string Fixing::getType() const {
    return "F";
}

void Fixing::print(ostream& out) const{
    cout << "Name: " << name << endl;
    cout << "ID: " << id << endl;
    cout << "Start Time: " << startTime << endl;
    cout << "End Time: " << endTime << endl;
}

std::ostream &operator<<(std::ostream &out, const activityNonExistent &activity) {
    out << "Activity with ID \"" << activity.id << "\" does not exist." << endl;
    return out;
}

ostream &operator<<(ostream &out, const Fixing &F){
    F.print(out);
    return out;
}

vector<Activity*> eraseAndReturnVectorActivity(vector<Activity*> vec,unsigned int i){
    vec.erase(vec.begin() + i);
    return vec;
}

