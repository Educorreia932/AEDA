#include "../Headers/Material.h"

bool Material::beingUsed(Time startTime, Time endTime){
    if(startTime > endTime){
        throw ImpossibleTimeDiference(startTime, endTime);
        /*
        try {
            throw ImpossibleTimeDiference(startTime, endTime);
        }
        catch (ImpossibleTimeDiference ImpossibleTimeDiference(Time startTime,Time endTime)){
            cout << ImpossibleTimeDiference(startTime, endTime) << endl;
        }*/
    }
    if(!activity){ //Ou == NULL
        return true;
    }
    else{
        if((activity->getStartTime() < endTime) || (activity->getEndTime() > startTime)){
            return false;
        }
    }
    return true;
}