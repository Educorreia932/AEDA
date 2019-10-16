#ifndef SUP_SCHOOL_CLIENT_H
#define SUP_SCHOOL_CLIENT_H

#include <string>
#include <iostream>
#include <vector>

#include "Activity.h"

using namespace std;

class Client {
    private:
        //vector<*Activity> activities;
        static unsigned int id;
        string name;
        bool gold_member;

    public:
        Client(unsigned int id, string name, bool has_gold_card);


        void purchaseGold();

        string getName() const;
        unsigned int getId() const;
        bool isGoldMember() const;

        void setName(string newName);


};


class alreadyGoldMember : std::exception {
public:
    unsigned int id;
    alreadyGoldMember(unsigned int id){id = id;};
};

std::ostream & operator <<(std::ostream &out,const alreadyGoldMember &member);


#endif //SUP_SCHOOL_CLIENT_H
