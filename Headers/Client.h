#ifndef SUP_SCHOOL_CLIENT_H
#define SUP_SCHOOL_CLIENT_H

#include <string>
#include <iostream>

using namespace std;

class Client {
    private:

        static unsigned int id;
        string name;
        bool gold_member;

    public:
        Client(unsigned int id, string name, bool has_gold_card);

        bool isGoldMember() const;
        void purchaseGold();
};


class alreadyGoldMember : std::exception {
public:
    unsigned int id;
    alreadyGoldMember(unsigned int id){id = id;};
};

std::ostream & operator <<(std::ostream &out,const alreadyGoldMember &member);


#endif //SUP_SCHOOL_CLIENT_H
