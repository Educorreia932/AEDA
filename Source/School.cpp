#include "../Headers/School.h"

School::School() {

}

School::School(const string& filename) {
    string line;
    ifstream File(filename);
    int counter = 0;

    if(File.is_open()) {
        while (getline(File, line)) {
            switch (counter) {
                case 0:
                    name = line;
                    break;
                case 1:
                    currentTime = Time(line);
                    break;
                case 2:
                    Files["Clients"] = line;
                    break;
                case 3:
                    Files["Materials"] = line;
                    break;
                default:
                    break;
            }

            counter++;
        }

        File.close();
    }

    else
        cerr << "ERROR: Couldn't read file";
}

School::School(vector<Client*> Clients, vector<Material*> Materials) {
    this->Clients = Clients;
    this->Materials = Materials;
}

void School::removeClient(unsigned int id) {
    bool exists = false;

    for(size_t i = 0; i < Clients.size() ; i++){
        if (Clients.at(i)->getId() == id){
            Clients.erase(Clients.begin()+i);
            exists = true;
            break;
        }
    }

    if (!exists){
        throw NonExistantClient(id);
    }
}

void School::addClient(Client* client) {
    if(clientIndex(client->getId()) != -1){
        throw ClientAlreadyExists(client->getId());
    }

    Clients.push_back(client);
}

int School::clientIndex(unsigned int id) {
    for (size_t i = 0; i < Clients.size();i++){
        if (Clients.at(i)->getId() == id){
            return i;
        }
    }

    return -1;
}

vector<Activity *> School::getActivities() const {
    return this->Activities;
}

std::ostream &operator<<(std::ostream &out, const NonExistantClient &client) {
    out << "Client with ID " << client.id << " does not exist in school." << endl;
    return out;
}

std::ostream &operator<<(std::ostream &out, const ClientAlreadyExists &client) {
    out << "Client with ID " << client.id << " already exists in school." << endl;
    return out;
}

