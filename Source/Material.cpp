#include "../Headers/Material.h"


using namespace std;

unsigned int Boat::cost = 250;
unsigned int Suits::cost = 80;
unsigned int Board::cost = 30;
unsigned int Material::last_id = 0;

bool Material::beingUsed(Time startTime, Time endTime){
    try{
        if (startTime > endTime) { //Implement >=
            throw ImpossibleTimeDifference(startTime, endTime);
        }
    }
    catch(ImpossibleTimeDifference &i){
        cerr << "Start time of " << i.getStartTime() << " is after end time of " << i.getEndTime() << endl;
    }

    if (Activities.size() == 0) //Or activity == NULL
        return true;

    for(int i = 0; i < Activities.size(); i++){
        if(!(endTime < Activities[i]->getStartTime() || startTime > Activities[i]->getEndTime())){
             return true;
        }
    }

    for(const auto &m :  Clients){
        if(m.second[0] == startTime)
            return true;

        if(m.second[1] == endTime)
            return true;

        if(m.second[0] < startTime && startTime < m.second[1])
            return true;

        if(endTime > m.second[0] && endTime < m.second[1])
            return true;
    }

    return false;
}

ostream &operator<<(ostream &out, Material material) {
    out << "This is a " <<  material.getType() << "(ID: " << material.getID() << ")" << ", which is going to be used by:\n";
    for(int i= 0; i < material.Activities.size(); i++){
        cout << (material.getActivities())[i]->getName();
        if(i != material.getActivities().size() - 1)
            cout << ", ";
    }

    cout << endl;

    for(const auto &c : material.Clients){
        out << "Client with ID: " << c.first->getId() << " From: " << c.second[0] << " To: " << c.second[1] << endl;
    }
    return out;
}

//Setters
void Material::setID(int ID){
    this->ID = ID;
}

void Material::setType(string type){
    this->type = type;
}

void Material::setLastID(unsigned int id) {
    last_id = id;
}

//Getters
unsigned int Material::getID() const{
    return ID;
}

string Material::getType() const{
    return type;
}

vector<Activity *> Material::getActivities() const {
    return Activities;
}

unsigned int Material::getLastID(){
    return last_id;
}


map<Client *, vector<Time>>* Material::getClients() {
    return &Clients;
}

Material::Material() {
    this->ID = ++last_id;
    map<Client* ,vector<Time>> Clients;

}

void Material::addActivity(Activity* activity) {

        for (const auto &ac : Activities)
            if (ac->getId() == activity->getId())
                throw materialAlreadyHasActivity(ID,ac->getId()); //Not catching

        Activities.push_back(activity);

}

string Material::getActivitiesID() const {
    stringstream result;

    for (auto a : Activities)
        result << a->getId() << " ";

    return result.str();
}

void Material::setActivities(vector <Activity*> activities) {
    this->Activities = activities;
}

void Material::setClients(map<Client*,vector<Time>> clients) {
    this->Clients = clients;
}

std::ostream &operator<<(std::ostream &out, const alreadyInUse &info) {
    out << "Material with ID \"" << info.materialId << "\" is already being used between " << info.startTime << " and " << info.endTime << endl;
    return out;
}

ostream &operator<<(std::ostream &out, const materialAlreadyHasActivity &ids) {
    out << "Activity with ID \"" << ids.activityId << "\" is already using material with ID \"" << ids.materialId << endl;
    return out;
}

