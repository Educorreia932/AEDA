#ifndef SUP_SCHOOL_SCHOOL_H
#define SUP_SCHOOL_SCHOOL_H

#include "Activity.h"
#include "Client.h"
#include "Material.h"
#include "Staff.h"
#include "Time.h"

#include <vector>

class School {
    public:
        School();
        School(vector<Client> Clients, vector<Material> Materials);

        void removeClient(unsigned int id);
    private:
        vector<Client> Clients;
        vector<Material> Materials;
};


class NonExistantClient : std::exception{
public:
    unsigned int id;
    NonExistantClient(unsigned int id){this->id = id;};
};

std::ostream & operator <<(std::ostream &out,const NonExistantClient &client);

#endif //SUP_SCHOOL_SCHOOL_H
