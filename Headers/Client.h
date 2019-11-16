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
        /**
         * @param name Name of the client.
         * @param has_gold_card Wheter the client is a gold member or not.
         * @param balance Initial balance of the client.
         */
        Client(string name, bool has_gold_card, int balance);
        ///@}

        /** @name Getters */
        ///@{
        /** @returns The name of the client. */
        string getName() const;
        /** @returns The ID of the most recent client to enter the school. */
        static unsigned int getLastID();
        /** @returns The ID of the client. */
        unsigned int getId() const;
        /** @returns Wheter the client is a gold member or not. */
        bool getGoldMember() const;
        /** @returns The past activities of the client. */
        vector<Activity*> getPastActivities() const;
        /** @returns The IDs of the past activities of the client separated by a space between them. */
        string getPastActivitiesID() const;
        /** @returns The scheduled activities of the client. */
        vector<Activity*> getScheduledActivities() const;
        vector<Activity*> getScheduleActivitiesByDate(Time Date) const;
        /** @returns The scheduled activites of the client that occur on the time period stated in the function parameters. */
        vector<Activity*> getScheduleActivitiesByDate(Time BeginDate, Time EndDate) const;
        /** @returns The IDs of the scheduled activities of the client separated by a space between them. */
        string getScheduledActivitiesID() const;
        /** @returns The balance of the client. */
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
        /** Activities in which the client has participated in the past */
        vector<Activity*> PastActivities;
        /** Activities in which the client is yet to participate */
        vector<Activity*> ScheduledActivities;
        static unsigned int last_id;
        /** Identification number of the client. Starts in 1 and is incremented by one each time a new client is added to the school. */
        unsigned int id;
        double balance;
        /** The name of the client */
        string name;
        bool gold_member;
        /** @returns Wheter the client has as an activity in the time period stated in the function parameters or not. */
        bool isOcuppied(const Time startTime,const Time endTime);
};

/** @ingroup group_exceptions */

class alreadyGoldMember : exception {
    public:
        unsigned int id;
        alreadyGoldMember(unsigned int id){this->id = id;};
};

ostream & operator <<(ostream &out, const alreadyGoldMember &member);

/** @brief Client already has an activity that collides with another that he tries to add. */
class hasActivityAtSameTime : exception {
    public:
        unsigned clientId;
        unsigned int activityId;
        hasActivityAtSameTime(unsigned int clientId,unsigned int activityId){this->clientId = clientId;this->activityId = activityId;};
};

ostream & operator <<(ostream &out, const hasActivityAtSameTime &ids);

/** @brief Client already has activity in its scheduled activities and tries to add it again */
class clientAlreadHasActivity : exception {
public:
    unsigned clientId;
    unsigned int activityId;
    clientAlreadHasActivity(unsigned int clientId,unsigned int activityId){this->clientId = clientId;this->activityId = activityId;};
};

ostream & operator <<(ostream &out,const clientAlreadHasActivity &ids);

/** @brief A client tries to spend more money that he currently has on his balance */
class insufficientFunds : exception {
    public:
        /** @brief ID of the client. */
        unsigned int clientId;
        /** @brief Current balance of the client. */
        int balance;
        /** @brief Excess amount resulting from the over-expense of the client. */
        int difference;
        insufficientFunds(unsigned clientId, int balance, int difference){this->clientId = clientId; this->balance = balance;this->difference = difference;};
};

ostream & operator <<(ostream &out,const insufficientFunds &info);

#endif //SUP_SCHOOL_CLIENT_H
