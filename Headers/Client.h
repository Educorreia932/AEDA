#ifndef SUP_SCHOOL_CLIENT_H
#define SUP_SCHOOL_CLIENT_H

#include <string>

using namespace std;

class Client {
    private:
        unsigned int id;
        string name;
        bool has_gold_card;
    public:
        Client(unsigned int id, string name, bool has_gold_card);
};



#endif //SUP_SCHOOL_CLIENT_H
