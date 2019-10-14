#ifndef SUP_SCHOOL_CLIENT_H
#define SUP_SCHOOL_CLIENT_H

#include <string>

using namespace std;

class Client {
    private:
        unsigned int id;
        string name;
    public:
        Client(unsigned int id, string name);
};

Client::Client(unsigned int id, string name) {
    this->id = id;
    this->name = name;
}

#endif //SUP_SCHOOL_CLIENT_H
