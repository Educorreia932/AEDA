#include "../Headers/School.h"
#include "../Headers/Menu.h"

//Price of gold card
double School::goldCardPrice = 40;

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
        readMaterials();
        readClients();
        readTeachers();
    }

    else
        cerr << "ERROR: Couldn't read file";
}

void School::removeClient(unsigned int id) {
    if(Clients[clientIndex(id)]->getId() == -1)
        throw NonExistentClient(id);

    for(auto &m: Materials) {
        auto it = m->Clients.find(Clients[clientIndex(id)]);
        m->Clients.erase(it);
    }

    for(size_t i = 0; i < Clients.size() ; i++)
        if (Clients.at(i)->getId() == id) {
            Clients.erase(Clients.begin()+i);
            break;
        }
}

void School::removeMaterial(unsigned int id) {
    if(Materials[materialIndex(id)]->getID() == -1)
        throw NonExistentMaterial(id);

    for(size_t i = 0; i < Materials.size() ; i++)
        if (Materials.at(i)->getID() == id) {
            Materials.erase(Materials.begin()+i);
            break;
        }
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

int School::materialIndex(unsigned int id) {
    for (size_t i = 0; i < Materials.size();i++){
        if (Materials.at(i)->getID() == id){
            return i;
        }
    }

    return -1;
}

vector<Client *> School::getClients() const{
    return this->Clients;
}

vector<Teacher *> School::getTeachers() const{
    return this->Teachers;
}

vector<Material *> School::getMaterials() const{
    return this->Materials;
}

void School::readActivities() {
    string line;
    ifstream File("../Data/" + Files["Activities"]);
    int counter = 0, activity_id;

    //Things for the new activity
    int id;
    string type;
    string acName;
    string startTime;
    string endTime;
    //int cost; //N é preciso pois é a linha atual


    if (File.is_open()) {
        while (getline(File, line)) {
            switch (counter % 7) {
                case 0:
                    id = stoul(line);
                    break;
                case 1:
                    type = line;
                    break;
                case 2:
                    acName = line;
                    break;
                case 3:
                    startTime = line;
                    break;
                case 4:
                    endTime = line;
                    break;
                case 5:
                    //Check if it's a lesson "L" or ride "R"
                    if(type == "L"){
                        Lesson* AuxLesson = new Lesson(id);
                        //AuxLesson->setID(id);
                        AuxLesson->setName(acName);
                        AuxLesson->setStartTime(startTime);
                        AuxLesson->setEndTime(endTime);

                        if (AuxLesson->getStartTime() < currentTime)
                            PastActivities.push_back(AuxLesson);
                        else
                            ScheduledActivities.push_back((AuxLesson));
                    }
                    else if(type == "R"){
                        Ride* AuxActivity = new Ride(id);
                        //AuxActivity->setID(id);
                        AuxActivity->setName(acName);
                        AuxActivity->setStartTime(startTime);
                        AuxActivity->setEndTime(endTime);
                        AuxActivity->setCost(stoul(line));
                        if (AuxActivity->getStartTime() < currentTime)
                            PastActivities.push_back(AuxActivity);

                        else
                            ScheduledActivities.push_back((AuxActivity));
                    }
                    else{
                        cerr << "Non activity and non file found whilst reading activities" << endl;
                    }
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
    auto* activities = new stringstream;

    if (File.is_open()) {
        while (getline(File, line)) {
                switch (counter % 6) {
                    case 0: // Name
                        auxClient->setName(line);
                        break;
                    case 1: // ID
                        auxClient->setID((stoi(line)));

                        if (stoi(line) > Client::getLastID())
                            Client::setLastID(stoi(line));

                        break;
                    case 2: // Gold membership
                        auxClient->setGoldMember(stob(line));
                        break;
                    case 3: // Balance
                        auxClient->addBalance(stod(line));
                        break;
                    case 4: // Activities
                        *activities << line;
                        break;
                    case 5:
                        Clients.push_back(auxClient);

                        readClientsActivities(activities, auxClient);

                        activities->clear();
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
    auto* activities = new stringstream;

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
                    *activities << line;
                    break;
                case 3:
                    Teachers.push_back(auxTeacher);

                    readTeachersActivities(activities, auxTeacher); ///ERROR

                    activities->clear();
                    auxTeacher = new Teacher();
                    break;
            }

            counter++;
        }

        File.close();
    }
}

void School::readMaterials() {
    string line;
    ifstream File("../Data/" + Files["Materials"]);
    int counter = 0;

    auto* activities = new stringstream;

    string type;
    unsigned id;

    if (File.is_open()) {
        while (getline(File, line)) {
            switch (counter % 4) {
                case 0:
                    type = line;
                    break;
                case 1:
                    id = stoi(line);
                    break;
                case 2:
                    *activities << line;
                    break;
                case 3:
                    if(type == "boat"){
                        Boat* auxBoat = new Boat();
                        auxBoat->setType(type);
                        auxBoat->setID(id);

                        if (id > Material::getLastID())
                            Material::setLastID(id);

                        Materials.push_back(auxBoat);
                        readMaterialActivities(activities, auxBoat);
                    } else if (type == "suits"){
                        Suits* auxSuits = new Suits();
                        auxSuits->setType(type);
                        auxSuits->setID(id);

                        if (id > Material::getLastID())
                            Material::setLastID(id);

                        Materials.push_back(auxSuits);
                        readMaterialActivities(activities, auxSuits);
                    } else if (type == "board"){
                        Board* auxBoard = new Board();
                        auxBoard->setType(type);
                        auxBoard->setID(id);

                        if (id > Material::getLastID())
                            Material::setLastID(id);

                        Materials.push_back(auxBoard);
                        readMaterialActivities(activities, auxBoard);
                    }

                    activities->clear();
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
        throw NonExistentClient(clientId);

    bool activityExists = false;

    for (const auto &ac : ScheduledActivities) {
        if (activityId == ac->getId()){
            try {
                client->addActivity(ac, false);
                activityExists = true;
            }

            catch (clientAlreadHasActivity &e) {
                throw e;
            }
        }
    }

    if(!activityExists)
        throw activityNonExistent(activityId);
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
        throw NonExistentTeacher(teacherId);

    bool activityExists = false;

    for (const auto &ac : ScheduledActivities) {
        if (activityId == ac->getId()){
            try {
                teacher->addActivity(ac, false);
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
        throw activityNonExistent(activityId);
}

void School::readClientsActivities(stringstream* activities, Client* c) {
    int activity_id;

    while (*activities >> activity_id) {
        Activity* AuxActivity = getActivity(activity_id);

        if (AuxActivity->getEndTime() < currentTime)
            c->addActivity(AuxActivity, true);

        else {
            try {
                enroll(c->getId(), activity_id);
            }

            catch (activityNonExistent &e) {
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
}

void School::readTeachersActivities(stringstream* activities, Teacher* t) {
    int activity_id;

    while (*activities >> activity_id) {
        Activity* AuxActivity = getActivity(activity_id);

        if (AuxActivity->getEndTime() < currentTime)
            t->addActivity(AuxActivity, true);

        else {
            try {
                assign(t->getID(), activity_id);
            }

            catch (activityNonExistent &e) {
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
}

void School::readMaterialActivities(stringstream* activities, Material* m) {
    int activity_id;

    while (*activities >> activity_id) {
        Activity* AuxActivity = getActivity(activity_id);

        if (AuxActivity->getEndTime() < currentTime)
            m->addActivity(AuxActivity);
    }
}

ostream &operator<<(ostream &out, const School& S) {
    out << "Name: " << S.name << endl
        << "Current date: " << S.currentTime << endl
        << "Number of enrolled clients: " << S.Clients.size() << endl
        << "Number of occurred activities: " << S.PastActivities.size() << endl
        << "Number of planned activities: " << S.ScheduledActivities.size() << endl;

    return out;
}

void School::viewClients(bool detailed) {
    if (detailed)
        for (auto & Client : Clients)
            cout << *Client << endl
                 << "---------------------" << endl;

    else
        for (auto & Client : Clients) {
            cout << Client->getName() << " - " << Client->getId();

            if (Client->isGoldMember())
                cout << " ($)";

            cout << endl;
        }
}

void School::viewMaterial(bool detailed){
    if (detailed)
        for (auto & Material : Materials)
            cout << *Material << endl
                 << "---------------------" << endl;

    else
        for (auto & Material : Materials) {
            cout << Material->getType() << " - " << Material->getID() << endl;
        }
}

//Exceptions

std::ostream &operator<<(std::ostream &out, const NonExistentClient &client) {
    out << "Client with ID " << client.id << " does not exist in school." << endl;
    return out;
}

std::ostream &operator<<(std::ostream &out, const ClientAlreadyExists &client) {
    out << "Client with ID " << client.id << " already exists in school." << endl;
    return out;
}

std::ostream &operator<<(std::ostream &out, const NonExistentTeacher &teacher) {
    out << "Teacher with ID " << teacher.id << " does not exist in school." << endl;
    return out;
}

std::ostream &operator<<(std::ostream &out, const TeacherAlreadyExists &teacher) {
    out << "Teacher with ID " << teacher.id << "already exists in school." << endl;
    return out;
}

std::ostream &operator<<(std::ostream &out, const NonExistentMaterial &material) {
    out << "Material with ID " << material.id << " does not exist in school." << endl;
    return out;
}

void School::viewActivities(bool detailed) {
    if (detailed) {
        cout << "Scheduled Activities:\n";
        cout << "---------------------" << endl;

        for (const auto &Activity : ScheduledActivities) {
            cout << *Activity;
            cout << "---------------------" << endl;
        }
    }

    else
        for (auto & activity : ScheduledActivities)
            cout << activity->getName() << " - " << activity->getId() << endl;
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

void School::saveActivities() {
    ofstream f;
    int counter = 0;

    f.open("../Data/" + Files["Activities"]);
    vector<Activity*> Activities;
    Activities.reserve(PastActivities.size() + ScheduledActivities.size());
    Activities.insert(Activities.end(), PastActivities.begin(), PastActivities.end());
    Activities.insert(Activities.end(), ScheduledActivities.begin(), ScheduledActivities. end());
    sort(Activities.begin(), Activities.end());
    if (f.is_open())
        for (auto c : Activities) {
            f << c->getId() << endl
              << c->getType() << endl
              << c->getName() << endl
              << c->getStartTime() << endl
              << c->getEndTime() << endl
              << c->CalcCost() << endl;

            if (counter == size(Activities) - 1)
                f << "---END---";

            else
                f << "::::::::::" << endl;

            counter++;
        }

    f.close();
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
              << c->getPastActivitiesID() << c->getScheduledActivitiesID() << endl;

            if (counter == size(Clients) - 1)
                f << "---END---";

            else
                f << "::::::::::" << endl;

            counter++;
        }

    f.close();
}

void School::saveMaterials() {
    ofstream f;
    int counter = 0;

    f.open("../Data/" + Files["Materials"]);

    if (f.is_open())
        for (auto m : Materials) {
            f << m->getType() << endl
              << m->getID() << endl
              << m->getActivitiesID() << endl;

            if (counter == size(Materials) - 1)
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

    cout << "0) Go back." << endl;
}

void School::saveTeachers() {
    ofstream f;
    int counter = 0;

    f.open("../Data/" + Files["Teachers"]);

    if (f.is_open())
        for (auto t : Teachers) {
            f << t->getName() << endl
              << t->getID() << endl
              << t->getPastActivitiesID() << t->getScheduledActivitiesID() << endl;

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

void School::addActivity(Activity* activity, bool past) {
    if (past)
        PastActivities.push_back(activity);

    else
        ScheduledActivities.push_back(activity);
}

void School::removeTeacher(unsigned id) {
    if (teacherIndex(id) == -1)
        throw NonExistentTeacher(id);

    Teachers.erase(Teachers.begin()+teacherIndex(id));
}

int School::activityIndex(unsigned int id, bool past) {
    if (past) {
        for (size_t i = 0; i < PastActivities.size();i++)
            if (PastActivities.at(i)->getId() == id)
                return i;
    }

    else {
        for (size_t i = 0; i < ScheduledActivities.size();i++)
            if (ScheduledActivities.at(i)->getId() == id)
                return i;
    }

    return -1;
}

Activity * School::getActivity(unsigned int id) const {
    for (auto a : PastActivities)
        if (a->getId() == id)
            return a;

    for (auto a : ScheduledActivities)
        if (a->getId() == id)
            return a;

    return nullptr;
}


//A client can only rent it once
void School::rent(const unsigned int materialId, const unsigned int clientId, Time startTime, Time endTime) {

    if(clientIndex(clientId) == -1)
        throw NonExistentClient(clientId);

    if (materialIndex(materialId) == -1)
        throw NonExistentMaterial(materialId);


    if(Materials[materialIndex(materialId)]->beingUsed(startTime,endTime))
        throw alreadyInUse(materialId,startTime,endTime);

    try{
        if(Materials[materialIndex(materialId)]->getType() == "boat")
            Clients[clientIndex(clientId)]->addBalance(-Boat::cost);
        else if (Materials[materialIndex(materialId)]->getType() == "suits")
            Clients[clientIndex(clientId)]->addBalance(-Suits::cost);
        else if (Materials[materialIndex(materialId)]->getType() == "board")
            Clients[clientIndex(clientId)]->addBalance(-Board::cost);
    } catch (insufficientFunds &e){
        cerr << e;
    }


    Materials[materialIndex(materialId)]->Clients[Clients[clientIndex(clientId)]] = {startTime,endTime};


}


