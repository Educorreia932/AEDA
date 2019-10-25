#include "../Headers/Client.h"
#include "Main.cpp"

using namespace std;

unsigned int Client::id = 0;

Client::Client(string name, bool gold_member) {
    this->id = Client::id++;
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

unsigned int Client::getId() const {
    return this->id;
}

void Client::setName(const string newName) {
    this->name = newName;
}

Client::Client(const string &filename, int line_number) {
    string line;
    ifstream File(filename);
    int counter = 0;

    if (File.is_open()) {
        while (getline(File, line)) {
            if (counter >= line_number && line_number + 3 > counter) {
                switch (counter % 3) {
                    case 0:
                        name = line;
                        break;
                    case 1:
                        id = stoi(line);
                        break;
                    case 2:
                        gold_member = stob(line);
                        break;
                }
            }


            counter++;
        }

        File.close();
    }

}

void Client::enroll(const unsigned int activityId) {

    //Time needs to be checked if is ahead of the set current time


    bool activityExists = false;

    for (const auto &ac : PortoSUPSchool.getActivities()){

        if(activityId == ac->getId()){
            if(isOcuppied(ac->getStartTime(),ac->getEndTime())){
                throw hasActivityAtSameTime(this->id,activityId);
            } else {
                ScheduledActivities.push_back(ac);
                activityExists = true;
            }
        }
    }

    if(!activityExists){
        throw activityNonExistant(activityId);
    }


}

bool Client::isOcuppied(Time startTime, Time endTime) {

    for (const auto &ac : PortoSUPSchool.getActivities()){

        if(ac->getStartTime() == startTime){
            return true;
        }
        if(ac->getEndTime() == endTime){
            return true;
        }
        if(ac->getStartTime() > startTime && ac->getStartTime() < endTime){
            return true;
        }
        if(ac->getEndTime() > startTime && ac->getEndTime() < endTime){
            return true;
        }
    }

    return false;


}

ostream &operator<<(ostream &out, const alreadyGoldMember &member) {
    out << "Client with ID \"" << member.id << "\" already has a gold card." << endl;
    return out;
}

ostream &operator<<(ostream &out, const hasActivityAtSameTime &ids) {
    out << "Client with ID \"" << ids.clientId << "\" already has an activity at the same time as activity with ID \"" << ids.activityId << "\"." << endl;
    return out;
}
