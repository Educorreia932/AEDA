#ifndef SUP_SCHOOL_SCHOOL_H
#define SUP_SCHOOL_SCHOOL_H

#include "Activity.h"
#include "Client.h"
#include "Material.h"
#include "Staff.h"
#include "Time.h"

#include <fstream>
#include <vector>

class School {
    public:
        //Constructors
        School();
        School(vector<Client> Clients, vector<Material> Materials);

        void addClient(Client client);
        int clientIndex(unsigned int id);
        void removeClient(unsigned int id);
        void readClients(string filename);
    private:
        vector<Client> Clients;
        vector<Material> Materials;
};

class NonExistantClient : std::exception {
    public:
        unsigned int id;
        NonExistantClient(unsigned int id){this->id = id;};
};

std::ostream & operator <<(std::ostream &out,const NonExistantClient &client);

class ClientAlreadyExists : std::exception{
    public:
        unsigned int id;
        ClientAlreadyExists(unsigned int id){this->id = id;};
};

std::ostream & operator <<(std::ostream &out,const ClientAlreadyExists &client);
#endif //SUP_SCHOOL_SCHOOL_H
