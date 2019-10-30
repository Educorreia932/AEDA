#ifndef SUP_SCHOOL_MATERIAL_H
#define SUP_SCHOOL_MATERIAL_H
#include "Activity.h"
#include <vector>
#include <string>
class Material {
    public:
        bool beingUsed(Time startTime, Time endTime);
        string getObjectType() const;
    private:
        string objectType;
        vector<Activity*> activities;
};

class Boat : public Material {
};

class Suits : public Material {
};

class Board : public Material {
};

#endif //SUP_SCHOOL_MATERIAL_H
