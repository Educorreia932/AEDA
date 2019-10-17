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

void School::addClient(Client client) {

    if(clientIndex(client.getId()) != -1){
        throw ClientAlreadyExists(client.getId());
    }
    Clients.push_back(client);
}

int School::clientIndex(unsigned int id) {

    for (size_t i = 0; i < Clients.size();i++){
        if(Clients.at(i).getId() == id){
            return i;
        }
    }
    return -1;
}

std::ostream &operator<<(std::ostream &out, const NonExistantClient &client) {
    out << "Client with ID " << client.id << " does not exist in school." << endl;
    return out;
}

std::ostream &operator<<(std::ostream &out, const ClientAlreadyExists &client) {
    out << "Client with ID " << client.id << " already exists in school." << endl;
    return out;
}

void School::readClients(string filename) {
    string line;
    ifstream ClientsFile(filename);
    int counter = 0;

    if (ClientsFile.is_open()) {
        while (getline(ClientsFile, line)) {
            if (line == "----------") //Or end of file
                ;
        }
    }

}

