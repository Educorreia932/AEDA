#include "../Headers/Material.h"

bool Material::BeingUsed(Time startTime, Time endTime){
    if(startTime > endTime){
        throw ImpossibleTimeDiference (startTime, endTime);
    }
    if(!activity){ //Ou == NULL
        return true;
    }
    else{
        if(activity->GetStartTime() > endTime || activity->GetEndTime() < endTime){
            return false;
        }
    }
    return true;
}