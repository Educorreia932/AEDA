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
                case 4:
                    Files["Activities"] = line;
                    break;
                default:
                    break;
            }

            counter++;
        }

        File.close();

        readActivities();
        readClients();
    }

    else
        cerr << "ERROR: Couldn't read file";
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

void School::readClients() {
    string line;
    ifstream File("../Data/" + Files["Clients"]);
    int counter = 0;
    Client* auxClient = new Client();

    if (File.is_open()) {
        while (getline(File, line)) {
                switch (counter % 4) {
                    case 0:
                        auxClient->setName(line);
                        break;
                    case 1:
                        auxClient->setID((stoi(line)));
                        break;
                    case 2:
                        auxClient->setGoldMember(stob(line));
                        break;
                    case 3:
                        Clients.push_back(auxClient);
                        auxClient = new Client();
                        break;
            }

            counter++;
        }

        File.close();
    }
}

void School::readActivities() {
    string line;
    ifstream File("../Data/" + Files["Activities"]);
    int counter = 0;

    Activity* auxActivity = new Activity();

    if (File.is_open()) {
        while (getline(File, line)) {
            switch (counter % 3) {
                case 0:
                    auxActivity->setID(stoi(line));
                    break;
                case 1:
                    auxActivity->setName(line);
                    break;
                case 2:
                    Activities.push_back(auxActivity);
                    auxActivity = new Activity();
                    break;
            }

            counter++;
        }
    }
}

void School::enroll(const unsigned int clientId,const unsigned int activityId,const vector<Activity*> schoolActivities) {

    //Time needs to be checked if is ahead of the set current time

    Client* client;
    bool clientExists = false;

    for(const auto &c : this->Clients){
        if(c->getId() == clientId){
            client = c;
            clientExists = true;
            break;
        }
    }

    if(!clientExists){
        throw NonExistantClient(clientId);
    }

    bool activityExists = false;

    for (const auto &ac : schoolActivities){

        if(activityId == ac->getId()){
            if(client->isOcuppied(ac->getStartTime(),ac->getEndTime())){
                throw hasActivityAtSameTime(clientId,activityId);
            } else {
                client->addActivity(ac);
                activityExists = true;
            }
        }
    }

    if(!activityExists){
        throw activityNonExistant(activityId);
    }


}

std::ostream &operator<<(std::ostream &out, const NonExistantClient &client) {
    out << "Client with ID " << client.id << " does not exist in school." << endl;
    return out;
}

std::ostream &operator<<(std::ostream &out, const ClientAlreadyExists &client) {
    out << "Client with ID " << client.id << " already exists in school." << endl;
    return out;
}

