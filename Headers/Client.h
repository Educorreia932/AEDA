#ifndef SUP_SCHOOL_CLIENT_H
#define SUP_SCHOOL_CLIENT_H

#include <fstream>
#include <string>
#include <vector>

#include "Activity.h"
#include "Auxiliary.h"

/** @defgroup group_client Client */

/** @ingroup group_client */

class Client {
    public:
        /*! @name Constructors */
        ///@{
        Client();
        Client(string name, bool has_gold_card, int balance);
        ///@}

        /*! @name Getters */
        ///@{
        string getName() const;
        static unsigned int getLastID();
        unsigned int getId() const;
        bool getGoldMember() const;
        vector<Activity*> getPastActivities() const;
        /** @returns The IDs of the past activities of the client separated by a space between them. */
        string getPastActivitiesID() const;
        vector<Activity*> getScheduledActivities() const;
        vector<Activity*> getScheduleActivitiesByDate(Time Date) const;
        /** @returns The scheduled activites of the client that occur on the time period stated in the function parameters. */
        vector<Activity*> getScheduleActivitiesByDate(Time BeginDate, Time EndDate) const;
        /** @returns The IDs of the scheduled activities of the client separated by a space between them. */
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
        /** @throws insufficientFunds if the user tries to make the balance negative.*/
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
        /** @returns True, if the client has as an activity in the time period stated in the function parameters. */
        bool isOcuppied(const Time startTime,const Time endTime);
};

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

#endif //SUP_SCHOOL_CLIENT_H
