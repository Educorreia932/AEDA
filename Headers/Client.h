#ifndef SUP_SCHOOL_CLIENT_H
#define SUP_SCHOOL_CLIENT_H

#include <fstream>
#include <string>
#include <vector>

#include "Activity.h"
#include "Auxiliary.h"

/*! @brief Client of the SUP School */

class Client {
    public:
        /*! @name Getters */
        ///@{
        Client();
        Client(string name, bool has_gold_card,int balance);
        ///@}

        /*! @name Getters */
        ///@{
        string getName() const;
        static unsigned int getLastID();
        unsigned int getId() const;
        bool getGoldMember() const;
        vector<Activity*> getPastActivities() const;
        string getPastActivitiesID() const;
        vector<Activity*> getScheduledActivities() const;
        vector<Activity*> getScheduleActivitiesByDate(Time Date) const;
        vector<Activity*> getScheduleActivitiesByDate(Time BeginDate, Time EndDate) const;
        string getScheduledActivitiesID() const;
        double getBalance() const;
        ///@}

        /*! @name Setters */
        ///@{
        void setName(const string newName);
        static void setLastID(const unsigned int id);
        void setID(const unsigned int id);
        void setGoldMember(const bool gold_member);
        void setScheduledActivities(const vector<Activity *>& Activities);
        void setPastActivities(const vector<Activity *>& Activities);
        ///@}

        //Misc.
        void addActivity(Activity* activity, bool past);
        //Amount can be negative(will throw exception if tries to make it negative)
        void addBalance(double amount);
        void purchaseGold();
        bool isGoldMember() const;

        friend ostream& operator<<(ostream& out, const Client& C);
    private:
        vector<Activity*> PastActivities;
        vector<Activity*> ScheduledActivities;
        static unsigned int last_id;
        unsigned int id;
        double balance;
        string name;
        bool gold_member;
        bool isOcuppied(const Time startTime,const Time endTime);
};

/*! \cond */

class alreadyGoldMember : std::exception {
    public:
        unsigned int id;
        alreadyGoldMember(unsigned int id){this->id = id;};
};

std::ostream & operator <<(std::ostream &out,const alreadyGoldMember &member);

class hasActivityAtSameTime : std::exception {
    public:
        unsigned clientId;
        unsigned int activityId;
        hasActivityAtSameTime(unsigned int clientId,unsigned int activityId){this->clientId = clientId;this->activityId = activityId;};
};

std::ostream & operator <<(std::ostream &out,const hasActivityAtSameTime &ids);

class clientAlreadHasActivity : std::exception {
public:
    unsigned clientId;
    unsigned int activityId;
    clientAlreadHasActivity(unsigned int clientId,unsigned int activityId){this->clientId = clientId;this->activityId = activityId;};
};

std::ostream & operator <<(std::ostream &out,const clientAlreadHasActivity &ids);

class insufficientFunds : std::exception {
public:
    unsigned int clientId;
    int balance;
    int difference;
    insufficientFunds(unsigned clientId, int balance, int difference){this->clientId = clientId; this->balance = balance;this->difference = difference;};
};

std::ostream & operator <<(std::ostream &out,const insufficientFunds &info);

/*! \endcond */

#endif //SUP_SCHOOL_CLIENT_H
