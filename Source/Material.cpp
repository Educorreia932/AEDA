#include "../Headers/Material.h"

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

    if (!activity) //Or activity == NULL
        return true;

    return !(endTime < activity->getStartTime() || startTime > activity->getEndTime());
}