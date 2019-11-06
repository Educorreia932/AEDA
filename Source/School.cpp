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

vector<Staff *> School::getStaff() const{
    return this->staff;
}

void School::readClients() {
    string line;
    ifstream File("../Data/" + Files["Clients"]);
    int counter = 0;
    auto* auxClient = new Client();
    ostringstream planned_activities;

    if (File.is_open()) {
        while (getline(File, line)) {
                switch (counter % 5) {
                    case 0:
                        auxClient->setName(line);
                        break;
                    case 1:
                        auxClient->setID((stoi(line)));

                        if (stoi(line) > Client::getLastID())
                            Client::setLastID(stoi(line));

                        break;
                    case 2:
                        auxClient->setGoldMember(stob(line));
                        break;
                    case 3:
                        planned_activities << line;

                        break;
                    case 4:
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

    auto* auxActivity = new Activity();

    if (File.is_open()) {
        while (getline(File, line)) {
            switch (counter % 6) {
                case 0:
                    auxActivity->setID(stoi(line));
                    break;
                case 1:
                    break;
                case 2:
                    auxActivity->setName(line);
                    break;
                case 3:
                    auxActivity->setStartTime(line);
                    break;
                case 4:
                    auxActivity->setEndTime(line);
                    break;
                case 5:
                    Activities.push_back(auxActivity);
                    auxActivity = new Activity();
                    break;
            }

            counter++;
        }
    }
}

void School::enroll(const unsigned int clientId, const unsigned int activityId) {
    //Time needs to be checked if is ahead of the set current time

    Client* client;
    bool clientExists = false;

    for (const auto &c : this->Clients) {
        if(c->getId() == clientId){
            client = c;
            clientExists = true;
            break;
        }
    }

    if(!clientExists)
        throw NonExistantClient(clientId);

    bool activityExists = false;

    for (const auto &ac : Activities) {
        if (activityId == ac->getId()){
            try {
                client->addActivity(ac);
            }

            catch (clientAlreadHasActivity &e) {
                throw e;
            }
        }
    }

/*    if(!activityExists)
        throw activityNonExistant(activityId);*/
}

void School::viewActivities() {

}

ostream &operator<<(ostream &out, const School& S) {
    out << "Name: " << S.name << endl
        << "Current date: " << S.currentTime << endl
        << "Number of enrolled clients: " << S.Clients.size() << endl
        << "Number of planned activities: " << S.Activities.size() << endl;

    return out;
}

void School::viewClients(bool detailed) {
    if (detailed)
        for (auto & Client : Clients)
            cout << *Client << endl;

    else
        for (auto & Client : Clients)
            cout << Client->getName() << " - " << Client->getId() << endl;
}

//Exceptions

std::ostream &operator<<(std::ostream &out, const NonExistantClient &client) {
    out << "Client with ID " << client.id << " does not exist in school." << endl;
    return out;
}

std::ostream &operator<<(std::ostream &out, const ClientAlreadyExists &client) {
    out << "Client with ID " << client.id << " already exists in school." << endl;
    return out;
}

