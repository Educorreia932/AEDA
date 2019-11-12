#include "../Headers/School.h"
#include "../Headers/Menu.h"

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
                case 5:
                    Files["Teachers"] = line;
                    break;
                default:
                    break;
            }

            counter++;
        }

        File.close();

        readActivities();
        readClients();
        readTeachers();
    }

    else
        cerr << "ERROR: Couldn't read file";
}

void School::removeClient(unsigned int id) {
    bool exists = false;

    for(size_t i = 0; i < Clients.size() ; i++)
        if (Clients.at(i)->getId() == id) {
            Clients.erase(Clients.begin()+i);
            exists = true;
            break;
        }

    if (!exists)
        throw NonExistantClient(id);
}

void School::addClient(Client* client) {
    if (clientIndex(client->getId()) != -1)
        throw ClientAlreadyExists(client->getId());

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

vector<Client *> School::getClients() const{
    return this->Clients;
}

vector<Activity *> School::getActivities() const {
    return this->Activities;
}

vector<Teacher *> School::getTeachers() const{
    return this->Teachers;
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

void School::readClients() {
    string line;
    ifstream File("../Data/" + Files["Clients"]);
    int counter = 0;
    auto* auxClient = new Client();
    auto* planned_activities = new stringstream;

    if (File.is_open()) {
        while (getline(File, line)) {
                switch (counter % 6) {
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
                        auxClient->addBalance(stod(line));
                        break;
                    case 4:
                        *planned_activities << line;
                        break;
                    case 5:
                        Clients.push_back(auxClient);

                        readClientsActivities(planned_activities, auxClient);

                        planned_activities->clear();
                        auxClient = new Client();
                        break;
            }

            counter++;
        }

        File.close();
    }
}

void School::readTeachers() {
    string line;
    ifstream File("../Data/" + Files["Teachers"]);
    int counter = 0;
    auto* auxTeacher = new Teacher();
    auto* planned_activities = new stringstream;

    if (File.is_open()) {
        while (getline(File, line)) {
            switch (counter % 4) {
                case 0:
                    auxTeacher->setName(line);
                    break;
                case 1:
                    auxTeacher->setID((stoi(line)));

                    if (stoi(line) > Teacher::getLastID())
                        Teacher::setLastID(stoi(line));

                    break;
                case 2:
                    *planned_activities << line;
                    break;
                case 3:
                    Teachers.push_back(auxTeacher);

                    readTeachersActivities(planned_activities, auxTeacher);

                    planned_activities->clear();
                    auxTeacher = new Teacher();
                    break;
            }

            counter++;
        }

        File.close();
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
                activityExists = true;
            }

            catch (clientAlreadHasActivity &e) {
                throw e;
            }
        }
    }

    if(!activityExists)
        throw activityNonExistant(activityId);
}

void School::assign(const unsigned int teacherId, const unsigned int activityId) {
    //Time needs to be checked if is ahead of the set current time

    Teacher* teacher;
    bool teacherExists = false;

    for (const auto &t : this->Teachers) {
        if(t->getID() == teacherId){
            teacher = t;
            teacherExists = true;
            break;
        }
    }

    if(!teacherExists)
        throw NonExistantTeacher(teacherId);

    bool activityExists = false;

    for (const auto &ac : Activities) {
        if (activityId == ac->getId()){
            try {
                teacher->addActivity(ac);
                activityExists = true;
            }

            catch (teacherAlreadHasActivity &e) {
                throw e;
            }
            catch(teacherHasActivityAtSameTime &e){
                throw e;
            }
        }
    }

    if(!activityExists)
        throw activityNonExistant(activityId);
}

void School::readClientsActivities(stringstream* planned_activities, Client* c) {
    int activity_id;

    while (*planned_activities >> activity_id) {
        try {
            enroll(c->getId(), activity_id);
        }

        catch (activityNonExistant &e) {
            cout << e;
            Menu::pause();
        }

        catch (hasActivityAtSameTime &e) {
            cout << e;
            Menu::pause();
        }

        catch (clientAlreadHasActivity &e) {
            cout << e;
            Menu::pause();
        }
    }

}

void School::readTeachersActivities(stringstream* planned_activities, Teacher* t) {
    int activity_id;

    while (*planned_activities >> activity_id) {
        try {
            assign(t->getID(), activity_id);
        }

        catch (activityNonExistant &e) {
            cout << e;
            Menu::pause();
        }

        catch (teacherHasActivityAtSameTime &e) {
            cout << e;
            Menu::pause();
        }

        catch (teacherAlreadHasActivity &e) {
            cout << e;
            Menu::pause();
        }
    }

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
            cout << *Client << endl
                 << "---------------------" << endl;

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

std::ostream &operator<<(std::ostream &out, const NonExistantTeacher &teacher) {
    out << "Teacher with ID " << teacher.id << " does not exist in school." << endl;
    return out;
}

std::ostream &operator<<(std::ostream &out, const TeacherAlreadyExists &teacher) {
    out << "Teacher with ID " << teacher.id << "already exists in school." << endl;
    return out;
}

void School::viewActivities(bool detailed){
    if(detailed) {
        cout << "All activities:\n";
        cout << "---------------------" << endl;

        for (const auto &Activity : Activities) {
            cout << *Activity;
            cout << "---------------------" << endl;
        }
    }
    else{
        for (auto & activity : Activities)
            cout << activity->getName() << " - " << activity->getId() << endl;

    }
}

void School::viewTeachers(bool detailed) {
    if (detailed)
        for (auto & teacher : Teachers)
            cout << *teacher
                 << "---------------------" << endl;

    else
        for (auto & teacher : Teachers)
            cout << teacher->getName() << " - " << teacher->getID() << endl;
}

void School::saveClients() {
    ofstream f;
    int counter = 0;

    f.open("../Data/" + Files["Clients"]);

    if (f.is_open())
        for (auto c : Clients) {
            f << c->getName() << endl
              << c->getId() << endl
              << btos(c->getGoldMember()) << endl
              << c->getBalance() << endl
              << c->getScheduledActivitiesID() << endl;

            if (counter == size(Clients) - 1)
                f << "---END---";


            else
                f << "::::::::::" << endl;

            counter++;
        }

    f.close();
}

vector<Time> School::getDatesFromActivicties(vector <Activity*> Activities) {
    vector<Time> Dates;
    Time auxDate;
    bool already_present = false;

    for (auto a : Activities) {
         auxDate = Time(a->getStartTime().getDay(), a->getStartTime().getMonth(), a->getStartTime().getYear());

         for (auto d : Dates) // See if it's already in the vector
             if (d == auxDate)
                already_present = true;

         if (!already_present)
             Dates.push_back(auxDate);

         already_present = false;
    }

    return Dates;
}

void School::viewDates(vector <Time> Dates) {
    int counter = 1;

    for (auto d : Dates) {
        cout << counter << ") " << d.toString() << endl;
        counter++;
    }
}

void School::saveTeachers() {
    ofstream f;
    int counter = 0;

    f.open("../Data/" + Files["Teachers"]);

    if (f.is_open())
        for (auto t : Teachers) {
            f << t->getName() << endl
              << t->getID() << endl
              << t->getActivitiesID() << endl;

            if (counter == size(Teachers) - 1)
                f << "---END---";


            else
                f << "::::::::::" << endl;

            counter++;
        }

    f.close();
}

void School::addTeacher(Teacher* teacher) {
    if (teacherIndex(teacher->getID()) != -1)
        throw TeacherAlreadyExists(teacher->getID());

    Teachers.push_back(teacher);
}

int School::teacherIndex(unsigned int id) {
    for (size_t i = 0; i < Teachers.size();i++){
        if (Teachers.at(i)->getID() == id){
            return i;
        }
    }

    return -1;
}

void School::addActivity(Activity* activity){
    Activities.push_back(activity);
}
void School::removeTeacher(unsigned id) {

    if (teacherIndex(id) == -1)
        throw NonExistantTeacher(id);

    Teachers.erase(Teachers.begin()+teacherIndex(id));


}


