#include "../Headers/Client.h"

using namespace std;

unsigned int Client::last_id = 0;

Client::Client() {

}

Client::Client(string name, bool gold_member) {
    this->id = Client::last_id+1;
    last_id++;
    this->name = name;
    this->gold_member = gold_member;
}

bool Client::isGoldMember() const {
    return this->gold_member;
}

void Client::purchaseGold() {

    if(this->gold_member){
        throw alreadyGoldMember (this->id);
    } else {
        gold_member = true;
    }

}

string Client::getName() const {
    return this->name;
}

unsigned int Client::getLastID() {
    return last_id;
}

unsigned int Client::getId() const {
    return this->id;
}

void Client::setGoldMember(const bool gold_member) {
    this->gold_member = gold_member;
}

void Client::setName(const string newName) {
    this->name = newName;
}

void Client::setID(const unsigned int id) {
    this->id = id;
}

bool Client::isOcuppied(const Time startTime,const Time endTime) {
    for (const auto &ac : this->ScheduledActivities) {
        if(ac->getStartTime() == startTime)
            return true;

        if(ac->getEndTime() == endTime)
            return true;

        if(ac->getStartTime() > startTime && ac->getStartTime() < endTime)
            return true;

        if(ac->getEndTime() > startTime && ac->getEndTime() < endTime)
            return true;
    }

    return false;
}

ostream &operator<<(ostream &out, const Client &C) {
    if (C.gold_member)
        out << "$ Gold Member $" << endl;

    out << "Name: " << C.name << endl
        << "ID: " << C.id << endl;

    return out;
}

void Client::setActivities(const vector<Activity *> Activities) {
    ScheduledActivities = Activities;
}

vector<Activity *> Client::getScheduledActivities() const {
    return this->ScheduledActivities;
}

void Client::addActivity(Activity* activity) {
    for (const auto &ac : ScheduledActivities)
        if (ac->getId() == activity->getId())
            throw clientAlreadHasActivity(id,activity->getId()); //Not catching

    if(isOcuppied(activity->getStartTime(), activity->getEndTime()))
        throw hasActivityAtSameTime(this->id,activity->getId());

    ScheduledActivities.push_back(activity);
}

void Client::setLastID(const unsigned int id) {
    last_id = id;
}

ostream &operator<<(ostream &out, const alreadyGoldMember &member) {
    out << "Client with ID \"" << member.id << "\" already has a gold card." << endl;
    return out;
}

ostream &operator<<(ostream &out, const hasActivityAtSameTime &ids) {
    out << "Client with ID \"" << ids.clientId << "\" already has an activity at the same time as activity with ID \"" << ids.activityId << "\"." << endl;
    return out;
}

ostream &operator<<(std::ostream &out, const clientAlreadHasActivity &ids) {
    out << "Client with ID \"" << ids.clientId << "\" already is already enrolled in activity with ID \"" << ids.activityId << "\"." << endl;
    return out;
}
