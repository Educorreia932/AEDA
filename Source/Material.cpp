#include "../Headers/Material.h"


using namespace std;
unsigned int Boat::maxCapacity = 10;
unsigned int Suits::maxCapacity = 6;
unsigned int Board::maxCapacity = 4;
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
        //if(*(activity[i]))
        if(!(endTime < Activities[i]->getStartTime() || startTime > Activities[i]->getEndTime())){
             return true;
        }
    }

    return false;
}

ostream &operator<<(ostream &out, Material material) {
    out << "This is a" <<  material.getType() << ", which is going to be used by:\n";
    for(int i= 0; i < material.Activities.size(); i++){
        cout << (material.getActivities())[i]->getName();
        if(i != material.getActivities().size() - 1)
            cout << ", ";
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

void Material::setCapacity(unsigned int capacity){
    capacity = capacity;
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

unsigned int Material::getCapacity(){
    return capacity;
}

map<Client *, vector<Time>>* Material::getClients() {
    return &Clients;
}

Material::Material() {
    this->ID = last_id++;
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


std::ostream &operator<<(std::ostream &out, const alreadyInUse &info) {
    out << "Material with ID \"" << info.materialId << "\" is already being used between " << info.startTime << " and " << info.endTime << endl;
    return out;
}

ostream &operator<<(std::ostream &out, const materialAlreadyHasActivity &ids) {
    out << "Activity with ID \"" << ids.activityId << "\" is already using material with ID \"" << ids.materialId << endl;
    return out;
}

