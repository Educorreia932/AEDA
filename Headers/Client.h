#ifndef SUP_SCHOOL_CLIENT_H
#define SUP_SCHOOL_CLIENT_H

#include <fstream>
#include <string>
#include <vector>

#include "Activity.h"
#include "Auxiliary.h"

class Client {
    public:
        //Constructors
        Client();
        Client(string name, bool has_gold_card);

        //Getters
        string getName() const;
        static unsigned int getLastID();
        unsigned int getId() const;
        vector<Activity*> getScheduledActivities() const;

        //Setters
        void setName(const string newName);
        void setID(const unsigned int id);
        void setGoldMember(const bool gold_member);
        //test -v
        void setActivities(const vector<Activity *> Activities);

        //Misc.
        void addActivity(Activity* activity);
        void purchaseGold();
        bool isGoldMember() const;
        void enroll(const unsigned int activityId,const vector<Activity*> schoolActivities);

        friend ostream& operator<<(ostream& out, const Client& C);
    private:
        vector<Activity*> PastActivities;
        vector<Activity*> ScheduledActivities;
        static unsigned int last_id;
        unsigned int id;
        string name;
        bool gold_member;
        bool isOcuppied(const Time startTime,const Time endTime);
};

//Exceptions

class alreadyGoldMember : std::exception {
    public:
        unsigned int id;
        alreadyGoldMember(unsigned int id){id = id;};
};

std::ostream & operator <<(std::ostream &out,const alreadyGoldMember &member);

class hasActivityAtSameTime : std::exception {
    public:
        unsigned clientId;
        unsigned int activityId;
        hasActivityAtSameTime(unsigned int clientId,unsigned int activityId){clientId = clientId;activityId = activityId;};
};

std::ostream & operator <<(std::ostream &out,const hasActivityAtSameTime &ids);

class clientAlreadHasActivity : std::exception {
public:
    unsigned clientId;
    unsigned int activityId;
    clientAlreadHasActivity(unsigned int clientId,unsigned int activityId){clientId = clientId;activityId = activityId;};
};

std::ostream & operator <<(std::ostream &out,const clientAlreadHasActivity &ids);

#endif //SUP_SCHOOL_CLIENT_H
