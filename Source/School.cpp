#include "../Headers/School.h"

School::School() {

}

School::School(vector<Client> Clients, vector<Material> Materials) {
    this->Clients = Clients;
    this->Materials = Materials;
}

void School::removeClient(unsigned int id) {

    bool exists = false;

    for(size_t i = 0; i < Clients.size() ; i++){
        if(Clients.at(i).getId() == id){
            Clients.erase(Clients.begin()+i);
            exists = true;
            break;
        }
    }

    if(!exists){
        throw NonExistantClient(id);
    }
}

std::ostream &operator<<(std::ostream &out, const NonExistantClient &client) {
    out << "Client with ID " << client.id << " does not exist in school." << endl;
    return out;
}
