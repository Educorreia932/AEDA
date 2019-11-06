#include "../Headers/Material.h"

using namespace std;

bool Material::beingUsed(Time startTime, Time endTime){
    if (startTime > endTime) { //Implement >=
        throw ImpossibleTimeDiference(startTime, endTime);
        /*
        try {
            throw ImpossibleTimeDiference(startTime, endTime);
        }
        catch (ImpossibleTimeDiference ImpossibleTimeDiference(Time startTime,Time endTime)){
            cout << ImpossibleTimeDiference(startTime, endTime) << endl;
        }*/
    }

    if (activities.size() == 0) //Or activity == NULL
        return true;

    for(int i = 0; i < activities.size(); i++){
        //if(*(activity[i]))
        if(!(endTime < activities[i]->getStartTime() || startTime > activities[i]->getEndTime())){
             return true;
        }
    }

    return false;
    //return !(endTime < activity->getStartTime() || startTime > activity->getEndTime());
}

ostream &operator<<(ostream &out, Material material) {
    out << "This is a" <<  material.getObjectType() << ", which is going to be used by:\n";
    for(int i= 0; i < material.getObjectType().size(); i++){
        cout << (material.getActivities())[i]->getName();
        if(i != material.getActivities().size() - 1){
            cout << ", ";
        }
    }
    return out;
}

string Material::getObjectType() const{
    return objectType;
}

vector<Activity *> Material::getActivities() const {
    return activities;
}
